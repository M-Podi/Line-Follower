# Line Follower Robot

This repository contains the Arduino setup and code for a line follower robot. The robot uses PID control to follow a line and is capable of self-calibration for optimal performance.

## Setup

### Components
- Arduino Board (e.g., Arduino Uno)
- QTR-8RC Reflectance Sensor Array
- 2x DC Gear Motors
- Motor Driver (e.g., L298N)
- Chassis with wheels
- Battery pack (suitable for motor and Arduino power requirements)
- Jumper wires

### Circuit View


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

### pidControl()
**Purpose**: Implements the PID control logic.

**Description**: Calculates the proportional, integral, and derivative terms based on the current error and the PID constants (kp, ki, kd). It then combines these to compute the overall PID value and applies this value to adjust the motors' speeds.

### applyPIDToMotors(int pidValue)
**Purpose**: Applies the PID value to the motors.

**Description**: Adjusts the speed of each motor based on the PID value while ensuring the speeds are within the defined limits. It calls setMotorSpeed to apply these adjustments.

### setMotorSpeed(int motor1Speed, int motor2Speed)
**Purpose**: Controls the speed and direction of the motors.

**Description**: Takes the desired speed for each motor and applies it, including handling the direction of rotation. It ensures that if a motor is set to 0 speed, it stops, and if the speed is positive or negative, it sets the rotation direction accordingly.

</details>
