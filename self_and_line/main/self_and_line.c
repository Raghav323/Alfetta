#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sra_board.h"
#include "tuning_http_server.h"
#include <math.h>

#define MODE NORMAL_MODE
#define BLACK_MARGIN 400
#define WHITE_MARGIN 2000
#define bound_LSA_LOW 0
#define bound_LSA_HIGH 1000
#define MAX_PITCH_CORRECTION (90.0f)
#define MAX_PITCH_AREA (850.0f)
#define MAX_PITCH_RATE (850.0f)
#define MAX_PWM (65.0f)
#define MIN_PWM (60.0f)

/* Self Balancing Tuning Parameters
float forward_offset = 2.51f;
float forward_buffer = 3.1f;
*/

/* 2 0 8 1.5 0 3 10 0.1 -0.1 67 67
minmax pwm 60 65
lowerhigherduty 60 80
purebalancingpart motor pwm
mixpart fwdpwm+correction
*/

/* 2 0 8 1.5 0 3 10 0.1 -0.1 67 67
minmax pwm 60 65
lowerhigherduty 60 80
purebalancingpart motor pwm
mixpart motorpwm+correction
not that great cuz when good balance then it enters mixedpart where motorpwm is very less
*/

float euler_angle[2], mpu_offset[2] = {0.0f, 0.0f};

SemaphoreHandle_t bi_sema = NULL;

float pitch_angle, pitch_error;

float motor_cmd, motor_pwm = 0.0f;
float left_combined_cycle = 0.0f;
float right_combined_cycle = 0.0f;

float pitch_cmd = 0.0f;
bool run = 1;
int optimum_duty_cycle = 63;
int lower_duty_cycle = 60;  // 50
int higher_duty_cycle = 80; // 76
float left_duty_cycle = 0, right_duty_cycle = 0;
const int weights[4] = {3, 1, -1, -3};
float forward_pwm = 0;
float hlp = 0;
float llp = 0;
float x = 0;
float y = 0;

float error = 0, prev_error = 0, difference, cumulative_error, correction;
line_sensor_array line_sensor_readings;

void lsa_to_bar()
{
    uint8_t var = 0x00;
    bool number[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        number[7 - i] = (line_sensor_readings.adc_reading[i] < BLACK_MARGIN) ? 0 : 1; // If adc value is less than black margin, then set that bit to 0 otherwise 1.
        var = bool_to_uint8(number);                                                  // A helper function to convert bool array to unsigned int.
        ESP_ERROR_CHECK(set_bar_graph(var));                                          // Setting bar graph led with unsigned int value.
    }
}

void calculate_correction()
{
    error = error * 10; // we need the error correction in range 0-100 so that we can send it directly as duty cycle paramete
    difference = error - prev_error;
    cumulative_error += error;

    cumulative_error = bound(cumulative_error, -30, 30);

    correction = read_pid_const().kp * error + read_pid_const().ki * cumulative_error + read_pid_const().kd * difference; // yaw kp ki kd
    prev_error = error;
}

void calculate_error()
{
    int all_black_flag = 1; // assuming initially all black condition
    float weighted_sum = 0, sum = 0;
    float pos = 0;

    for (int i = 0; i < 4; i++)
    {
        if (line_sensor_readings.adc_reading[i] > BLACK_MARGIN)
        {
            all_black_flag = 0;
        }
        weighted_sum += (float)(weights[i]) * (line_sensor_readings.adc_reading[i]);
        sum = sum + line_sensor_readings.adc_reading[i];
    }

    if (sum != 0) // sum can never be 0 but just for safety purposes
    {
        pos = weighted_sum / sum; // This will give us the position wrt line. if +ve then bot is facing left and if -ve the bot is facing to right.
    }

    if (all_black_flag == 1) // If all black then we check for previous error to assign current error.
    {
        if (prev_error > 0)
        {
            error = 2.5;
        }
        else
        {
            error = -2.5;
        }
    }
    else
    {
        error = pos;
    }
}

void calculate_motor_command(const float pitch_error, float *motor_cmd)
{

    static float prev_pitch_error = 0.0f;

    static float pitch_area = 0.0f;

    float pitch_error_difference = 0.0f;

    float pitch_correction = 0.0f, absolute_pitch_correction = 0.0f;

    float pitch_rate = 0.0f;

    float P_term = 0.0f, I_term = 0.0f, D_term = 0.0f;

    pitch_error_difference = pitch_error - prev_pitch_error;

    pitch_area += (pitch_error);

    pitch_rate = pitch_error_difference;

    P_term = read_pid_const2().kp2 * pitch_error;
    I_term = read_pid_const2().ki2 * bound(pitch_area, -MAX_PITCH_AREA, MAX_PITCH_AREA);
    D_term = read_pid_const2().kd2 * bound(pitch_rate, -MAX_PITCH_RATE, MAX_PITCH_RATE);

    pitch_correction = P_term + I_term + D_term;

    absolute_pitch_correction = fabsf(pitch_correction);

    *motor_cmd = bound(absolute_pitch_correction, 0, MAX_PITCH_CORRECTION);
    prev_pitch_error = pitch_error;
}

