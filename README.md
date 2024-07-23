

# Introduction
V2X communication is one of the recent technologies in modern day cars. It's a technology that makes roads safer and makes cars more reliable. It allows cars to communicate with each other, and with the infrastructure around them. This project aims at implementing a V2X communication system, and using it to implement some use-cases.

Project main focus: Embedded SW Development || Automotive || IOT. 

Technologies : ARM | LINUX | ML | Computer vision | MQTT | RTOS | ROS2

# Project Description
This project aims at implementing three use-cases for V2X communication. The first use-case is called Overtaking Vehicle Warning, The second use-case is Cooperative Emergency Brake Assistance and third use-case is Co-operative Glare Reduction.

## Overtaking Vehicle Warning 
In High ways, vehicles could try to overtake slower vans that is blocking its view which could risk the drivers life due to the possibility of cars moving in opposite direction.

![image](https://github.com/user-attachments/assets/3ff0e4cc-1ed9-46e2-847e-3b933f0468c0)

## Cooperative Emergency Brake Assistance
Consider the following scenario:

![Emergency braking](https://github.com/Markadies/V2V_Project/assets/105671159/fd190ad4-c281-4fec-9586-feaff2f321e9)

If Red Car hard brakes, Blue Car has a chance to see it and avoid a collision, but there is a very big risk that yellow Car will respond when it's too late and an crash happens. V2X communication would be useful in this case, since Red Car will automatically send a warning message/indicator to both Yellow and Blue Cars when the speed drops dramatically.

## Co-operative Glare Reduction
This use case enables a capable vehicle to automatically switch from high beams to low beams when detecting a vehicle arriving in the opposite direction
that reports high light beam blinding the driver.

![High beam](https://github.com/Markadies/V2V_Project/assets/105671159/3a3c9406-1735-4e63-8b78-ff8ea37155e8)

# Hardware Used
Main MCU: stm32f446re

Wireless Module: ESP32

High level Control : Raspberry pi

Sensors: GPS | IMU | TSL2561 | BLE | Buzzer | speed sensors | LCD 20*4 with I2C module | motors with H-bridges | Ultrasonic 
 
Control: Through an android app with HC-05 bluetooth

Showcased on an 2 RC cars

# Additional Documentation
Book : https://drive.google.com/file/d/1ooKx2NT_Y66dZ8iP0fNLw9vi7KBfpxvX/view?usp=sharing%20%20%20

Drive : https://drive.google.com/drive/folders/1nebVVTy2VRCJ-NF3PGbqPUDHoXjTnorL?usp=drive_link

Presentation : [https://docs.google.com/presentation/d/1J0bNqVI_JlAhHnhn6w28LNjJr5SJ-hBG/edit?usp=sharing&ouid=111720471842626202523&rtpof=true&sd=true](https://drive.google.com/file/d/144QHh1AOpUGU9hrKvCKPQeFpyKUzazmz/view)
