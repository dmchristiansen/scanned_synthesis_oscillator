EESchema Schematic File Version 4
LIBS:FDM-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L Amplifier_Operational:MCP6004 IC2
U 1 1 5CA97CCE
P 3150 2300
F 0 "IC2" H 3150 1933 50  0000 C CNN
F 1 "MCP6004" H 3150 2024 50  0000 C CNN
F 2 "" H 3100 2400 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 3200 2500 50  0001 C CNN
	1    3150 2300
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R2
U 1 1 5CA97F09
P 2400 2200
F 0 "R2" V 2195 2200 50  0000 C CNN
F 1 "100k" V 2286 2200 50  0000 C CNN
F 2 "" V 2440 2190 50  0001 C CNN
F 3 "~" H 2400 2200 50  0001 C CNN
	1    2400 2200
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R7
U 1 1 5CA97F8E
P 3150 1700
F 0 "R7" V 2945 1700 50  0000 C CNN
F 1 "33k" V 3036 1700 50  0000 C CNN
F 2 "" V 3190 1690 50  0001 C CNN
F 3 "~" H 3150 1700 50  0001 C CNN
	1    3150 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R1
U 1 1 5CA97FEB
P 2400 1450
F 0 "R1" V 2195 1450 50  0000 C CNN
F 1 "200k" V 2286 1450 50  0000 C CNN
F 2 "" V 2440 1440 50  0001 C CNN
F 3 "~" H 2400 1450 50  0001 C CNN
	1    2400 1450
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5CA98121
P 3150 1350
F 0 "C1" V 2898 1350 50  0000 C CNN
F 1 "3n3" V 2989 1350 50  0000 C CNN
F 2 "" H 3188 1200 50  0001 C CNN
F 3 "~" H 3150 1350 50  0001 C CNN
	1    3150 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 1450 1900 1450
Wire Wire Line
	2550 2200 2800 2200
Wire Wire Line
	3450 2300 3500 2300
Wire Wire Line
	3500 2300 3500 1700
Wire Wire Line
	3500 1700 3300 1700
Wire Wire Line
	3500 1700 3500 1350
Wire Wire Line
	3500 1350 3300 1350
Connection ~ 3500 1700
Wire Wire Line
	3000 1350 2800 1350
Wire Wire Line
	2800 1350 2800 1450
Connection ~ 2800 2200
Wire Wire Line
	2800 2200 2850 2200
Wire Wire Line
	3000 1700 2800 1700
Connection ~ 2800 1700
Wire Wire Line
	2800 1700 2800 2200
Wire Wire Line
	2550 1450 2800 1450
Connection ~ 2800 1450
Wire Wire Line
	2800 1450 2800 1700
$Comp
L power:GND #PWR0104
U 1 1 5CA98515
P 2050 2500
F 0 "#PWR0104" H 2050 2250 50  0001 C CNN
F 1 "GND" H 2055 2327 50  0000 C CNN
F 2 "" H 2050 2500 50  0001 C CNN
F 3 "" H 2050 2500 50  0001 C CNN
	1    2050 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5CA98549
P 2750 2500
F 0 "#PWR0105" H 2750 2250 50  0001 C CNN
F 1 "GND" H 2755 2327 50  0000 C CNN
F 2 "" H 2750 2500 50  0001 C CNN
F 3 "" H 2750 2500 50  0001 C CNN
	1    2750 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2400 2750 2400
Wire Wire Line
	2750 2400 2750 2500
$Comp
L Amplifier_Operational:MCP6004 IC2
U 2 1 5CAAB615
P 3150 4250
F 0 "IC2" H 3150 3883 50  0000 C CNN
F 1 "MCP6004" H 3150 3974 50  0000 C CNN
F 2 "" H 3100 4350 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 3200 4450 50  0001 C CNN
	2    3150 4250
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R4
U 1 1 5CAAB61B
P 2400 4150
F 0 "R4" V 2195 4150 50  0000 C CNN
F 1 "100k" V 2286 4150 50  0000 C CNN
F 2 "" V 2440 4140 50  0001 C CNN
F 3 "~" H 2400 4150 50  0001 C CNN
	1    2400 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R8
U 1 1 5CAAB621
P 3150 3650
F 0 "R8" V 2945 3650 50  0000 C CNN
F 1 "33k" V 3036 3650 50  0000 C CNN
F 2 "" V 3190 3640 50  0001 C CNN
F 3 "~" H 3150 3650 50  0001 C CNN
	1    3150 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R3
