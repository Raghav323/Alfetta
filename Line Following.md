Line Following Code Notes


Pid principle:-
Proportional decreases error but causes oscillations

 Derivative decreases the slope and makes it follow straight line Bot might stop oscillating and follow straight line but path slightly deviated from the line on either of the side. 

 Integral reduces the area enclosed between line and path of the bot.
Weights = 3 , 1 ,-1 , -3 given to 4 sensor 


FUNCTIONS :

lsa_to_bar():-Purpose: To showcase the lsa readings on the 8 leds var : 8bit unsigned int used to send data to set_bar_graph() which sets led number[]: A list to store the state of all 8 leds, with last 4 being used to store the state of 4 line sensors bool_to_uint8() : Converts the 8 bit array of number[] to unsigned int and stores in var

This var is sent to set_bar_graph() which turns on the respective leds . 

calculate_correction():-  Difference= error-prev_error (used for Derivative term) .  cumulative_error= cumulative-error + error (used for I term).
 Correction = Kp*error+Ki*cumulative_error+kd*difference

Calculate_error():- error = pos 
Weighted sum= weights*line_sensor_readings
sum= sum of light sensor readings

Where pos = weighted sum/ sum gives position wrt line

Bound,map = explained in lsa

line_follow_task() :- Readings are first bounded to margins(done in lsa notes)
Then following fns are called
        calculate_error();
        calculate_correction();
        lsa_to_bar();

Then according to correction duty cycle is set 
left_duty_cycle = bound((optimum_duty_cycle - correction), lower_duty_cycle, higher_duty_cycle)
right_duty_cycle = bound((optimum_duty_cycle + correction), lower_duty_cycle, higher_duty_cycle)
