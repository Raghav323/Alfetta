
# Table of Contents

- [Alfetta](#sketch-2-paint)
  - [Table of Contents](#table-of-contents)
- [About The Project](#about-the-project)
  - [Aim](#aim)
  - [Description](#description)
  - [Tech Stack](#tech-stack)
  - [File Structure](#file-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Theory and Approach](#theory-and-approach)
- [Results and Demo](#results-and-demo)
- [Future Works](#future-works)
- [Contributors](#contributors)
- [Acknowledgements and Resources](#acknowledgements-and-resources)
- [License](#license)

# About The Project
<!-- Aim -->
## Aim
* Line following robots may be used in various industrial and domestic applications such as to carry goods, floor cleaning, delivery services and transportation.
* Self balancing two wheeled robot is advantageous over traditional four wheeled robots as it helps in taking sharp turns and navigating through tighter areas
* In this project, we will implement a self balancing and line following robot . 

## Description
* We make use of two sensors , MPU and LSA to provide us with enough data to implement line following and self balancing together . 
* Using Two PID feedback loop , one for self balancing and one for line following , we implement this project . 

## Tech Stack
This section contains the technologies we used for this project.
* Embedded C 
* PID Controller 
* FreeRTOS
* ESP32 


## File Structure 
    ├── Documentation                  # Folder containing pngs explaining the project 
    ├── components                   # SRA components folder         
    ├── self_and_line                   # Source code files
        ├── build
        ├── frontend
          ├── index.html
        ├── main 
          ├── include 
            ├── tuning_http_server.h
            ├── wifi_handler.h
          ├──CmakeLists.txt
          ├──component.mk
          ├──Kconfig
          ├──self_and_line.c
          ├──tuning_http_server.c
          ├──wifi_handler.c
        ├── CmakeLists.txt
        ├──parititon_table.csv
        ├── sdkconfig
        ├── sdkconfig.defaults
        ├── sdkconfig.old
        ├── sdkconfigs
        ├── sdkconfigw  
    ├── LICENSE                  # MIT license
    ├── README.md                # readme.md
# Getting Started 

## Prerequisites
To download and use this code, the minimum requirements are:

* [ESP_IDF](https://github.com/espressif/esp-idf)
* [FreeRTOS](https://www.freertos.org/a00104.html)
* [SRA_Components](https://github.com/SRA-VJTI/Wall-E/tree/master/components)
* Windows 7 or later (64-bit), Ubuntu 20.04 or later
* [Microsoft VS Code](https://code.visualstudio.com/download)

## Installation
Clone the project by typing the following command in your Terminal/CommandPrompt

git clone https://github.com/Raghav323/Alfetta 

cd Alfetta

## Usage
Once the requirements are satisfied, you can easily download the project and use it on your machine.
After following the above steps , use the following commands to:

Build
```
idf.py build
```
Flash
```
idf.py -p (PORT) flash monitor
```
Configuration

```
idf.py menuconfig
```

## Theory and Approach
Refer [this](/NOTES/) for more info . 
* The main motto of this project is to implement a **line following** and **self balancing robot** . 
* We use **ESP-IDFs** (Espressif's official IoT Development Framework) **ESP32** as the main microcontroller for this task . 
* **MPU6050** is a Micro Electro-mechanical system (MEMS), it consists of three-axis accelerometer and three-axis gyroscope. It helps us to measure velocity, orientation, acceleration, displacement and other motion like features. This provides us with critical info that is required for balancing .
* **Line sensors** detect the presence of a black line by emitting infrared (IR) light and detecting the light levels that return to the sensor. We use 4 line sensor arrays to detect turns and move using PID accordingly by subtracting and adding line following correction to motors . 
* For implementing both self balancing and line following , we use **2 PIDs** , one gives us the required duty cycle for balancing , the other gives us correction by which a motor should be accelerated and the other should be decelerated to follow the line .Positive correction implies that the right motor should be accelerating (bot should move left) that is bot is towards right of line while negative correction means left motor should be accelerating (bot should move right). 
* After getting these corrections , we make some decisions using conditional if-else statements . 
* Our first decision is to see if the pitch error that is (setpoint - pitch_angle) is positive or negative . If it is positive means our bot is above the desired position for self balancing and we move it backwards so that it tilts forward by pseduo forces. If it is negative means our bot is below the desired position for self balancing and we move it forwards so that it tilts backward by pseudo forces . The negative pitch error state is the desired state as ideally we want our bot to only move forwards for line following . 
* Now coming to the speed with which we move it backwards and forwards . 

```
left_duty_cycle = self_balancing_correction - line_correction 
right_duty_cycle= self_balancing_correction + line_correction
```

* While moving it backwards , we want it to move in such a way that it is still facing the line and also getting enough pwm for balancing . We do this by providing the right motor pwm to left motor and vice-versa . While moving it forwards , we provide the normal left and right duty cycles as mentioned above 

## Results and Demo
This is the final output of our project . The self balancing and line following algorithm is still not perfect . The bot still touches the ground at occasions which is not ideal for a self balancing bot . 

https://user-images.githubusercontent.com/111511248/194223248-77d15f45-b21e-482c-922c-cc45c4c83eca.mp4

## Future Works
* The following developments are yet to be achieved
- [ ] Fine Tuning the PID for better results 
- [ ] Improving the Self-Balancing and Line-Following Algorithm 
- [ ] Adding Power Source to make bot work wirelessly
- [ ] Improving Design of Robot for better self balancing

## Contributors 

* [Raghav Agarwal](https://github.com/Raghav323)
* [Dhruv Sapra](https://github.com/Dhruv-Sapra)

# Acknowledgements and Resources
* [SRA VJTI](https://www.sravjti.in/) Eklavya 2021  
* Referred [this](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) for ESP32 API
* Referred [this](https://www.google.com/search?channel=fs&client=ubuntu&q=PID+without+a+PHD) for understanding PID.
* Special Thanks to our awesome mentor [Mateen Shah](https://github.com/Jamm02) who always helped us during our project journey.
