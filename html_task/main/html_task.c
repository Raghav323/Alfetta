#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sra_board.h"
#include "tuning_http_server.h"
#include <math.h>


void self_and_line(void* arg)
{


         while(true) {
        ESP_LOGI("debug", "KP: %f ::  KI: %f  :: KD: %f :: KP2: %f ::  KI2: %f  :: KD2: %f", read_pid_const().kp, read_pid_const().ki, read_pid_const().kd ,  read_pid_const2().kp2, read_pid_const2().ki2, read_pid_const2().kd2);


             vTaskDelay(10);
          }
 

}







void app_main()
{   
    xTaskCreate(&self_and_line, "self_and_line", 4096, NULL, 1, NULL);
    start_tuning_http_server();
}
