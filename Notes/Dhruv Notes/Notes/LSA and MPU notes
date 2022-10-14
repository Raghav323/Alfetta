***LSA and MPU notes***

Mpu
Euler angles are obtained from accelerometer and gyroscope.

Euler_angel and mpu_offset stores pitch and yaw values.

Tag : constant pointer pointing to a char array


**Functions defined in mpu6050.c**
Enable_mpu6050 :- enables mpu and returns esp_ok if successful. Works on i2c protocol

Read_mpu6050 :-  reads eugler angle and mpu offset  and returns esp_ok if successful.

Esp_logi :-  Esp_logi works like printf. ESP_LOG(I/W/E) are intended to implement "permanent" logging functionality in the code and is also used in the ESP-IDF itself. 

Display_mpu :- displaying pitch and roll on oled



Xtaskcreate:- freertos function
BaseType_t xTaskCreate(    TaskFunction_t pvTaskCode,
                            const char * const pcName,
                            configSTACK_DEPTH_TYPE usStackDepth,
                            void *pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t *pxCreatedTask
                          );

LSA

Functions:-
Bound:maps a value in range [input lower limit,input higher limit] to [output lower limit, output higher limit]. Declared in utils.h

Map(val,oldmin,oldmax,newmin,newmax) :- maps value bounded by oldmin oldmax to newmin newmax. Linear Proportionality is maintained.

There is a union ( date type like array ) called line_sensor_array defined in lsa.h which enables and configure adc

          
enable_line_sensor():-Defined in lsa.c  . Enables line sensor and returns esp_ok if        successful 

 Read_line_sensor :-returns line sensor readings for 4 pins .Defined as variable of data line_sensor_array. Uses read_adc() written in adc.c

Tag:- constant pointer pointing to a char array

   Esp_logi works like printf . ESP_LOG(I/W/E) are intended to implement "permanent" logging functionality in the code and is also used in the ESP-IDF itself. 

