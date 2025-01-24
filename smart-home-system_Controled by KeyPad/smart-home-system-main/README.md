Project Description:
Our smart Home System Divided into 2 Parts:
1)Embedded system part 
This part consists of 2 parts:

1.1)security system 
our Home is supported with security system which enabled us for entering to the mode selection system 
you have 3 trials to enter the correct password then you can go to the mode selection system
after failed 3 trials, we enable an alarm for a few seconds using a buzzer and you can go back for trying again. 

1.2)mode selection system
this mode consists of 4 modes:

1.2.1)Air Conditioning mode
If you select this mode, you can control your fan automatically by measuring the temperature of your home using temperature sensor and comparing this value with a critical value, we identify it then 
If the measuring value is greater than the critical value, the fan is turned on automatically and vice versa until the measuring value equals the critical value. 

1.2.2)Safety system mode
You can use this mode when you need to go out and you want to know if any strange person on your home. we enable for you PIR sensor which detect any weird bodies then we notify you using alarm system.

1.2.3)Room system mode
This mode enables you to turn on /off the rooms of your house manually. this we implement this using led for each room.

1.2.4)Fan System mode
This mode enables you to turn on /off the fans of your house manually 

2) IOT part
if you enable your home on this system you can control any system by your smart phone using Blynk application using WIFI module with aid your esp32 MCU.
This system consists of 4 modes
Lightning system
Fan system
Safety system

System Components🏠

1)Embedded system Part:

-Atmega 32 MCU
-LCD 2x16
-Keypad 4x4
-BUZZER
-Fan
-4 LED
-LM 35

2)IOT System part:

-Esp32 
-PIR sensor
-BUZZER
-Fan
-Lightning system

