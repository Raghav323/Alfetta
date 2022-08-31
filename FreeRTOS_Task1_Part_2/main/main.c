#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define  BOOT_BUTTON 0
TaskHandle_t taskhandle1=NULL;
TaskHandle_t taskhandle2=NULL;
TaskHandle_t taskhandle3=NULL;
int count =0;
void myTask1(void *p){
    
    while (1){
        vTaskDelay(1000/portTICK_PERIOD_MS);
        printf("Hello World from Task 1 : %d\n",count++);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
     //Task 1 prints hello world with count

}

void myTask2(void *p){
    
    while(1){
        printf("Hello World from Task 2 : %d\n",count++);
        vTaskDelay(2000/portTICK_PERIOD_MS);
        //Task 2 prints hello world with count
    }
}

void suspend_resume_tasks(void *p){
    //Task used for suspending task 1 and task 2 when boot button is pressed . Has Higher priority than both of these . 


    static bool switcher =1;   //switcher variable used to switch between resume and suspend functions 

    while (1){
    vTaskDelay(100/portTICK_PERIOD_MS);

    bool boot_button_state=gpio_get_level((gpio_num_t) BOOT_BUTTON );  // Gets the state of the boot button . If it is pressed gpio pin becomes low level.

    if (!boot_button_state){    // if boot buttton is pressed : 

        if (switcher){    // if tasks are to be suspended 

        printf("Boot Button was pressed . Bye World ! All Tasks are suspended \n");
        vTaskSuspend(taskhandle1);
        vTaskSuspend(taskhandle2);     //Suspend Tasks 
        vTaskDelay(3000/portTICK_PERIOD_MS);  //Wait some time . To prevent immediately switching to resume 

        }

        else{      // if tasks are to be resumed 

            printf("Boot Button was pressed . All Tasks are resumed \n");
            vTaskResume(taskhandle1);
            vTaskResume(taskhandle2);  //Resume Tasks

            vTaskDelay(3000/portTICK_PERIOD_MS);  //Wait some time . To prevent immediately switching to suspend
        }

        switcher=!switcher;  //if tasks are suspended , next time boot button will resume them and vice versa .

    }

    }
}
void app_main(){

    xTaskCreate(myTask1,"Task 1",2048,NULL,5,&taskhandle1);
    xTaskCreate(myTask2,"Task 2",2048,NULL,5,&taskhandle2);
    xTaskCreate(suspend_resume_tasks,"SRTASK",2048,NULL,4,&taskhandle3);

    
}
