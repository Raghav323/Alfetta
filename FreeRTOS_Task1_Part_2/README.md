# Suspending and Resuming Tasks Using Boot Button 

**Gpio pins** : General Purpose Input Output Pins . Used for communication between software and hardware .

**BOOT BUTTON** : Button on ESP32 connected to gpio pin number 0 . Can be used as a general purpose button .
When pressed state of gpio pin becomes 0 .

**int gpio_get_level(gpio_num_t gpio_num)** : Takes the gpio pin number as input and returns its state . Can be used to detect when 
boot button is pressed .

## OUTPUT 

