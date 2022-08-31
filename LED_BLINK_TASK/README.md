LED BLINK
============

![LED blinking](https://pic-microcontroller.com/wp-content/uploads/2015/10/A-complete-guide-for-LED-Blinking.jpg)

TABLE OF CONTENTS
1. [What is a LED?](#des)
2. [How does a LED blinks?](#how)
3. [Circuit Diagram](#cktd)
4. [Implementing LED blink using GPIO pins](#gpio)
5. [OUTPUT](#o)

<a name="des"></a>
What is a LED?
-----------------
<p><strong><em>Light Emitting Diode</em></strong> is a device that produces light on electrical and electronic devices.<br> It is a light sensor which emits light that is reflected from surface which further helps in sensing the environment.</p>

<a name="how"></a>
How does a LED blinks?
---------------------
There are several ways of making a blinking LED circuit.

<ul>
  <li>A relay</li>
  <li>A transistors</li>
  <li>An inverter (a logic NOT-gate)</li>
  <li>PWM</li>
</ul>

![LED blinking with ESP32](https://content.instructables.com/ORIG/F90/E6L0/JTWT5IR7/F90E6L0JTWT5IR7.jpg?crop=1%3A1&frame=1&width=320)

<a name="cktd"></a>

Circuit Diagram
----------------
![ckt](https://user-images.githubusercontent.com/70626983/108228025-7ba4d380-7164-11eb-8662-e6fbaa5f42f4.png)
<a name="gpio"></a>
Implementing LED blink using GPIO pins 
-----------------
<p>A <strong><em>General Purpose Input Output Pin </em></strong> is a device that is used to communicate between hardware and software .
We can use these to blink LEDs on and off using standard functions from driver/gpio.h header file .

<strong><em>esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)</em></strong> : Sets the gpio with the given gpio number to either on and off .

Parameters : GPIO pin Number and desired state of GPIO .

Returns ESP_OK if set successfully .

<strong><em>struct gpio_config_t </em></strong>: Struct used to configure gpio pins . After configuring them once we can set them on and off using gpio_set_level()

Parameters :

1. uint64_t pin_bit_mask : set with bit mask, each bit maps to a GPIO

2. gpio_mode_t mode: set input/output mode

3. gpio_pullup_t pull_up_en: pull-up

4. gpio_pulldown_t pull_down_en : pull-down

5. gpio_int_type_t intr_type : interrupt type

Returns ESP_OK if successfully configured .

<a name="o"></a>

https://user-images.githubusercontent.com/111511248/187690531-9be6ae85-1053-4482-86a2-69e93fd1cb0f.mp4






</p>
