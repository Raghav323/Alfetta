#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define BG_LED_1 32
#define BG_LED_2 33
#define BG_LED_3 25
#define BG_LED_4 26
#define BG_LED_5 27
#define BG_LED_6 14
#define BG_LED_7 12
#define BG_LED_8 13
static const int pin_out[8] = {BG_LED_1, BG_LED_2, BG_LED_3, BG_LED_4, BG_LED_5, BG_LED_6, BG_LED_7, BG_LED_8}; // Array storing all gpio pin numbers connected to LED

esp_err_t enable_all_gpio(){

 // Configures all the gpio pins which are connected to LEDs 

gpio_config_t io_conf;   // Configuration struct of gpio pins 

uint64_t bit_mask = (1ULL << BG_LED_1) | (1ULL << BG_LED_2) | (1ULL << BG_LED_3) | (1ULL << BG_LED_4) | (1ULL << BG_LED_5) | (1ULL << BG_LED_6) | (1ULL << BG_LED_7) | (1ULL << BG_LED_8);

io_conf.pin_bit_mask = bit_mask;    // bit mask gives position of gpio pin number to be on . 

io_conf.mode = GPIO_MODE_OUTPUT;    // We need to output from laptop to gpio pins 

io_conf.pull_up_en = 0;

io_conf.pull_down_en = 1;

io_conf.intr_type = GPIO_INTR_DISABLE;    // No Interrupts

esp_err_t err = gpio_config(&io_conf);   // GIVES ESP OK IF CONFIGURED GPIO PINS 

return err;  // Returning the error 


}

void set_all_led(bool state){


for (int i=0;i<8;i++){

    gpio_set_level((gpio_num_t)pin_out[i], state); // set the state of the led at ith index 

    }


}

void app_main(){
    ESP_ERROR_CHECK(enable_all_gpio());
    while (1){
        
        vTaskDelay(1000/portTICK_PERIOD_MS); //Delay of 1s

        set_all_led(1);   //turn on all LEDs

        vTaskDelay(1000/portTICK_PERIOD_MS); //Delay of 1s

        set_all_led(0);   //turn off all LEDs
    }
}
