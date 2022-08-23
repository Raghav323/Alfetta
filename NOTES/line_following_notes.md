**CONCEPTS**:

**PID** : To find correction and remove error using proportional , integral and derivative terms. 
Proportional decreases error but causes oscillations on its own, derivative decreases the slope and makes 
it follow straight line  , integral reduces the area between line and bot.**
P=kp*e
I=ki*cumulative sum of errors 
D=Kd*rate of change of error 

**Duty_cycle** : percentage of time the load circuit is on  
**optimum Duty_cycle:** current duty cycle 
**lower duty cycle:** minimum allowable duty cycle 
**higher_duty_cycle:** maximum allowable duty cycle 

**FUNCTIONS :**

**lsa_to_bar()**{
Purpose:
To showcase the lsa readings on the 8 leds 
var : 8bit unsigned int used to send data to set_bar_graph() which sets led 
number[]: A list to store the state of all 8 leds, with last 4 being used 
to store the state of 4 line sensors 
bool_to_uint8() : Converts the 8 bit array of number[] to unsigned int and stores 
in var

This var is send to set_bar_graph() which turns on the respective leds . 
}

**calculate_correction()**{
Explanation : 
Difference of error is calculated as error-prev_error used for D term .
Cumulative sum of error is stored in cumulative_error used for I term. 
This is bound between -30 and 30 to prevent overshoot.
Correction is calculated using = Kp*error+Ki*cumulative_error+kd*diff
previous error = error //for next loop 


**bound():** helper function defined in utils.c of sra-components
 . Uses basic if , else statements to bound a value . 
}
**calculate_error()**{
Explanation :
1. Calculates weighted sum of readings from 4 lsa sensors as 
3*L2+L1-R1-3*R1 using for loop. Its magnitude represents the amound of error
and direction represents if we need to move left or right .
2. Calculates sum of readings from 4 lsa sensors using for loop 
3. pos = weightedsum/sum gives position wrt line 

Also using flag variable in for loop we find out if bot is touching line 
or far away from line . 
Using simple if else statements :
if bot is far away : error= +- 2.5 depending upon prev error
if bot is touching the line even a bit : error =pos 
}

**line_follow_task()**{
Explanation : First the line sensor tasks are bounded and mapped
to respective margins (Also explained in lsa notes) using utility functions 
which have basic maths and if-else as their definitions.
Then error is calculated using calculate_error()
Then correction is calculated using calculate_correction()
lsa readings displayed on leds using lsa_to_bar()

left duty cycle = optimal duty cycle - correction 
right duty cycle = optimal duty cycle+ correction
so if correction is positive bot moves towards left and vice versa .
These is then bounded between lower and higher duty cycles 
These values are then passed to set_motor_speed with MOVE_FORWARD
to move motors A0 and A1 using normal mode . 
}
**app_main()** - just like int main 
inside this we created a freeRTOS function called 
XtaskCreate(pointer to task,task_name,stack_size,parameters,priority,created_task )
this Xtask creates and executes the line_follow_task

}
