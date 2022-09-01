#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static int shared_int = 0;  //shared resource 


TaskHandle_t taskhandle1=NULL;   // taskhandles 
TaskHandle_t taskhandle2=NULL;

void led_blink_1(void *p)
{
    const char task[] = "led blink 1";
    while (1)
    {

        

            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.

            if (ulTaskNotifyTake(pdTRUE,portMAX_DELAY))  //takes the task notification at index 0 and resets it to 0 
                                                            // if we have been given task notification it will return notification value which would be 1 
                                                            // if not given task notification value would be 0 and therefore we havent been given the "semaphore"




            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                shared_int += 1;
                // ...
                ESP_LOGI(task,"Semaphore Taken Succesfully | Shared Res - %d", shared_int);
                // We have finished accessing the shared resource.  Release the
                // semaphore.
                xTaskNotifyGive(taskhandle2); // increment the task notification value at index 0 by 1 for task2

            }
            else
            {
                // We could not obtain the semaphore and can therefore not
                // access the shared resource safely.
                ESP_LOGW(task, "Failed in taking Semaphore");
            }
            vTaskDelay(1000/portTICK_PERIOD_MS); 
        }
        
    }


void led_blink_2(void *p)
{
    const char task[] = "led blink 2";
    while (1)
    {
        
            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.

            //takes the task notification at index 0 and resets it to 0 
            // if we have been given task notification it will return notification value which would be 1 
            // if not given task notification value would be 0 and therefore we havent been given the "semaphore"

            if (ulTaskNotifyTake(pdTRUE,portMAX_DELAY))
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                shared_int -= 1;
                // ...
                ESP_LOGI(task,"Semaphore Taken Succesfully | Shared Res - %d", shared_int);
                // We have finished accessing the shared resource.  Release the
                // semaphore.
                xTaskNotifyGive(taskhandle1); // increment the task notification value at index 0 by 1 for task1
            }
            else
            {
                // We could not obtain the semaphore and can therefore not
                // access the shared resource safely.
                ESP_LOGW(task, "Failed in taking Semaphore");
            }
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void start_transmission(void *p){

    //semaphore must be given before it can be taken

    while (1){
        xTaskNotifyGive(taskhandle2);   //giving notification to task 2 equivalent to giving semaphore in order to start the whole process
        vTaskSuspend(NULL);  //suspend this task as we dont need it after starting transmission 
    }

}
void app_main()
{
   
    
    
    // The semaphore must be given before it can be taken . The function start transmission gives the semaphore to a task . 

    xTaskCreate(&start_transmission, "start_transmission", 4096, NULL, 0, NULL);

    xTaskCreate(&led_blink_1, "Led Blink 1", 4096, NULL, 1, &taskhandle1);

    xTaskCreate(&led_blink_2, "Led Blink 2", 4096, NULL, 2, &taskhandle2);
}
