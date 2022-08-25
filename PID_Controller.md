# <div align="center">PROPORTIONAL INTEGRAL  DERIVATIVE CONTROL</div>
## Reference: https://www.wescottdesign.com/articles/pid/pidWithoutAPhd.pdf

### <div align="center">CONTROL LOOPS</div>

**Plant** : The object we want to control . In our case it is the WallE bot.

**Command**:- Task given to controller . In our case it is to align with line/balance itself.

**Drive** :- Response produced by the controller in order to complete the task . In our case this is the bot moving back/forth to self balance or left/right to follow line.

In closed Loop control systems such as in PID , the plant behaviour is measured and fed to the controller . That is the controller uses both 
feedback from the plant and the command to generate the drive . Just like in WallE bot we use previous error and current error. (feedback from bot)

### <div align="center">Basics of PID Control </div>

The Controller receives the plant feedback and command . It then finds error as command - plant_feedback . This error is used to find the proportional and
integral elements while for derivative element we directly use plant feedback .

### <div align="center">PROPORTIONAL CONTROL</div>
A proportional controller is just
the error signal multiplied by a constant and fed out to the drive.

The proportional term gets calculated with the following code within the function UpdatePID:

real_t pTerm;



pTerm = pid->propGain * error;




return pTerm;

### <div align="center">INTEGRAL CONTROL</div>
Integral control is used to add long-term precision to a control loop. It is almost always
used in conjunction with proportional control. The integrator state "remembers" all that
has gone on before, which is what allows the controller to cancel out any long term errors
in the output. This same memory also contributes to instability - the controller is always
responding too late, after the plant has gotten up speed

Given by I = cumulative sum of errors * KI

The code to implement an integrator is shown below: 

real_t iTerm;

// calculate the integral state with appropriate limiting

pid->integratState += error;

// Limit the integrator

if (pid->integratState > pid->integratMax)

{

pid->integratState = pid->integratMax;

}

else if (pid->integratState < pid->integratMin)

{

pid->integratState = pid->integratMin;

}

// calculate the integral term

iTerm = pid->integratGain * pid->integratState;

### <div align="center">DERIVATIVE CONTROL</div>

Derivative Control predicts the plant behavior .
Given by D= (de/dt )* Kd

Pseudocode for derivative control : 

real_t dTerm;

dTerm = input - pid->derState;

pid->derState = input;




 ### <div align="center">Applying PID on some example plants </div>
 
 
 #### Basic Terminologies 
 1.Gear Train : When sometimes two or more gears are made to mess with each other to transmit power from one shaft to another such combination is called gear trains.
 
 2.Shaft : A shaft is a rotating machine element, usually circular in cross section, which is used to transmit power from one part to another
 
 3.Actuator : An actuator is a device that produces a motion by converting energy and signals going into the system.

 ### <div align="center">1.Motor and gear </div>
The first example plant is a motor driving a gear train, with the output position of the
gear train being monitored by a potentiometer .
The potentiometer outputs a voltage proportional to the position of the output shaft .

The response of the motor position to input voltage is given by : 

D^2 theta = 1/tau (KVm - D) where D = d/ dt

Vm= Input Voltage , K = Motor gain 

Note : Vm is the variable we can control so we can replace Vm with some function of time and then solve the differential equation .

#### STEP RESPONSE 
A useful concept when working with control systems is the “step response”. A system’s
step response is just the behavior of the system output in response to an input that goes
from zero to some constant value at time t = 0 . Its equivalent to plugging Vm= some constant in above differential equation and solving it .

On solving we get motor_angle=A+ Be^-kx + Cx  which has following graph : 


**Only Proportional Control on Motor and Gear** 

For small gains (propGain or kp = 1) the motor goes to the correct
target, but it does so quite slowly. Increasing the gain (kp = 2) speeds up the response to
a point. Beyond that point (kp = 5, kp = 10) the motor starts out faster but overshoots the target.
The reason the motor and gear start to overshoot with high gains is because of the delay
in the motor response. 

**Only Integral Control on Motor and Gear**

 This system simply doesn’t settle, no matter how
low you set the integral gain. Like the precision actuator with proportional control, the
motor and gear system with integral control  will oscillate with bigger and bigger
swings until something hits a limit

**Proportional and Integral Control on Motor and Gear**

The position takes longer to settle out than the system with pure proportional control, but unlike the
motor with pure integral control it does settle out, and the system will not settle to the
wrong spot.

 ###  <div align="center"> 2. Precision Actuator </div>
 
 Used for accurate positional movements .Software commands the current in the coil. This current 
 sets up a magnetic field which exerts a force on the magnet. The magnet is attached to the stage, which moves 
 with an acceleration proportional to the coil current. Finally, the stage position is monitored by a non-contact position transducer.
 
 Force on the system is directly proportional to the drive command that is current so the DE is :
 
 m a= k i  
 
 D^2x = Ki/m  where D= d/dt
 
 For step response , i=constant , solving equation using basic calculus gives equation of parabola. 
 This makes control problem even harder as the system will keep wanting to move when it gets going .
 
 **Only Proportional Control on Precision Actuator**
 
There is so much delay in the plant that no matter how low the gain is the
system will oscillate. As the gain is increased the frequency of the output will increase, but
the system just won’t settle
 
 **Only Integral Control on Precision Actuator**
 
 Since the system cannot be stabilised with proportional control , it cannot be with integral control either 
 
**Proportional and Integral Control on Precision Actuator**

Not enough as it fails using only proportional and only integral . 


**Proportional and Derivative Control on Precision Actuator**

