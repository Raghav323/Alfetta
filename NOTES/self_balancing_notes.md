**CONCEPTS**

1.**PID**:  To find correction and remove error using proportional , 
integral and derivative terms. 
Proportional decreases error but causes oscillations on its own, derivative decreases the slope 
and makes it follow straight line ,integral reduces the area between line and bot.** 

P=kpe 

I=ki*cumulative sum of errors 

D=Kd*rate of change of error

2.**PITCH**: Rotation of the bot with y axis as axis of rotation .
Note that the bot moves in the xy plane and its direction of motion 
is always along x axis . 

3.**Pitch and roll angles** : When bot rotates about y-axis 
the yaw angle is zero . Therefore we need only roll and pitch angles 
for calculations .

4.**Self  balancing concept**: We determine pitch correction for the pitch
error using PID just like in line-following and then use it as duty cycle
for motor drivers which move the bot forward/backwards and 
correct the bots angle wrt ground thanks to inertia . 


**MACROS:**

MAX_PITCH_CORRECTION 90 : Maximum allowable pitch correction is 90

MAX_PITCH_AREA 850 : Maximum allowable pitch area(for integral term) is 850

MAX_PITCH_RATE 850 : Maximum allowable pitcch rate(for derivative term) is 850

MAX_PWM 80 : Maximum allowable duty cycle for motor drivers .

MIN_PWM 60 : Minimum allowable duty cycle for motor drivers .

**FUNCTIONS** : 

1. calculate_motor_command(pitch_error,*motor_cmd)

      **Variables** : 

      **prev_pitch_error**: self-explanatory
      
      **pitch_error** : the angle by which our bot needs to rotate along y axis
      to come to horizontal state/reference position . 
      
      **pitch_error_difference** : change in pitch error 
      
      **pitch_correction**: overall correction duty cycle given to motor drivers
      so that bot moves front/back and corrects itself using inertia 
      
      **absolute_pitch_correction** : since duty cycle is always positive we take
      absolute value of pitch correction :
      
      **pitch_rate** : pitch_error_diff * delta t
      
      **P_term**=kp*pitch error ,**I_term**=pitch_area*ki,**D_term**=kd*pitch_rate

     **Explanation:**
     
      1.We find pitch error difference by subtracting prev pitch error from 
      current pitch error . We keep adding pitch error to pitch area variable
      
      2.Then we apply the formula for pitch correction which comes from concept
      of PID explained in line_following .
      
      3. We take  absolute value of pitch correction using fabsf() 

      4. Now we bound it between 0 and MAX_PITCH_CORRECTION using bound() and store
      it in *motor_cmd pointer .
      
      5. Prev_pitch_error=pitch_error (For next loop)

      **SUB FUNCTIONS**

      **fabsf()** : function used to get absolute value of floating point .
      
      **bound()** : Utility function used to bound values defined in utils.c in sra lib.

2. balance_task():

      **Euler angles**: Complementary pitch and roll angles from mpu that is 
      angles obtained after sensor fusion of accelerometer and gyroscope readings. 
      Stored in array of size 2 .
      
      **mpu_offsets**: Initial accelerometer angles 
      
      **motor_cmd**: Stores calculated correction angle from calculate_motor_command()
      
      **motor_pwm** : Stores bounded motor_cmd bounded using bound()

      **pitch_cmd** = stores reference angle using read_pid_const().setpoint
      
      **pitch_error**=pitch_cmd-pitch_angle , if its negative bot is below 
      desired position and vice versa.

      **SUB FUNCTIONS**
      read_mpu6050(euler_angle,mpu_offset) : calculates current pitch angle 
      using mpu and returns ESP_OK if successfull
      
      enable_mpu6050() : returns ESP_OK if mpu is initialized successfully.
      
      enable_motor_driver(A,Normal_mode) Enables motor driver in normal mode 


      **Explanation**:
      1) We intialize all variables above.
      
      2) We enable_mpu and if ESP_OK , we enable motor driver using enable_motor_driver()
     
      3)Read mpu values using euler angle and mpu offset and if ESP_OK we read
      pitch_cmd from server , then calculate pitch angle as pitch_cmd-pitch_angle
      
      4) Calculate correction using calculate_motor_command() and store in motor_cmd
     
      5) Bound motor_cmd between MIN_PWM AND MAX_PWM and obtain motor_pwm which
      is the desired duty cycle to be passed 
      
      6) Depending upon sign of error 
          i)If pitch error>1 we move bot backwards so that inertia pulls it down by
      setting motor speed of both motors using set_motor_speed()
      
          ii)If pitch error<-1 we move bot forwards so that inertia pulls it up by
      setting motor speed of both motors using set_motor_speed() 

          iii)if pitch_error is between 1 and -1 , this means our bot is approximately
      in the right position so we stop the bot by using set_motor_speed() function

      set_motor_speed(Motor Name , Macro defining direction , duty cycle)



3. app_main()- Just like int main()

     Inside this we use XtaskCreate() coming from FreeRTOS library to create and perform balance_task().
   
     This is explained in line_following_notes.
