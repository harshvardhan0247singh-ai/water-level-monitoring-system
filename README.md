# Water Level Monitoring System

An Arduino-based water level monitoring system designed to measure and display the amount of liquid present in containers with varying dimensions.

## Overview

The system uses an ultrasonic sensor to measure the distance between the sensor and the water surface. Based on the measured distance and the configured container height, the system calculates the water level and displays the result on a 16×2 I2C LCD.

The container height can be adjusted using push buttons, allowing the system to work with containers of different dimensions.

## Features

- Non-contact water-level measurement using an HC-SR04 ultrasonic sensor
- Configurable container height
- Water-level calculation based on sensor readings
- Water-level percentage display
- 16×2 I2C LCD output
- Servo-controlled lid mechanism
- Multiple ultrasonic readings averaged for more stable measurements

## Components Used

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- 16×2 I2C LCD
- SG90 Servo Motor
- Push Buttons
- 7.4V Li-ion Battery
- Supporting wiring and enclosure

## Working

1. The HC-SR04 ultrasonic sensor measures the distance from the sensor to the water surface.
2. Multiple readings are taken and averaged to obtain a more stable measurement.
3. The system uses the configured container height to determine the water level.
4. The water level is converted into a percentage of the container height.
5. The calculated values are displayed on the LCD.
6. Push buttons allow the container height to be adjusted.
7. Both buttons can also be used to control the servo-operated lid.

## Software

- Arduino IDE
- C/C++ (Arduino programming environment)

## Team & My Role

This project was developed as a team of three members, with me serving as the team leader.

As the team leader, I was primarily responsible for the system design, hardware component selection and arrangement, sensor and button integration, Arduino implementation, testing, and project documentation. I also coordinated the overall development of the project with the other team members.

## What I Learned
- Working with an Arduino Uno
- Interfacing an ultrasonic sensor
- Reading and processing sensor measurements
- Working with an I2C LCD
- Using push buttons as user inputs
- Controlling a servo motor
- Understanding basic hardware-software integration
- Developing and testing an embedded-system prototype

## Project Images
<img width="3456" height="4608" alt="IMG_20251117_110703_851" src="https://github.com/user-attachments/assets/b31c0f65-2107-407a-8d51-47b186a17745" />
<img width="3456" height="4608" alt="IMG_20251117_125454_291" src="https://github.com/user-attachments/assets/205a8e67-7182-4521-bb55-7316b96510dd" />
<img width="3456" height="4608" alt="IMG_20251124_005529_968" src="https://github.com/user-attachments/assets/c160313d-8ec9-4af8-afbe-74237d57baaf" />


## Future Improvements
Possible improvements include:
- Improving measurement reliability under different environmental conditions
- Adding data logging
- Adding wireless monitoring
- Improving the physical enclosure
- Developing a more flexible configuration system

## Author
Harshvardhan
B.Tech Computer Science & Engineering
Lovely Professional University

