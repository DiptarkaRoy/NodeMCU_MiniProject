# Smart Water Level Indicator with Automatic Pumping Action
>The above Mini Project is a project I along with my team consisting of Moulindu Mandal, Aishwarya and me took as part of our mandatory 2nd Year B.Tech. Course Curriculum.
>In the Mini Project, we tried to solve the problem of water wastage in Indian Households by automating the process of water pumping. And also created an IoT interface that will >show Water Level Data to the user through WiFi.

In this project we have used NodeMCU instead of the more popular Arduino because of its WiFi capabilities. The project has two water level sensors which tells the MCU if the water level is too high or too low and therefore leading to the MCU turning OFF or ON the motor respectively. However, if the water level is at an intermediate level, then the user can use the IoT interface to turn ON or OFF the motor.

### Steps to Run this Project:
1. Open Arduino IDE.
2. Follow this tutorial for setting up your Arduino IDE for NodeMCU:   https://www.instructables.com/How-to-Program-NodeMCU-on-Arduino-IDE/
3. Make the correct connections in the circuit.
4. Connect your PC to NodeMCU using appropriate USB cable.
5. Copy and Paste the file NodeMCUcode.c in your Arduino.
6. Click on the `Upload` button.
