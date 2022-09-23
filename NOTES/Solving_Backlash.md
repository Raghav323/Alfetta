# Possible (Not sure) Ways to solve backlash : 
1. **Buy a motor** with larger gear ratio , the back lash error decreases with gear ratio , motor with 1:120 gear ratio will have backlash/120 compared to motor with 1:1 .
2. **Compensating Torque using Integral Term** : If we can measure the speed variations between true speed and expected speed , we can calculate the error and correct it using integral term. I believe this will need an encoder for measuring true speed . 
4. **Non Linear Controllers** : 

      i) **Deadband**: 

      Sets the proportional term drive to the motor to zero when the input
      error is within some defined limit, so the motor will come to rest even if it is at a slightly
      incorrect position . Only applied on proportional term and not on derivative term so that the drive damps and there are no sudden changes .

      ii) **Switching Control** : 

      A type of hybrid controller, which switches between the
      linear controller and the Backlash controller. The switch from linear control to backlash control happens when there is a change in velocity .

      **Weighted Switching Controller**: Modified version of switching controller , backlash controller is activated due to minor changes in direction, and
    it this interrupts the linear controller from stabilizing the plat-
    form . Thereby switching controller weighing, according to
    different tilt body angle, is introduced to reduce the activity of
    the backlash controller at larger angles

    **BackLash Model**: Sandwitch model which quantifies backlash as relationship of load torque and shaft torque .  This model will give us a backlash angle . 
    We use a proportional backlash controller which uses backlash angle as a feedback input and it outputs control signal to motors accordingly . Kp = max velocity / max backlash angle 

# References 
1. https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.894.6109&rep=rep1&type=pdf
2. http://www.wescottdesign.com/articles/Friction/friction.pdf

