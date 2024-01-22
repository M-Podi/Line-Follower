# Line Follower Robot - DarkerThanAsphalt - 17.6s

This repository contains the Arduino setup and code for a line follower robot. The robot uses PID control to follow a line and is capable of self-calibration for optimal performance.

## Setup

![Line Follower setup](https://github.com/M-Podi/Line-Follower/assets/114012309/3758c6df-7367-4e03-920e-204fb7cc0cbd)

### Components

To build the Line Follower Robot, you will need the following components:

1. **Arduino Uno**: Serves as the main controller for the robot.
2. **DC Motors (2)**: These motors drive the robot's wheels.
3. **Wheels (2)**: Attached to the DC motors for movement.
4. **L293D Motor Driver**: Interfaces the DC motors with the Arduino Uno.
5. **QTR-8A Reflectance Sensor Array**: Used for line detection.
6. **Power Source**: In this setup, a LiPo battery is used.
7. **Chassis**: The base structure to which all components are attached.
8. **Ball Caster**: Provides support and balance to the robot.
9. **Breadboard**: Used for assembling the circuit.
10. **Wires**: To connect the components.
11. **Zip-ties**: For securing components to the chassis.
12. **Screws**: For mounting the QTR-8A reflectance sensor.

### Circuit View

Below is the circuit diagram of the Line Follower Robot:

![Circuit View](https://github.com/M-Podi/Line-Follower/assets/114012309/5fecd379-6ca1-4202-a485-d3e7b81b9a5b)


## How to Use
1. **Assemble the Robot**: Attach the motors to the chassis, connect the wheels, and mount the Arduino and sensor array.
2. **Wiring**: Follow the circuit view to connect motors to the motor driver, the motor driver to the Arduino, and the QTR sensor array to the Arduino.
3. **Upload Code**: Connect the Arduino to your computer, open the provided code in Arduino IDE, and upload it to the Arduino board.
4. **Calibrate Sensors**: Place the robot on the track, power it on, and allow it to calibrate its sensors. The built-in LED indicates the calibration mode.
5. **Start the Robot**: Once calibration is complete, the robot will start following the line.


## Functions Description

<details>
<summary> </summary>

### calibration()
**Purpose**: Manages the calibration process of the robot.

**Description**: This function swaps the speeds of the two motors and constrains them within a specified range. It is called at regular intervals based on calibrationTime to ensure the robot's sensors are accurately calibrated for optimal line detection.

### setup()
**Purpose**: Initializes the robot's hardware and sensors.

**Description**: Sets up the motor control pins, initializes the QTR sensors, performs a preliminary sensor calibration, and establishes the serial communication. It also blinks the built-in LED to indicate calibration mode.

### loop()
**Purpose**: The main control loop for the robot.

**Description**: Continuously reads sensor values and calculates the error for line tracking. It also executes the PID control by adjusting motor speeds based on this error.

### setMotorSpeed(int motor1Speed, int motor2Speed)
**Purpose**: Controls the speed and direction of the motors.

**Description**: Takes the desired speed for each motor and applies it, including handling the direction of rotation. It ensures that if a motor is set to 0 speed, it stops, and if the speed is positive or negative, it sets the rotation direction accordingly.

</details>

## Proof that it worked


https://github.com/M-Podi/Line-Follower/assets/114012309/eba157be-2c82-4c87-be53-6f211740c544


## Project Overview


### Academic Context
This Line Follower Robot project was developed as part of the Introduction to Robotics course at UB-FMI taught by Andrei Dumitriu.

### Team
The project was undertaken by Team "DarkerThanAsphalt", consisting of three participants:
- [Robert Schmidt](https://github.com/Robstoner)
- [Horia Marinescu](https://github.com/Hvdri)
- [Matei Podeanu](https://github.com/M-Pod)

### Achievement
A highlight of this project was finishing the circuit in **17.6 seconds**, showcasing the effectiveness of our PID control algorithm and the precision of our robot's design and calibration.

