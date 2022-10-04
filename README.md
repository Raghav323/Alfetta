
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

* [ESP_IDF]()
* [FreeRTOS](https://www.freertos.org/a00104.html)
* [SRA_Components](https://github.com/SRA-VJTI/Wall-E/tree/master/components)
* Windows 7 or later (64-bit), Ubuntu 20.04 or later
* [Microsoft VS Code](https://code.visualstudio.com/download)

## Installation
Clone the repo

` git clone https://github.com/Raghav323/Alfetta 

## Usage
Once the requirements are satisfied, you can easily download the project and use it on your machine.

1) First navigate to the folder Alfetta 
2) Navigate to Self_and_line folder using cd self_and_line
3) Connect one end of the cable to your laptop and the other end to ESP32.
5) Execute command idf.py build on terminal . 
6) Execute command idf.py flash monitor on terminal .