U 1 1 5CAAB627
P 2400 3400
F 0 "R3" V 2195 3400 50  0000 C CNN
F 1 "200k" V 2286 3400 50  0000 C CNN
F 2 "" V 2440 3390 50  0001 C CNN
F 3 "~" H 2400 3400 50  0001 C CNN
	1    2400 3400
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5CAAB62D
P 3150 3300
F 0 "C2" V 2898 3300 50  0000 C CNN
F 1 "3n3" V 2989 3300 50  0000 C CNN
F 2 "" H 3188 3150 50  0001 C CNN
F 3 "~" H 3150 3300 50  0001 C CNN
	1    3150 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 3400 1900 3400
Wire Wire Line
	1950 4150 2250 4150
Wire Wire Line
	2550 4150 2800 4150
Wire Wire Line
	3450 4250 3500 4250
Wire Wire Line
	3500 4250 3500 3650
Wire Wire Line
	3500 3650 3300 3650
Wire Wire Line
	3500 3650 3500 3300
Wire Wire Line
	3500 3300 3300 3300
Connection ~ 3500 3650
Wire Wire Line
	3000 3300 2800 3300
Wire Wire Line
	2800 3300 2800 3400
Connection ~ 2800 4150
Wire Wire Line
	2800 4150 2850 4150
Wire Wire Line
	3000 3650 2800 3650
Connection ~ 2800 3650
Wire Wire Line
	2800 3650 2800 4150
Wire Wire Line
	2550 3400 2800 3400
Connection ~ 2800 3400
Wire Wire Line
	2800 3400 2800 3650
$Comp
L power:GND #PWR0106
U 1 1 5CAAB646
P 2050 4450
F 0 "#PWR0106" H 2050 4200 50  0001 C CNN
F 1 "GND" H 2055 4277 50  0000 C CNN
F 2 "" H 2050 4450 50  0001 C CNN
F 3 "" H 2050 4450 50  0001 C CNN
	1    2050 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5CAAB64C
P 2750 4450
F 0 "#PWR0107" H 2750 4200 50  0001 C CNN
F 1 "GND" H 2755 4277 50  0000 C CNN
F 2 "" H 2750 4450 50  0001 C CNN
F 3 "" H 2750 4450 50  0001 C CNN
	1    2750 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 4350 2050 4350
Wire Wire Line
	2050 4350 2050 4450
Wire Wire Line
	2850 4350 2750 4350
Wire Wire Line
	2750 4350 2750 4450
$Comp
L Amplifier_Operational:MCP6004 IC2
U 3 1 5CAABFC5
P 3150 6100
F 0 "IC2" H 3150 5733 50  0000 C CNN
F 1 "MCP6004" H 3150 5824 50  0000 C CNN
F 2 "" H 3100 6200 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 3200 6300 50  0001 C CNN
	3    3150 6100
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R6
U 1 1 5CAABFCC
P 2400 6000
F 0 "R6" V 2195 6000 50  0000 C CNN
F 1 "100k" V 2286 6000 50  0000 C CNN
F 2 "" V 2440 5990 50  0001 C CNN
F 3 "~" H 2400 6000 50  0001 C CNN
	1    2400 6000
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R9
U 1 1 5CAABFD3
P 3150 5500
F 0 "R9" V 2945 5500 50  0000 C CNN
F 1 "33k" V 3036 5500 50  0000 C CNN
F 2 "" V 3190 5490 50  0001 C CNN
F 3 "~" H 3150 5500 50  0001 C CNN
	1    3150 5500
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R5
U 1 1 5CAABFDA
P 2400 5250
F 0 "R5" V 2195 5250 50  0000 C CNN
F 1 "200k" V 2286 5250 50  0000 C CNN
F 2 "" V 2440 5240 50  0001 C CNN
F 3 "~" H 2400 5250 50  0001 C CNN
	1    2400 5250
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 5CAABFE1
P 3150 5150
F 0 "C3" V 2898 5150 50  0000 C CNN
F 1 "3n3" V 2989 5150 50  0000 C CNN
F 2 "" H 3188 5000 50  0001 C CNN
F 3 "~" H 3150 5150 50  0001 C CNN
	1    3150 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 5250 1900 5250
Wire Wire Line
	1950 6000 2250 6000
Wire Wire Line
	2550 6000 2800 6000
Wire Wire Line
	3450 6100 3500 6100
Wire Wire Line
	3500 6100 3500 5500
Wire Wire Line
	3500 5500 3300 5500
Wire Wire Line
	3500 5500 3500 5150
Wire Wire Line
	3500 5150 3300 5150
Connection ~ 3500 5500
Wire Wire Line
	3000 5150 2800 5150
Wire Wire Line
	2800 5150 2800 5250
Connection ~ 2800 6000
Wire Wire Line
	2800 6000 2850 6000
Wire Wire Line
	3000 5500 2800 5500
