LED BLINK CODE NOTES 

1. app_main is just like int main but for embedded programs. We can write code to be exected here .
2. esp_error_check checks for a tag called esp ok , if it does not get esp ok it prints
error message and aborts the program.
3. Tick rate : no of times information is updated in a second . Unit - hertz
4. portTICK_RATE_MS : tick rate in milliseconds 
5. vTaskDelay(1000/portTick_RATE_MS) : adds delay of 1s as 1000/portTICK_RATE_MS is one second . This enables us to see the led for 1s..
6. Gpio pins : For communication of esp idf with wall E bot
7 . enable_bar_graph() : turns on gpio pins and returns ESP_OK if succeeded 
8. set_bar_graph( hexadecimal number ): gives information to leds . The hexadecimal number is converted to binary . Example : 0xFF → 1111 1111 means all leds are on.
9. left - shift operator (<<) : adds specified number of zeroes  to the right of the binary number Ex : 5<<2 → 00101 << 2 which means 10100 which is 20 .
This can be used to shift the led blinks from one led to another . Doing this in a loop will give the led blink task result . 
