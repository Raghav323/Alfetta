#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

typedef struct qBinary_semaphore_Handle{
    QueueHandle_t queue;
    int placeholder;
    int dump;
}

 void qCreate_Binary_Semaphore(struct qBinary_semaphore_Handle *bsh){
        bsh->queue=xQueueCreate(1,sizeof(int));
        bsh->placeholder=1;
        
        bsh->dump=0;
    }
 bool qSemaphoreTake(struct qBinary_semaphore_Handle *bsh,float delay){
        bool result=xQueueReceive(bsh->queue,&(bsh->dump),delay);
        if (result){
            return 1;
        }
        return 0;
    }

void qSemaphoreGive(struct qBinary_semaphore_Handle *bsh,float delay){
        bool result=xQueueSend(bsh->queue,&(bsh->placeholder),delay);
        if (result){
            printf("Gave up the semaphore successfully ! \n");
        }
        else{
            printf("Failed to give up the semaphore ! \n ");
        }
    }
    
struct qBinary_semaphore_Handle bi_sema;

static int shared_int = 0;

void led_blink_1()
{
    const char task[] = "led blink 1";
    while (1)
    {

      
            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.
            if (qSemaphoreTake(&bi_sema, 10/portTICK_PERIOD_MS) )
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                shared_int += 1;
                // ...
                ESP_LOGI(task,"Semaphore Taken Succesfully | Shared Res - %d", shared_int);
                // We have finished accessing the shared resource.  Release the
                // semaphore.
                qSemaphoreGive(&bi_sema,0);
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

void led_blink_2()
{
    const char task[] = "led blink 2";
    while (1)
    {
        
            // See if we can obtain the semaphore.  If the semaphore is not
            // available wait 10 ticks to see if it becomes free.
            if (qSemaphoreTake(&bi_sema, 10/portTICK_PERIOD_MS) == pdTRUE)
            {
                // We were able to obtain the semaphore and can now access the
                // shared resource.
                shared_int -= 1;
                // ...
                ESP_LOGI(task,"Semaphore Taken Succesfully | Shared Res - %d ", shared_int);
                // We have finished accessing the shared resource.  Release the
                // semaphore.
                qSemaphoreGive(&bi_sema,0);
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

void app_main()
{
    qCreate_Binary_Semaphore(&bi_sema);
    // xSemaphoreCreateBinary() Creates a new binary semaphore instance, and
    // returns a handle by which the new semaphore can be referenced.
    
    qSemaphoreGive(&bi_sema,0);
    // The semaphore must be given before it can be taken if calls are made
    // using xSemaphoreCreateBinary()

    xTaskCreate(&led_blink_1, "Led Blink 1", 4096, NULL, 0, NULL);
    xTaskCreate(&led_blink_2, "Led Blink 2", 4096, NULL, 1, NULL);
}