Connection ~ 2800 5500
Wire Wire Line
	2800 5500 2800 6000
Wire Wire Line
	2550 5250 2800 5250
Connection ~ 2800 5250
Wire Wire Line
	2800 5250 2800 5500
$Comp
L power:GND #PWR0108
U 1 1 5CAABFFB
P 2050 6300
F 0 "#PWR0108" H 2050 6050 50  0001 C CNN
F 1 "GND" H 2055 6127 50  0000 C CNN
F 2 "" H 2050 6300 50  0001 C CNN
F 3 "" H 2050 6300 50  0001 C CNN
	1    2050 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5CAAC001
P 2750 6300
F 0 "#PWR0109" H 2750 6050 50  0001 C CNN
F 1 "GND" H 2755 6127 50  0000 C CNN
F 2 "" H 2750 6300 50  0001 C CNN
F 3 "" H 2750 6300 50  0001 C CNN
	1    2750 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6200 2050 6200
Wire Wire Line
	2050 6200 2050 6300
Wire Wire Line
	2850 6200 2750 6200
Wire Wire Line
	2750 6200 2750 6300
$Comp
L Amplifier_Operational:MCP6004 IC2
U 4 1 5CAAD000
P 5900 2300
F 0 "IC2" H 5900 1933 50  0000 C CNN
F 1 "MCP6004" H 5900 2024 50  0000 C CNN
F 2 "" H 5850 2400 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 5950 2500 50  0001 C CNN
	4    5900 2300
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R11
U 1 1 5CAAD007
P 5150 2200
F 0 "R11" V 4945 2200 50  0000 C CNN
F 1 "100k" V 5036 2200 50  0000 C CNN
F 2 "" V 5190 2190 50  0001 C CNN
F 3 "~" H 5150 2200 50  0001 C CNN
	1    5150 2200
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R16
U 1 1 5CAAD00E
P 5900 1700
F 0 "R16" V 5695 1700 50  0000 C CNN
F 1 "33k" V 5786 1700 50  0000 C CNN
F 2 "" V 5940 1690 50  0001 C CNN
F 3 "~" H 5900 1700 50  0001 C CNN
	1    5900 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R10
U 1 1 5CAAD015
P 5150 1450
F 0 "R10" V 4945 1450 50  0000 C CNN
F 1 "200k" V 5036 1450 50  0000 C CNN
F 2 "" V 5190 1440 50  0001 C CNN
F 3 "~" H 5150 1450 50  0001 C CNN
	1    5150 1450
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 5CAAD01C
P 5900 1350
F 0 "C4" V 5648 1350 50  0000 C CNN
F 1 "3n3" V 5739 1350 50  0000 C CNN
F 2 "" H 5938 1200 50  0001 C CNN
F 3 "~" H 5900 1350 50  0001 C CNN
	1    5900 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	5000 1450 4650 1450
Wire Wire Line
	4700 2200 5000 2200
Wire Wire Line
	5300 2200 5550 2200
Wire Wire Line
	6200 2300 6250 2300
Wire Wire Line
	6250 2300 6250 1700
Wire Wire Line
	6250 1700 6050 1700
Wire Wire Line
	6250 1700 6250 1350
Wire Wire Line
	6250 1350 6050 1350
Connection ~ 6250 1700
Wire Wire Line
	5750 1350 5550 1350
Wire Wire Line
	5550 1350 5550 1450
Connection ~ 5550 2200
Wire Wire Line
	5550 2200 5600 2200
Wire Wire Line
	5750 1700 5550 1700
Connection ~ 5550 1700
Wire Wire Line
	5550 1700 5550 2200
Wire Wire Line
	5300 1450 5550 1450
Connection ~ 5550 1450
Wire Wire Line
	5550 1450 5550 1700
$Comp
L power:GND #PWR0110
U 1 1 5CAAD036
P 4800 2500
F 0 "#PWR0110" H 4800 2250 50  0001 C CNN
F 1 "GND" H 4805 2327 50  0000 C CNN
F 2 "" H 4800 2500 50  0001 C CNN
F 3 "" H 4800 2500 50  0001 C CNN
	1    4800 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5CAAD03C
P 5500 2500
F 0 "#PWR0111" H 5500 2250 50  0001 C CNN
F 1 "GND" H 5505 2327 50  0000 C CNN
F 2 "" H 5500 2500 50  0001 C CNN
F 3 "" H 5500 2500 50  0001 C CNN
	1    5500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2400 4800 2400
Wire Wire Line
	4800 2400 4800 2500
Wire Wire Line
	5600 2400 5500 2400
Wire Wire Line
	5500 2400 5500 2500
