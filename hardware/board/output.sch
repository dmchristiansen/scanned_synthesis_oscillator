EESchema Schematic File Version 4
LIBS:FDM-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L eurorack:AK4554 U?
U 1 1 5CF6A1D7
P 5150 2850
F 0 "U?" H 4950 3325 50  0000 C CNN
F 1 "AK4554" H 4950 3234 50  0000 C CNN
F 2 "" H 5150 2850 50  0001 C CNN
F 3 "" H 5150 2850 50  0001 C CNN
	1    5150 2850
	1    0    0    -1  
$EndComp
NoConn ~ 4550 2700
NoConn ~ 5350 2600
Text GLabel 5350 3000 2    50   Input ~ 0
I2S_BCLK
Text GLabel 5350 3100 2    50   Input ~ 0
I2S_MCLK
Text GLabel 5350 3300 2    50   Input ~ 0
I2S_TXD
Text GLabel 4550 3300 0    50   Output ~ 0
I2S_RXD
$EndSCHEMATC
