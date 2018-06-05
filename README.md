# Autonomous Human Following Robot
______
### Northwestern University
### Kaiyang Zheng
------
## Intro ##
______
The goal of this project is to design a robot which follows its user. The
autonomous human following robot could be applied to multiple areas. For instance,
a smart luggage that follows a traveler helps relieve stress, and the same idea
could also be applied to robotics pets. Who doesn't want a robotic dog?
## Platform ##
______
The carrying robot is a four wheel robot with a high torque motor attached to
each wheel. The turning mechanism is based on differential drive. In this design,
when the four wheels rotate in the same direction, the robot moves forward, and
when two sides of the wheels rotate in the opposite direction, the robot either
turn to the left or the right.   

The control unit in this system is a pic32 micro processor. One HC05 bluetooth module is 
used to receive command from a master(laptop or smartphone) in real time. 

The distance sensor is VL6180 from sparkfun, and the code in this project is derived from its arduino library.

## Real time control algorithm ##
______
The TX pin of the HC-05 bluetooth module is connected to the RX interrupt on the pic32 module. Everytime the HC-05 
module receives a command, the robot reacts with a corresponding reaction. 

Once the robot receives the autonomous command from the master, the distance sensor interrupt starts checking the distance 
in front of the robot. When the distance falls below a threshold, the robot rotates to the left with a little angle, then rotates 
to the right and compare the two distances. Then the robot goes in the direction with a longer distance reading. This ensures 
the robot finds the most realiable way to avoid collision. 