$Comp
L Amplifier_Operational:MCP6004 IC3
U 1 1 5CAAE85C
P 5900 4250
F 0 "IC3" H 5900 3883 50  0000 C CNN
F 1 "MCP6004" H 5900 3974 50  0000 C CNN
F 2 "" H 5850 4350 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 5950 4450 50  0001 C CNN
	1    5900 4250
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R13
U 1 1 5CAAE863
P 5150 4150
F 0 "R13" V 4945 4150 50  0000 C CNN
F 1 "100k" V 5036 4150 50  0000 C CNN
F 2 "" V 5190 4140 50  0001 C CNN
F 3 "~" H 5150 4150 50  0001 C CNN
	1    5150 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R17
U 1 1 5CAAE86A
P 5900 3650
F 0 "R17" V 5695 3650 50  0000 C CNN
F 1 "33k" V 5786 3650 50  0000 C CNN
F 2 "" V 5940 3640 50  0001 C CNN
F 3 "~" H 5900 3650 50  0001 C CNN
	1    5900 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R12
U 1 1 5CAAE871
P 5150 3400
F 0 "R12" V 4945 3400 50  0000 C CNN
F 1 "200k" V 5036 3400 50  0000 C CNN
F 2 "" V 5190 3390 50  0001 C CNN
F 3 "~" H 5150 3400 50  0001 C CNN
	1    5150 3400
	0    1    1    0   
$EndComp
$Comp
L Device:C C5
U 1 1 5CAAE878
P 5900 3300
F 0 "C5" V 5648 3300 50  0000 C CNN
F 1 "3n3" V 5739 3300 50  0000 C CNN
F 2 "" H 5938 3150 50  0001 C CNN
F 3 "~" H 5900 3300 50  0001 C CNN
	1    5900 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	5000 3400 4650 3400
Wire Wire Line
	4700 4150 5000 4150
Wire Wire Line
	5300 4150 5550 4150
Wire Wire Line
	6200 4250 6250 4250
Wire Wire Line
	6250 4250 6250 3650
Wire Wire Line
	6250 3650 6050 3650
Wire Wire Line
	6250 3650 6250 3300
Wire Wire Line
	6250 3300 6050 3300
Connection ~ 6250 3650
Wire Wire Line
	5750 3300 5550 3300
Wire Wire Line
	5550 3300 5550 3400
Connection ~ 5550 4150
Wire Wire Line
	5550 4150 5600 4150
Wire Wire Line
	5750 3650 5550 3650
Connection ~ 5550 3650
Wire Wire Line
	5550 3650 5550 4150
Wire Wire Line
	5300 3400 5550 3400
Connection ~ 5550 3400
Wire Wire Line
	5550 3400 5550 3650
$Comp
L power:GND #PWR0112
U 1 1 5CAAE892
P 4800 4450
F 0 "#PWR0112" H 4800 4200 50  0001 C CNN
F 1 "GND" H 4805 4277 50  0000 C CNN
F 2 "" H 4800 4450 50  0001 C CNN
F 3 "" H 4800 4450 50  0001 C CNN
	1    4800 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5CAAE898
P 5500 4450
F 0 "#PWR0113" H 5500 4200 50  0001 C CNN
F 1 "GND" H 5505 4277 50  0000 C CNN
F 2 "" H 5500 4450 50  0001 C CNN
F 3 "" H 5500 4450 50  0001 C CNN
	1    5500 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 4350 4800 4350
Wire Wire Line
	4800 4350 4800 4450
Wire Wire Line
	5600 4350 5500 4350
Wire Wire Line
	5500 4350 5500 4450
$Comp
L Amplifier_Operational:MCP6004 IC3
U 2 1 5CAB0C3C
P 5900 6100
F 0 "IC3" H 5900 5733 50  0000 C CNN
F 1 "MCP6004" H 5900 5824 50  0000 C CNN
F 2 "" H 5850 6200 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 5950 6300 50  0001 C CNN
	2    5900 6100
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R15
U 1 1 5CAB0C43
P 5150 6000
F 0 "R15" V 4945 6000 50  0000 C CNN
F 1 "100k" V 5036 6000 50  0000 C CNN
F 2 "" V 5190 5990 50  0001 C CNN
F 3 "~" H 5150 6000 50  0001 C CNN
	1    5150 6000
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R18
U 1 1 5CAB0C4A
P 5900 5500
F 0 "R18" V 5695 5500 50  0000 C CNN
F 1 "33k" V 5786 5500 50  0000 C CNN
F 2 "" V 5940 5490 50  0001 C CNN
F 3 "~" H 5900 5500 50  0001 C CNN
	1    5900 5500
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R14
U 1 1 5CAB0C51
P 5150 5250
F 0 "R14" V 4945 5250 50  0000 C CNN
F 1 "200k" V 5036 5250 50  0000 C CNN
F 2 "" V 5190 5240 50  0001 C CNN
F 3 "~" H 5150 5250 50  0001 C CNN
	1    5150 5250
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 5CAB0C58
P 5900 5150
F 0 "C6" V 5648 5150 50  0000 C CNN
F 1 "3n3" V 5739 5150 50  0000 C CNN
F 2 "" H 5938 5000 50  0001 C CNN
F 3 "~" H 5900 5150 50  0001 C CNN
	1    5900 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	5000 5250 4650 5250
