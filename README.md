# Banjir
“Si-Banjir: IoT-Based Flood Early Warning System” is an innovation motivated by 
the fact that there are still many areas and people in Indonesia that are still being hit 
by floods. The use of technology should be able to reduce the effects caused by the 
flood disaster. Therefore, we created an innovation entitled“Si-Banjir: IoT-Based 
Flood Early Warning System” as an effort to minimize the adverse effects caused 
by flood disasters.

Project Explanation
This tool system consists of two parts. Hardware and Software. To find out 
the water level, this tool uses a waterproof ultrasonic sensor which is in accordance 
with industrial needs with the ability to detect up to 6m, Si-Flood is also equipped 
with a water speed sensor, besides distance and water speed sensors, Si-Flood is 
equipped with GPS to display location data, p. it aims to find flood points on maps, 
data from measurements are processed using STM32 and connected to a portable 
Wifi/Mifi network. The output of this tool is in the form of water level data and the 
the location where the device is installed, in the form of an LCD display on the panel 
box and a smartphone application. The main feature of this tool application is that 
it can display flood locations, measure water level and speed, and predict whether it will 
flood or not, and send notifications to WhatsApp or Telegram.

![image](https://github.com/Azhar14/Banjir/assets/43295093/4628ceb0-68a1-4512-893e-c92fedde0655)

Explanation:
1. User Determines Water Level Setpoint
2. Water Level and Speed Sensors Working
3. Working GPS determines the coordinates of the Si-Flood location
4. If the water level exceeds the Setpoint, the led indicator on the Si-Sein will 
light up, and the status on the application will be Flood. If not then the 
status will show No Flood.
5. Data results from sensors and GPS will be sent to smartphone applications 
via the internet network.
6. App will show Sensor and GPS data

![image](https://github.com/Azhar14/Banjir/assets/43295093/0d8faac3-8f46-4f7b-be17-1b35686540a3)

In the picture above there is the Internet Of Things architecture that we 
use, here is the explanation:
● Si-Flood Sending and receiving data via the Internet network (Mifi).

● Data from Si-Banjir is stored using a database from Firebase

● Then the data is sent to the smartphone via the Internet network

● The application on the Smartphone displays data from the Si-Flood tool.

The following is a prototype of the IoT-Based Early Warning System that 
we have made, the dimensions of this tool are 130 cm in length and the 
dimensions of the solar panel are 35 x 25 cm

![image](https://github.com/Azhar14/Banjir/assets/43295093/6cf4e6ab-98c5-4089-85c0-d2aed1556cef)

The advantages of the tools we make, compared to existing ones, are that 
they are more compact (smaller), support renewable energy with power systems 
using solar panels and applications that can monitor location, water level, and water 
speed in real-time.

![image](https://github.com/Azhar14/Banjir/assets/43295093/bc64f495-bd2b-47d4-a0bf-dc7959283cab)

The services we provide are in the form of an application that can monitor 
and display the location of the device installed, besides that, the user can adjust the 
height of the sensor measurement based on the input threshold, this is useful if the 
the sensor is not parallel to the ground the user does not have to raise or lower the 
sensor, only through the application only the user can set sensor measurements.

Here's a look at the application we've made:

![image](https://github.com/Azhar14/Banjir/assets/43295093/bdb7b061-2a1d-41bf-8b65-42d086aa7399)

The main menu consists of information on GPS data, sensor readings of 
height and water speed and is equipped with a status indicator for flooding 
or not flooding.

● The Settings menu consists of logging data graphs from the water level 
readings with a time range of once every 3 seconds, at the bottom there is 
a slider to set the desired threshold.
In this research we used the method of preliminary study, making 
technological designs, tool production processes, constraint testing, and evaluation.

● Tool Testing
In the early stages of the prototype, we conducted several tests in two 
different places, the first we tested in the river and the second on a bucket and 
a water hose.

![image](https://github.com/Azhar14/Banjir/assets/43295093/124c8031-2d9f-4391-9007-b71f6de8da1a)

The following are the results of testing the water speed sensor readings on 
the time of sending data between the tool and the smartphone.

![image](https://github.com/Azhar14/Banjir/assets/43295093/76fe56cb-e3bc-4a74-9242-5a8ac931d09a)

To test the water level sensor, we do it directly in the river, using a measuring tape 
as a comparison.

![image](https://github.com/Azhar14/Banjir/assets/43295093/829f849b-c97f-4872-940d-fce6c4fcf924)

The following are the results of the Water Sensor Accuracy Test, a 
comparison of meter gauges and ultrasonic sensors:

![image](https://github.com/Azhar14/Banjir/assets/43295093/9fa85af9-408c-43fe-9a00-48ccba74638b)







