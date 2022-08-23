**CONCEPTS**
PWM: Technique for getting analog results using digital means . The supply is switched on and off with a 
fast rate and the percent of time for which supply is on is called duty cycle . This fast rate leads
to perceived analog results .

**FUNCTIONS**
#define MODE NORMAL MODE 
The above  defines macro mode for the motor driver as normal mode ie one driver
controls two motors . 
**pwm_task():**
if mode is **normal** : 
1. enable motor driver A in normal mode using enable_motor_driver
2. it loops the duty cycle through 60 to 100 and sets motor speed of motors A0 and A1
according to duty cycle using set motor speed function in forward dirn
VtaskDelay adds 100 ms delay 
3.Then both motors are stopped and another delay of 100 ms to see the change .
4.it loops the duty cycle through 60 to 100 and sets motor speed of motors A0 and A1
according to duty cycle using set motor speed function in backward dirn
VtaskDelay adds 100 ms delay 

if mode is **parallel** : 
1. enable motor driver A in parallel mode using enable_motor_driver. Now only
one motor can be controlled .
2. it loops the duty cycle through 60 to 100 and sets motor speed of motor A0 
according to duty cycle using set motor speed function in forward dirn
VtaskDelay adds 100 ms delay 
3.Then both motors are stopped and another delay of 100 ms to see the change .
4.it loops the duty cycle through 60 to 100 and sets motor speed of motor A0 =
according to duty cycle using set motor speed function in backward dirn
VtaskDelay adds 100 ms delay 

**app_main()** - just like int main
Inside this we create a task using freeRTOs which will execute the pwm_task()
Its working is explained in line_following code .