Wire Wire Line
	4700 6000 5000 6000
Wire Wire Line
	5300 6000 5550 6000
Wire Wire Line
	6200 6100 6250 6100
Wire Wire Line
	6250 6100 6250 5500
Wire Wire Line
	6250 5500 6050 5500
Wire Wire Line
	6250 5500 6250 5150
Wire Wire Line
	6250 5150 6050 5150
Connection ~ 6250 5500
Wire Wire Line
	5750 5150 5550 5150
Wire Wire Line
	5550 5150 5550 5250
Connection ~ 5550 6000
Wire Wire Line
	5550 6000 5600 6000
Wire Wire Line
	5750 5500 5550 5500
Connection ~ 5550 5500
Wire Wire Line
	5550 5500 5550 6000
Wire Wire Line
	5300 5250 5550 5250
Connection ~ 5550 5250
Wire Wire Line
	5550 5250 5550 5500
$Comp
L power:GND #PWR0114
U 1 1 5CAB0C72
P 4800 6300
F 0 "#PWR0114" H 4800 6050 50  0001 C CNN
F 1 "GND" H 4805 6127 50  0000 C CNN
F 2 "" H 4800 6300 50  0001 C CNN
F 3 "" H 4800 6300 50  0001 C CNN
	1    4800 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5CAB0C78
P 5500 6300
F 0 "#PWR0115" H 5500 6050 50  0001 C CNN
F 1 "GND" H 5505 6127 50  0000 C CNN
F 2 "" H 5500 6300 50  0001 C CNN
F 3 "" H 5500 6300 50  0001 C CNN
	1    5500 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 6200 4800 6200
Wire Wire Line
	4800 6200 4800 6300
Wire Wire Line
	5600 6200 5500 6200
Wire Wire Line
	5500 6200 5500 6300
$Comp
L Amplifier_Operational:MCP6004 IC3
U 3 1 5CAB3FB7
P 8700 2300
F 0 "IC3" H 8700 1933 50  0000 C CNN
F 1 "MCP6004" H 8700 2024 50  0000 C CNN
F 2 "" H 8650 2400 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 8750 2500 50  0001 C CNN
	3    8700 2300
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R20
U 1 1 5CAB3FBE
P 7950 2200
F 0 "R20" V 7745 2200 50  0000 C CNN
F 1 "100k" V 7836 2200 50  0000 C CNN
F 2 "" V 7990 2190 50  0001 C CNN
F 3 "~" H 7950 2200 50  0001 C CNN
	1    7950 2200
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R23
U 1 1 5CAB3FC5
P 8700 1700
F 0 "R23" V 8495 1700 50  0000 C CNN
F 1 "33k" V 8586 1700 50  0000 C CNN
F 2 "" V 8740 1690 50  0001 C CNN
F 3 "~" H 8700 1700 50  0001 C CNN
	1    8700 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R19
U 1 1 5CAB3FCC
P 7950 1450
F 0 "R19" V 7745 1450 50  0000 C CNN
F 1 "200k" V 7836 1450 50  0000 C CNN
F 2 "" V 7990 1440 50  0001 C CNN
F 3 "~" H 7950 1450 50  0001 C CNN
	1    7950 1450
	0    1    1    0   
$EndComp
$Comp
L Device:C C7
U 1 1 5CAB3FD3
P 8700 1350
F 0 "C7" V 8448 1350 50  0000 C CNN
F 1 "3n3" V 8539 1350 50  0000 C CNN
F 2 "" H 8738 1200 50  0001 C CNN
F 3 "~" H 8700 1350 50  0001 C CNN
	1    8700 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 1450 7450 1450
Wire Wire Line
	7500 2200 7800 2200
Wire Wire Line
	8100 2200 8350 2200
Wire Wire Line
	9000 2300 9050 2300
Wire Wire Line
	9050 2300 9050 1700
Wire Wire Line
	9050 1700 8850 1700
Wire Wire Line
	9050 1700 9050 1350
Wire Wire Line
	9050 1350 8850 1350
Connection ~ 9050 1700
Wire Wire Line
	8550 1350 8350 1350
