**CONCEPTS :**
**MPU**: Motion processing unit contains gyroscope and 
accelerometer to obtain the changes in roll and pitch used for self balancing task.

**euler_angle[2],mpu_offset[2**] are float arrays of size 2 to store 
pitch and yaw values . These are passed to read_mpu function to find 
final angles .

**Tag**: const character pointer used as tag for esplogi function .

**Functions**:

**read_mpu()** (Written inside sra header file)
1. Euler angles are obtained by reading values from the accelerometer and gyroscope
2.Calculating change in roll, pitch from raw accelerometer and gyroscope readings seperately
3.performing sensor fusion via complementary filter to obtain a stable reading
4.changes in angles from both measurements are weighted and added to the complementary angle

**enable_mpu()** : enables the mpu and returns ESP_OK if successfull.
It uses I2C communication protocol . Written inside sra library.

**app_main()**: Just like int main
**xTaskCreate()**: freeRtos function to create task . Explanation in line_following code .
