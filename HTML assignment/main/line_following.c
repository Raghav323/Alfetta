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
#define MAX_PWM (100.0f)
#define MIN_PWM (60.0f)

int optimum_duty_cycle = 63;
int lower_duty_cycle = 50;
int higher_duty_cycle = 76;
float left_duty_cycle = 0, right_duty_cycle = 0;
const int weights[4] = {3,1,-1,-3};

float error=0, prev_error=0, difference, cumulative_error, correction;
line_sensor_array line_sensor_readings;
//line follow yaw
void lsa_to_bar()
{   
    uint8_t var = 0x00;                     
    bool number[8] = {0,0,0,0,0,0,0,0};
    for(int i = 0; i < 4; i++)
    {
        number[7-i] = (line_sensor_readings.adc_reading[i] < BLACK_MARGIN) ? 0 : 1; //If adc value is less than black margin, then set that bit to 0 otherwise 1. 
        var = bool_to_uint8(number);  //A helper function to convert bool array to unsigned int.
        ESP_ERROR_CHECK(set_bar_graph(var)); //Setting bar graph led with unsigned int value.
    }
}

void calculate_correction()
{
    error = error*10;  // we need the error correction in range 0-100 so that we can send it directly as duty cycle paramete
    difference = error - prev_error;
    cumulative_error += error;

    cumulative_error = bound(cumulative_error, -30, 30);

    correction = read_pid_const().kp*error + read_pid_const().ki*cumulative_error + read_pid_const().kd*difference;           //yaw kp ki kd
    prev_error = error;
}

void calculate_error()
{
    int all_black_flag = 1; // assuming initially all black condition
    float weighted_sum = 0, sum = 0; 
    float pos = 0;
    
    for(int i = 0; i < 4; i++)
    {
        if(line_sensor_readings.adc_reading[i] > BLACK_MARGIN)
        {
            all_black_flag = 0;
        }
        weighted_sum += (float)(weights[i]) * (line_sensor_readings.adc_reading[i]);
        sum = sum + line_sensor_readings.adc_reading[i];
    }

    if(sum != 0) // sum can never be 0 but just for safety purposes
    {
        pos = weighted_sum / sum; // This will give us the position wrt line. if +ve then bot is facing left and if -ve the bot is facing to right.
    }

    if(all_black_flag == 1)  // If all black then we check for previous error to assign current error.
    {
        if(prev_error > 0)
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



void self_and_line(void* arg)
{

         //task- to check working of new html site

#ifdef CONFIG_ENABLE_OLED
    // Declaring the required OLED struct
    u8g2_t oled_config;

    // Initialising the OLED
    ESP_ERROR_CHECK(init_oled(&oled_config));

#endif
          while(true) {
         ESP_LOGI("debug", "KP: %f ::  KI: %f  :: KD: %f :: KP2: %f ::  KI2: %f  :: KD2: %f", read_pid_const().kp, read_pid_const().ki, read_pid_const().kd ,  read_pid_const2().kp2, read_pid_const2().ki2, read_pid_const2().kd2);


 #ifdef CONFIG_ENABLE_OLED
        // Diplaying kp, ki, kd values on OLED 
        if (read_pid_const().val_changed)
        {
            display_pid_values(read_pid_const().kp, read_pid_const().ki, read_pid_const().kd,read_pid_const2().kp2, read_pid_const2().ki2, read_pid_const2().kd2, &oled_config);
            reset_val_changed_pid_const();
        }

        if (read_pid_const2().val_changed)
        {
             display_pid_values(read_pid_const().kp, read_pid_const().ki, read_pid_const().kd,read_pid_const2().kp2, read_pid_const2().ki2, read_pid_const2().kd2, &oled_config);
            reset_val_changed_pid_const2();
        }
#endif

          }
 
}








void app_main()
{   
    xTaskCreate(&self_and_line, "self_and_line", 4096, NULL, 1, NULL);
    start_tuning_http_server();
}