This system settles in less than 1/2 or a second, compared to multiple seconds for the
other systems.



 ###  <div align="center">3. Temperature Controller </div>
 The vessel is heated by an electric heater, and the temperature of its
contents is sensed by a temperature sensing device. Its DE: 

D^2 T = -(1/tau1 + 1/tau2) D -T/(tau1*tau2) + (K*V + Ta)/(tau1*tau2) where T is current temperature, Ta is ambient temperature , Vd is input drive 

For step response , lets consider a change in vd and change in ambient temperature , Change in ambient temp can be regarded as disturbance : 


**Only Proportional Control on Temperature Controller**

With or without the disturbance , proportional control doesn’t get the temperature to the desired setting; with the
disturbance loop is susceptible to external effects. 

Increasing the gain helps with both the settling to target and with the disturbance rejection
But high gain results in strong overshoot at start that continues to travel back and forth for some time before settling out.


**Only Integral Control on Temperature Controller**

This system takes a lot longer to settle out than the same plant with proportional control
 but when it does settle out it settles out to the target value - even the undesired response
 from the disturbance goes to zero eventually.
 
 **Proportional and Integral Control on Temperature Controller**
 
 The heater still settles out to the exact target temperature as with pure integral control
 , but with PI control it settles out 2 to 3 times faster.


### Important Parameters for integrators 

1.**Sampling rate** : For a PI controller  prefer to have a system where each sample falls within ±1% to ±5 of the correct sample time,
and a long-term average rate that is right on the button.

2.**Prevent Integrator Windup**: If you use a PI controller, then all the time spent in
saturation can cause the integrator state to grow (wind up) to very large values. When the
plant reaches the target, the integrator value is still very large, so the plant drives beyond
the target while the integrator unwinds and the process reverses. This situation can get so
bad that the system never settles out, but just slowly oscillates around the target position. 

To deal with integrator windup , we can limit the value of integrator state(integral term ) within the bounds 
of the drive output.

### Problems with Differential Control 

The three problems with differential control are sampling
irregularities, noise, and high frequency oscillations.

The output is proportional to the position change divided by the sample time. If the position is changing
at a constant rate but your sample time varies from sample to sample then you will get
noise on your differential term. Since the differential gain is usually high, this noise will
be amplified a great deal.

At worst you want the sampling interval to be consistent to within 1% of the total at all times,
the closer the better.

Either set the hardware up to reinforce sampling  or give priority to sampling in software .


### Complete Controller 

Code for complete controller : 

typedef struct

{

real_t derState; // Last position input

real_t integratState; // Integrator state

real_t integratMax, // Maximum and minimum

integratMin; // allowable integrator state

real_t integratGain, // integral gain


propGain, // proportional gain

derGain; // derivative gain

} SPid;

real_t UpdatePID(SPid * pid, real_t error, real_t position)

{

real_t pTerm, dTerm, iTerm;

pTerm = pid->propGain * error; // calculate the proportional term

// calculate the integral state with appropriate limiting


pid->integratState += error;

// Limit the integrator state if necessary

if (pid->integratState > pid->integratMax)

{

pid->integratState = pid->integratMax;

}

else if (pid->integratState < pid->integratMin)
{

pid->integratState = pid->integratMin;

}
// calculate the integral term


iTerm = pid->integratGain * pid->integratState;

// calculate the derivative

dTerm = pid->derGain * (pid->derState - position);

pid->derState = position;

return pTerm + dTerm + iTerm;

}


### Tuning the PID Controller 

#### Adjusting Derivative Gain

1.Check to see how the system works. If it oscillates with proportional gain you should
be able to cure it with differential gain.

 2.Start with about 100 times more derivative gain than
proportional gain. Watch your drive signal while you stimulate the system. If the system
oscillates under derivative control when it did not oscillate under proportional control
alone, or if the system oscillates much faster when you dial in some derivative gain, back
the derivative gain off by factors of two until it stops.

3.Push the gain up until the system is on the verge of oscillation,
then back the gain off by a factor of 2 or 4. Make sure the drive signal still looks good. At
this point your system will probably be settling out very sluggishly, so its time to tune the
proportional and integral gains.


#### Adjusting Integral Gain

1.Set it after setting proportional gain.

2.If you are using derivative gain, a good starting value for the integrator gain is to set it
smaller than the proportional gain by the same ratio as proportional gain to derivative
gain. 

For example, if you have a derivative gain of 1000 and a proportional gain of 10 (a
100:1 ratio), set the starting integrator gain to 0.1.

3.If you are not using derivative gain, a good starting value for the integrator gain will
be around 1/100 of the proportional gain.

4.If you see oscillation, decrease the integrator gain by steps of 8 or 10 until the oscillation goes away. 

5.If you don’t seeoscillation, increase the integrator gain by steps of 8 or ten until you do. 

6.Try to find the gain where the system just breaks into oscillation, and then back the gain
off by a factor of 2 or 4.




#### Adjusting Proportional Gain

1.If you have nonzero derivative gain in your system, a good starting value for the proportional gain is 1/100 of the derivative gain value.
 
2.If you are not using derivative action in the system, find a starting value for the proportional gain. In most control systems, a gain
of between 1 and 100 is a good point to start.

3.If you see oscillation drop the proportional gain by factors of 8 or 10 until the oscillation
stops. 

4.If you don’t see oscillation, increase the proportional gain by factors of 8 or 10
until you start seeing oscillation or excessive overshoot. 

5.Once you are close, fine tune the proportional gain by factors of two until you see oscillation, then back the gain off by a
factor of two or four.
