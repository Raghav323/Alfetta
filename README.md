
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