Wire Wire Line
	8350 1350 8350 1450
Connection ~ 8350 2200
Wire Wire Line
	8350 2200 8400 2200
Wire Wire Line
	8550 1700 8350 1700
Connection ~ 8350 1700
Wire Wire Line
	8350 1700 8350 2200
Wire Wire Line
	8100 1450 8350 1450
Connection ~ 8350 1450
Wire Wire Line
	8350 1450 8350 1700
$Comp
L power:GND #PWR0116
U 1 1 5CAB3FED
P 7600 2500
F 0 "#PWR0116" H 7600 2250 50  0001 C CNN
F 1 "GND" H 7605 2327 50  0000 C CNN
F 2 "" H 7600 2500 50  0001 C CNN
F 3 "" H 7600 2500 50  0001 C CNN
	1    7600 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5CAB3FF3
P 8300 2500
F 0 "#PWR0117" H 8300 2250 50  0001 C CNN
F 1 "GND" H 8305 2327 50  0000 C CNN
F 2 "" H 8300 2500 50  0001 C CNN
F 3 "" H 8300 2500 50  0001 C CNN
	1    8300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2400 7600 2400
Wire Wire Line
	7600 2400 7600 2500
Wire Wire Line
	8400 2400 8300 2400
Wire Wire Line
	8300 2400 8300 2500
$Comp
L Amplifier_Operational:MCP6004 IC3
U 4 1 5CABD731
P 8700 4250
F 0 "IC3" H 8700 3883 50  0000 C CNN
F 1 "MCP6004" H 8700 3974 50  0000 C CNN
F 2 "" H 8650 4350 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 8750 4450 50  0001 C CNN
	4    8700 4250
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R22
U 1 1 5CABD738
P 7950 4150
F 0 "R22" V 7745 4150 50  0000 C CNN
F 1 "100k" V 7836 4150 50  0000 C CNN
F 2 "" V 7990 4140 50  0001 C CNN
F 3 "~" H 7950 4150 50  0001 C CNN
	1    7950 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R24
U 1 1 5CABD73F
P 8700 3650
F 0 "R24" V 8495 3650 50  0000 C CNN
F 1 "33k" V 8586 3650 50  0000 C CNN
F 2 "" V 8740 3640 50  0001 C CNN
F 3 "~" H 8700 3650 50  0001 C CNN
	1    8700 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R21
U 1 1 5CABD746
P 7950 3400
F 0 "R21" V 7745 3400 50  0000 C CNN
F 1 "200k" V 7836 3400 50  0000 C CNN
F 2 "" V 7990 3390 50  0001 C CNN
F 3 "~" H 7950 3400 50  0001 C CNN
	1    7950 3400
	0    1    1    0   
$EndComp
$Comp
L Device:C C8
U 1 1 5CABD74D
P 8700 3300
F 0 "C8" V 8448 3300 50  0000 C CNN
F 1 "3n3" V 8539 3300 50  0000 C CNN
F 2 "" H 8738 3150 50  0001 C CNN
F 3 "~" H 8700 3300 50  0001 C CNN
	1    8700 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 3400 7450 3400
Wire Wire Line
	7500 4150 7800 4150
Wire Wire Line
	8100 4150 8350 4150
Wire Wire Line
	9000 4250 9050 4250
Wire Wire Line
	9050 4250 9050 3650
Wire Wire Line
	9050 3650 8850 3650
Wire Wire Line
	9050 3650 9050 3300
Wire Wire Line
	9050 3300 8850 3300
Connection ~ 9050 3650
Wire Wire Line
	8550 3300 8350 3300
Wire Wire Line
	8350 3300 8350 3400
Connection ~ 8350 4150
Wire Wire Line
	8350 4150 8400 4150
Wire Wire Line
	8550 3650 8350 3650
Connection ~ 8350 3650
Wire Wire Line
	8350 3650 8350 4150
Wire Wire Line
	8100 3400 8350 3400
Connection ~ 8350 3400
Wire Wire Line
	8350 3400 8350 3650
$Comp
L power:GND #PWR0118
U 1 1 5CABD767
P 7600 4450
F 0 "#PWR0118" H 7600 4200 50  0001 C CNN
F 1 "GND" H 7605 4277 50  0000 C CNN
F 2 "" H 7600 4450 50  0001 C CNN
F 3 "" H 7600 4450 50  0001 C CNN
	1    7600 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5CABD76D
P 8300 4450
F 0 "#PWR0119" H 8300 4200 50  0001 C CNN
F 1 "GND" H 8305 4277 50  0000 C CNN
F 2 "" H 8300 4450 50  0001 C CNN
F 3 "" H 8300 4450 50  0001 C CNN
	1    8300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 4350 7600 4350
