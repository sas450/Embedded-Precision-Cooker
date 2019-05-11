# SousVide Project

What is Sous Vide Cooking and Why?

https://www.seriouseats.com/2015/06/food-lab-complete-guide-to-sous-vide-steak.html

Step 1. 
Build the Diode Temperature Sensor

Step 2. 
Turn a switch on and off using the arduino 


Step 1 in more Detail
<br/>Based off of the fact that for every degree change above the ambient temperature there is a 2.2 mV drop across the diode. So if the ambient temperature is known, as well as the voltage at the anode (which is read in the arduino analogRead pin), then the current temp can be worked out. 

Step 2. - Reverse Engineer an RF Signal
<br/>Went with a remote controlled switch, because didn't want to mess around with high voltages

<br/><br/>Got a 433 Mhz transciever and hooked up the data pin of that to an oscilloscope. After pulsing the on and off signals, I found 4 Types of Signals 

<br/>100 uS short high 	1
<br/>500 uS long low	2
<br/>400uS-500 uS Pulse long high 	3
<br/>200us medium low followed by the long high 	4

<br/>Transcribed the On Signal
<br/>1	2	1	2	3	4	1	2	1	2	1	2	1	2	1	2	3	4	1	2	1	2	1	2	3	4	1	2	3	4	1	2	3	4	3	4	1	2	3	4	(3	4)	3	4	1	2	1	2	1	0

<br/>Transcribed Off Signal
<br/>1	2	1	2	3	4	1	2	1	2	1	2	1	2	1	2	3	4	1	2	1	2	1	2	3	4	1	2	3	4	1	2	3	4	3	4	1	2	3	4	(1 2)	3	4	1	2	1	2	1	0

<br/>1 is always followed by 2 
<br/>3 is always followed by 4

<br/>Also the only bits that are different (in paranthesis) are 3,4 for on and 1,2 on 

<br/>Therefore I came up with the encoding that 
<br/>if a 1 is followed by a 2 then its = 0
<br/>if a 3 is followed by a 4 then its = 1

<br/>On Sequence 00100000100010101101(1)1000
<br/>Off Sequence 00100000100010101101(0)1000