void pure_balance(void *arg)
{

    const char task[] = "pure_balance";

    while (true)
    {
        if (bi_sema != NULL)
        {
            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.
            if (xSemaphoreTake(bi_sema, 10 / portTICK_PERIOD_MS) == pdTRUE)
            {
                read_mpu6050(euler_angle, mpu_offset);
                pitch_cmd = read_pid_const2().setpoint;
                pitch_angle = euler_angle[1];
                pitch_error = pitch_cmd - pitch_angle;

                calculate_motor_command(pitch_error, &motor_cmd);

                line_sensor_readings = read_line_sensor();
                for (int i = 0; i < 4; i++)
                {
                    line_sensor_readings.adc_reading[i] = bound(line_sensor_readings.adc_reading[i], BLACK_MARGIN, WHITE_MARGIN);
                    line_sensor_readings.adc_reading[i] = map(line_sensor_readings.adc_reading[i], BLACK_MARGIN, WHITE_MARGIN, bound_LSA_LOW, bound_LSA_HIGH);
                }

                calculate_error();
                calculate_correction();
                lsa_to_bar();

                //  left_duty_cycle = bound((optimum_duty_cycle - correction), lower_duty_cycle, higher_duty_cycle);
                // right_duty_cycle = bound((optimum_duty_cycle + correction), lower_duty_cycle, higher_duty_cycle);

                motor_pwm = bound((motor_cmd), MIN_PWM, MAX_PWM);

                // left_combined_cycle = bound(motor_cmd - correction, MIN_PWM, MAX_PWM);
                // right_combined_cycle = bound(motor_cmd + correction, MIN_PWM, MAX_PWM);

                if (pitch_error > 1)
                {

                    set_motor_speed(MOTOR_A_0, MOTOR_BACKWARD, motor_pwm);
                    // printf("%f correction",correction);
                    set_motor_speed(MOTOR_A_1, MOTOR_BACKWARD, motor_pwm);
                }

                else if (pitch_error < -1)
                {

                    set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, motor_pwm);

                    set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, motor_pwm);
                }

                else
                {

                    xSemaphoreGive(bi_sema);
                }

                ESP_LOGI("debug", "KP: %f ::  KI: %f  :: KD: %f :: KP2: %f ::  KI2: %f  :: KD2: %f :: Setpoint: %0.2f  | Pitch: %0.2f | PitchError: %0.2f", read_pid_const().kp, read_pid_const().ki, read_pid_const().kd, read_pid_const2().kp2, read_pid_const2().ki2, read_pid_const2().kd2, read_pid_const2().setpoint, euler_angle[1], pitch_error);
            }
        }
        // vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void forward_line(void *arg)
{
    //    set_motor_speed(MOTOR_A_0, MOTOR_STOP, 0);

    // 	set_motor_speed(MOTOR_A_1, MOTOR_STOP, 0);
    const char task[] = "forward_line";

    while (1)
    {
        if (bi_sema != NULL)
        {
            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.

            if (xSemaphoreTake(bi_sema, 10 / portTICK_PERIOD_MS) == pdTRUE)
            {
                read_mpu6050(euler_angle, mpu_offset);
                pitch_cmd = read_pid_const2().setpoint;
                pitch_angle = euler_angle[1];
                pitch_error = pitch_cmd - pitch_angle;
                calculate_motor_command(pitch_error, &motor_cmd);

                hlp = read_pid_const2().hlp;
                llp = read_pid_const2().llp;
                x = read_pid_const2().x;
                y = read_pid_const2().y;

                forward_pwm = (hlp - llp) * pitch_angle / (x - y) + hlp - (hlp - llp) * (read_pid_const2().setpoint - y) / (x - y);

                //  set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, forward_pwm);

                //   set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, forward_pwm);

                line_sensor_readings = read_line_sensor();
                for (int i = 0; i < 4; i++)
                {
                    line_sensor_readings.adc_reading[i] = bound(line_sensor_readings.adc_reading[i], BLACK_MARGIN, WHITE_MARGIN);
                    line_sensor_readings.adc_reading[i] = map(line_sensor_readings.adc_reading[i], BLACK_MARGIN, WHITE_MARGIN, bound_LSA_LOW, bound_LSA_HIGH);
                }

                calculate_error();
                calculate_correction();
                lsa_to_bar();

                //  left_duty_cycle = bound((optimum_duty_cycle - correction), lower_duty_cycle, higher_duty_cycle);
                // right_duty_cycle = bound((optimum_duty_cycle + correction), lower_duty_cycle, higher_duty_cycle);

                left_duty_cycle = bound(forward_pwm - correction, lower_duty_cycle, higher_duty_cycle);
                right_duty_cycle = bound(forward_pwm + correction, lower_duty_cycle, higher_duty_cycle);

                set_motor_speed(MOTOR_A_0, MOTOR_FORWARD, left_duty_cycle);
                set_motor_speed(MOTOR_A_1, MOTOR_FORWARD, right_duty_cycle);

                if (pitch_error > x || pitch_error < y)
                {
                    xSemaphoreGive(bi_sema);
                }
            }
        }
    }
}

void app_main()
{
    enable_mpu6050();
    enable_motor_driver(a, NORMAL_MODE);
    enable_line_sensor();
    enable_bar_graph();

    bi_sema = xSemaphoreCreateBinary();
    xSemaphoreGive(bi_sema);

    xTaskCreate(&pure_balance, "pure_balance", 4096, NULL, 1, NULL);
    xTaskCreate(&forward_line, "forward_line", 4096, NULL, 2, NULL);
    start_tuning_http_server();
}