Wire Wire Line
	7600 4350 7600 4450
Wire Wire Line
	8400 4350 8300 4350
Wire Wire Line
	8300 4350 8300 4450
Wire Wire Line
	3500 2300 3600 2300
Connection ~ 3500 2300
Text Label 3600 2300 0    50   ~ 0
CV_PITCH
Wire Wire Line
	3500 4250 3600 4250
Connection ~ 3500 4250
Wire Wire Line
	3500 6100 3600 6100
Connection ~ 3500 6100
Wire Wire Line
	6250 6100 6350 6100
Connection ~ 6250 6100
Wire Wire Line
	6250 4250 6350 4250
Connection ~ 6250 4250
Wire Wire Line
	6250 2300 6350 2300
Connection ~ 6250 2300
Wire Wire Line
	9050 2300 9150 2300
Connection ~ 9050 2300
Wire Wire Line
	9050 4250 9150 4250
Connection ~ 9050 4250
Text Label 3600 4250 0    50   ~ 0
CV_SHAPE
Text Label 3600 6100 0    50   ~ 0
CV_STRENGTH
Text Label 6350 2300 0    50   ~ 0
CV_MASS
Text Label 6350 4250 0    50   ~ 0
CV_DAMP
Text Label 6350 6100 0    50   ~ 0
CV_SPRING
Text Label 9150 2300 0    50   ~ 0
CV_CENTER
Text Label 9150 4250 0    50   ~ 0
CV_RATE
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB3411E
P 1700 2350
F 0 "J?" H 1731 2725 50  0000 C CNN
F 1 "PJ398SM" H 1731 2634 50  0000 C CNN
F 2 "" H 1700 2350 50  0001 C CNN
F 3 "" H 1700 2350 50  0001 C CNN
	1    1700 2350
	1    0    0    -1  
$EndComp
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB34407
P 1700 4300
F 0 "J?" H 1731 4675 50  0000 C CNN
F 1 "PJ398SM" H 1731 4584 50  0000 C CNN
F 2 "" H 1700 4300 50  0001 C CNN
F 3 "" H 1700 4300 50  0001 C CNN
	1    1700 4300
	1    0    0    -1  
$EndComp
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB34817
P 1700 6150
F 0 "J?" H 1731 6525 50  0000 C CNN
F 1 "PJ398SM" H 1731 6434 50  0000 C CNN
F 2 "" H 1700 6150 50  0001 C CNN
F 3 "" H 1700 6150 50  0001 C CNN
	1    1700 6150
	1    0    0    -1  
$EndComp
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB34C54
P 4450 6150
F 0 "J?" H 4481 6525 50  0000 C CNN
F 1 "PJ398SM" H 4481 6434 50  0000 C CNN
F 2 "" H 4450 6150 50  0001 C CNN
F 3 "" H 4450 6150 50  0001 C CNN
	1    4450 6150
	1    0    0    -1  
$EndComp
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB35030
P 4450 4300
F 0 "J?" H 4481 4675 50  0000 C CNN
F 1 "PJ398SM" H 4481 4584 50  0000 C CNN
F 2 "" H 4450 4300 50  0001 C CNN
F 3 "" H 4450 4300 50  0001 C CNN
	1    4450 4300
	1    0    0    -1  
$EndComp
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB352BB
P 4450 2350
F 0 "J?" H 4481 2725 50  0000 C CNN
F 1 "PJ398SM" H 4481 2634 50  0000 C CNN
F 2 "" H 4450 2350 50  0001 C CNN
F 3 "" H 4450 2350 50  0001 C CNN
	1    4450 2350
	1    0    0    -1  
$EndComp
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB355A1
P 7250 2350
F 0 "J?" H 7281 2725 50  0000 C CNN
F 1 "PJ398SM" H 7281 2634 50  0000 C CNN
F 2 "" H 7250 2350 50  0001 C CNN
F 3 "" H 7250 2350 50  0001 C CNN
	1    7250 2350
	1    0    0    -1  
$EndComp
$Comp
L eurorack:PJ398SM J?
U 1 1 5CB3579C
P 7250 4300
F 0 "J?" H 7281 4675 50  0000 C CNN
F 1 "PJ398SM" H 7281 4584 50  0000 C CNN
F 2 "" H 7250 4300 50  0001 C CNN
F 3 "" H 7250 4300 50  0001 C CNN
	1    7250 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 4250 7600 4250
Wire Wire Line
	7600 4250 7600 4350
Connection ~ 7600 4350
Wire Wire Line
	7500 2300 7600 2300
Wire Wire Line
	7600 2300 7600 2400
Connection ~ 7600 2400
Wire Wire Line
	4700 2300 4800 2300
