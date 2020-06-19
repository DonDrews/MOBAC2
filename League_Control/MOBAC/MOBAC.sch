EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L nucleof042k6:NucleoF042K6 U1
U 1 1 5EE85A81
P 6750 3350
F 0 "U1" H 6750 4417 50  0000 C CNN
F 1 "NucleoF042K6" H 6750 4326 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6750 2050 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6900 3500 50  0001 C CNN
	1    6750 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B J?
U 1 1 5EE86F99
P 5050 2650
F 0 "J?" H 4820 2639 50  0000 R CNN
F 1 "USB_B" H 4820 2548 50  0000 R CNN
F 2 "" H 5200 2600 50  0001 C CNN
F 3 " ~" H 5200 2600 50  0001 C CNN
	1    5050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2450 5650 2450
Wire Wire Line
	5650 2450 5650 2050
$Comp
L power:VDD #PWR?
U 1 1 5EE88572
P 5650 2050
F 0 "#PWR?" H 5650 1900 50  0001 C CNN
F 1 "VDD" H 5665 2223 50  0000 C CNN
F 2 "" H 5650 2050 50  0001 C CNN
F 3 "" H 5650 2050 50  0001 C CNN
	1    5650 2050
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EE8B262
P 5050 3050
F 0 "#PWR?" H 5050 2800 50  0001 C CNN
F 1 "GND" H 5055 2877 50  0000 C CNN
F 2 "" H 5050 3050 50  0001 C CNN
F 3 "" H 5050 3050 50  0001 C CNN
	1    5050 3050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5EE8BF8A
P 7700 2500
F 0 "#PWR?" H 7700 2350 50  0001 C CNN
F 1 "VDD" H 7715 2673 50  0000 C CNN
F 2 "" H 7700 2500 50  0001 C CNN
F 3 "" H 7700 2500 50  0001 C CNN
	1    7700 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 2500 7700 2700
Wire Wire Line
	7700 2700 7250 2700
Wire Wire Line
	7700 2700 7700 3000
Wire Wire Line
	7700 3000 7250 3000
Connection ~ 7700 2700
$Comp
L nucleof042k6:Joystick JY?
U 1 1 5EE8EF9B
P 9800 3150
F 0 "JY?" H 10028 2996 50  0000 L CNN
F 1 "Joystick" H 10028 2905 50  0000 L CNN
F 2 "" H 9800 3150 50  0001 C CNN
F 3 "" H 9800 3150 50  0001 C CNN
	1    9800 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EE90F1E
P 9300 4200
F 0 "#PWR?" H 9300 3950 50  0001 C CNN
F 1 "GND" H 9305 4027 50  0000 C CNN
F 2 "" H 9300 4200 50  0001 C CNN
F 3 "" H 9300 4200 50  0001 C CNN
	1    9300 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2800 7900 2800
Wire Wire Line
	7900 2800 7900 2900
$Comp
L power:GND #PWR?
U 1 1 5EE918F1
P 7900 2900
F 0 "#PWR?" H 7900 2650 50  0001 C CNN
F 1 "GND" H 7905 2727 50  0000 C CNN
F 2 "" H 7900 2900 50  0001 C CNN
F 3 "" H 7900 2900 50  0001 C CNN
	1    7900 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 3250 9500 3250
NoConn ~ 4950 3050
Wire Wire Line
	5350 2650 5650 2650
Wire Wire Line
	5650 2650 5650 3100
Wire Wire Line
	5650 3100 6250 3100
Wire Wire Line
	5350 2750 5550 2750
Wire Wire Line
	5550 2750 5550 3900
Wire Wire Line
	5550 3900 6250 3900
Text HLabel 7250 3800 2    50   Input ~ 0
SW_Q
Text HLabel 7250 3700 2    50   Input ~ 0
SW_W
Text HLabel 7250 3600 2    50   Input ~ 0
SW_E
Text HLabel 7250 3500 2    50   Input ~ 0
SW_R
Text HLabel 6250 2700 0    50   Input ~ 0
SUMM1
Text HLabel 6250 2800 0    50   Input ~ 0
SUMM2
Text HLabel 6250 3200 0    50   Input ~ 0
ITM1
Text HLabel 6250 3300 0    50   Input ~ 0
ITM2
Text HLabel 6250 3400 0    50   Input ~ 0
ITM3
Text HLabel 6250 3500 0    50   Input ~ 0
WRD
Text HLabel 6250 3600 0    50   Input ~ 0
RCL
Text HLabel 6250 3700 0    50   Input ~ 0
SHP
Text HLabel 6250 3800 0    50   Input ~ 0
PS
Text HLabel 6250 4000 0    50   Input ~ 0
QCK_TOG
Text HLabel 6250 4100 0    50   Input ~ 0
R_CLICK
Text HLabel 7250 4100 2    50   Input ~ 0
CAM_TOG
Wire Wire Line
	9300 3250 9300 4200
Wire Wire Line
	9500 3350 9400 3350
Wire Wire Line
	9400 3350 9400 4000
Wire Wire Line
	9400 4000 7250 4000
Wire Wire Line
	7850 3650 7850 3400
Wire Wire Line
	7850 3400 7250 3400
Wire Wire Line
	7850 3650 9500 3650
Wire Wire Line
	7950 3550 7950 3300
Wire Wire Line
	7950 3300 7250 3300
Wire Wire Line
	7950 3550 9500 3550
Wire Wire Line
	8050 3450 8050 3200
Wire Wire Line
	8050 3200 7250 3200
Wire Wire Line
	8050 3450 9500 3450
$EndSCHEMATC
