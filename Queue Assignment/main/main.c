#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

QueueHandle_t queue;        

static int shared_int = 0;

void led_blink_1()
{
    const char task[] = "led blink 1";
    while (1)
    {       shared_int += 1;
          long ok=xQueueSend(queue,&shared_int,1000/portTICK_PERIOD_MS);
        if (ok)
        {
           
                // ...
                ESP_LOGI(task,"Queue 1 Taken Succesfully | Shared Res - %d", shared_int);
                
               int rxInt1;
               xQueueReceive(queue,&rxInt1,5000/portTICK_PERIOD_MS);

            
            
        }
        else
            {
                
                ESP_LOGW(task, "Failed in sending Queue 1");
            }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void led_blink_2()
{
    const char task[] = "led blink 2";
     while (1)
    {       shared_int -= 1;
          long ok=xQueueSend(queue,&shared_int,1000/portTICK_PERIOD_MS);
        if (ok)
        {
           
               
                // ...
                ESP_LOGI(task,"Queue 2 Taken Succesfully | Shared Res - %d", shared_int);
                
               int rxInt2;
               xQueueReceive(queue,&rxInt2,5000/portTICK_PERIOD_MS);
               
            
            
        }
        else
            {
                
                ESP_LOGW(task, "Failed in sending Queue 2");
            }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
      queue=xQueueCreate(1,sizeof(int)); 
   
    

    xTaskCreate(&led_blink_1, "Led Blink 1", 4096, NULL, 0, NULL);
    xTaskCreate(&led_blink_2, "Led Blink 2", 4096, NULL, 1, NULL);
}