Wire Wire Line
	4800 2300 4800 2400
Connection ~ 4800 2400
Wire Wire Line
	4700 4250 4800 4250
Wire Wire Line
	4800 4250 4800 4350
Connection ~ 4800 4350
Wire Wire Line
	4700 6100 4800 6100
Wire Wire Line
	4800 6100 4800 6200
Connection ~ 4800 6200
Wire Wire Line
	1950 6100 2050 6100
Wire Wire Line
	2050 6100 2050 6200
Connection ~ 2050 6200
Wire Wire Line
	1950 4250 2050 4250
Wire Wire Line
	2050 4250 2050 4350
Connection ~ 2050 4350
Wire Wire Line
	2050 2500 2050 2400
Wire Wire Line
	2050 2400 1950 2400
Wire Wire Line
	2050 2400 2050 2300
Wire Wire Line
	2050 2300 1950 2300
Connection ~ 2050 2400
Wire Wire Line
	1950 2200 2250 2200
$Comp
L Amplifier_Operational:MCP6004 U?
U 5 1 5CB95DCC
P 8200 5500
F 0 "U?" H 8158 5546 50  0000 L CNN
F 1 "MCP6004" H 8158 5455 50  0000 L CNN
F 2 "" H 8150 5600 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 8250 5700 50  0001 C CNN
	5    8200 5500
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6004 U?
U 5 1 5CB95ED9
P 8700 5500
F 0 "U?" H 8658 5546 50  0000 L CNN
F 1 "MCP6004" H 8658 5455 50  0000 L CNN
F 2 "" H 8650 5600 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 8750 5700 50  0001 C CNN
	5    8700 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5CB96044
P 9200 5450
F 0 "C?" H 9315 5496 50  0000 L CNN
F 1 "C" H 9315 5405 50  0000 L CNN
F 2 "" H 9238 5300 50  0001 C CNN
F 3 "~" H 9200 5450 50  0001 C CNN
	1    9200 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5CB9613D
P 9550 5450
F 0 "C?" H 9665 5496 50  0000 L CNN
F 1 "C" H 9665 5405 50  0000 L CNN
F 2 "" H 9588 5300 50  0001 C CNN
F 3 "~" H 9550 5450 50  0001 C CNN
	1    9550 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 5200 8100 5150
Wire Wire Line
	8100 5150 8600 5150
Wire Wire Line
	9550 5150 9550 5300
Wire Wire Line
	8600 5200 8600 5150
Connection ~ 8600 5150
Wire Wire Line
	8600 5150 8850 5150
Wire Wire Line
	9200 5300 9200 5150
Connection ~ 9200 5150
Wire Wire Line
	9200 5150 9550 5150
Wire Wire Line
	8100 5800 8100 5850
Wire Wire Line
	8100 5850 8600 5850
Wire Wire Line
	9550 5850 9550 5600
Wire Wire Line
	9200 5600 9200 5850
Connection ~ 9200 5850
Wire Wire Line
	9200 5850 9550 5850
Wire Wire Line
	8600 5800 8600 5850
Connection ~ 8600 5850
$Comp
L power:GND #PWR?
U 1 1 5CBC7A99
P 8850 5900
F 0 "#PWR?" H 8850 5650 50  0001 C CNN
F 1 "GND" H 8855 5727 50  0000 C CNN
F 2 "" H 8850 5900 50  0001 C CNN
F 3 "" H 8850 5900 50  0001 C CNN
	1    8850 5900
	1    0    0    -1  
$EndComp
Connection ~ 8850 5850
Text GLabel 8800 5050 0    50   Input ~ 0
+3V3_A
Wire Wire Line
	8800 5050 8850 5050
Wire Wire Line
	8850 5050 8850 5150
Connection ~ 8850 5150
Wire Wire Line
	8850 5150 9200 5150
Wire Wire Line
	8850 5900 8850 5850
Wire Wire Line
	8850 5850 9200 5850
Wire Wire Line
	8600 5850 8850 5850
Text GLabel 7450 3400 0    50   Input ~ 0
AREF_-10
Text GLabel 7450 1450 0    50   Input ~ 0
AREF_-10
Text GLabel 4650 1450 0    50   Input ~ 0
AREF_-10
Text GLabel 4650 3400 0    50   Input ~ 0
AREF_-10
Text GLabel 4650 5250 0    50   Input ~ 0
AREF_-10
Text GLabel 1900 5250 0    50   Input ~ 0
AREF_-10
Text GLabel 1900 3400 0    50   Input ~ 0
AREF_-10
Text GLabel 1900 1450 0    50   Input ~ 0
AREF_-10
$EndSCHEMATC
