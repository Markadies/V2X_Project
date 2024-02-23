
# Introduction
V2V communication is one of the recent technologies in modern day cars. It's a technology that makes roads safer and makes cars more reliable. It allows cars to communicate with each other, and with the infrastructure around them. This project aims at implementing a V2V communication system, and using it to implement some use-cases.

# Project Description
This project aims at implementing three use-cases for V2V communication. The first use-case is called Overtaking Vehicle Warning, The second use-case is Cooperative Emergency Brake Assistance and third use-case is Co-operative Glare Reduction.
## Overtaking Vehicle Warning 
vehicles can communicate their intent to overtake, provide realtime updates on their position and speed, and receive
notifications from surrounding vehicles.

## Cooperative Emergency Brake Assistance
Consider the following scenario:

![Emergency braking](https://github.com/Markadies/V2V_Project/assets/105671159/fd190ad4-c281-4fec-9586-feaff2f321e9)

If Red Car hard brakes, Blue Car has a chance to see it and avoid a collision, but there is a very big risk that yellow Car will respond when it's too late and an crash happens. V2V communication would be useful in this case, since Red Car will automatically send a warning message/indicator to both Yellow and Blue Cars when the speed drops dramatically.

## Co-operative Glare Reduction
This use case enables a capable vehicle to automatically switch from high beams to low beams when detecting a vehicle arriving in the opposite direction.


![High beam](https://github.com/Markadies/V2V_Project/assets/105671159/3a3c9406-1735-4e63-8b78-ff8ea37155e8)

# Hardware Used
Main MCU: stm32f446re

Wireless Module: esp8266

GPS: Neo m8n

Speed Sensor: LM393

Display: LCD Display

Control: Through an android app and bluetooth

Bluetooth: HC-05

Showcased on an RC car.
# Additional Documentation
Drive : https://drive.google.com/drive/folders/1nebVVTy2VRCJ-NF3PGbqPUDHoXjTnorL?usp=drive_link

Slides : https://docs.google.com/presentation/d/1J0bNqVI_JlAhHnhn6w28LNjJr5SJ-hBG/edit?usp=sharing&ouid=111720471842626202523&rtpof=true&sd=true
