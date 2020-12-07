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
L 74xx:74AHC595 U?
U 1 1 5FCEA65E
P 3300 2500
F 0 "U?" H 3700 3225 50  0000 C CNN
F 1 "74AHC595" H 3700 3150 50  0000 C CNN
F 2 "" H 3300 2500 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74AHC_AHCT595.pdf" H 3300 2500 50  0001 C CNN
	1    3300 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FCEB154
P 3300 3200
F 0 "#PWR?" H 3300 2950 50  0001 C CNN
F 1 "GND" H 3305 3027 50  0000 C CNN
F 2 "" H 3300 3200 50  0001 C CNN
F 3 "" H 3300 3200 50  0001 C CNN
	1    3300 3200
	1    0    0    -1  
$EndComp
Text GLabel 1625 2100 0    50   Input ~ 0
SRDAT
Text GLabel 1625 2300 0    50   Input ~ 0
SRCLK
Text GLabel 1625 2600 0    50   Input ~ 0
LATCH
$Comp
L power:VCC #PWR?
U 1 1 5FCEFC8E
P 3425 1875
F 0 "#PWR?" H 3425 1725 50  0001 C CNN
F 1 "VCC" H 3440 2048 50  0000 C CNN
F 2 "" H 3425 1875 50  0001 C CNN
F 3 "" H 3425 1875 50  0001 C CNN
	1    3425 1875
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 1900 3300 1875
Wire Wire Line
	3300 1875 3425 1875
Wire Wire Line
	1625 2100 2900 2100
Wire Wire Line
	3700 3000 3775 3000
Connection ~ 2525 2600
Connection ~ 2625 2300
Wire Wire Line
	2900 2600 2525 2600
Wire Wire Line
	2625 2300 2900 2300
Wire Wire Line
	1625 2300 2625 2300
Wire Wire Line
	2725 3950 2900 3950
Wire Wire Line
	3775 3425 2725 3425
Wire Wire Line
	3775 3000 3775 3425
Wire Wire Line
	2525 4450 2900 4450
Wire Wire Line
	2625 4150 2900 4150
$Comp
L power:VCC #PWR?
U 1 1 5FCFF9C2
P 3425 3700
F 0 "#PWR?" H 3425 3550 50  0001 C CNN
F 1 "VCC" H 3440 3873 50  0000 C CNN
F 2 "" H 3425 3700 50  0001 C CNN
F 3 "" H 3425 3700 50  0001 C CNN
	1    3425 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FCFF646
P 3300 5050
F 0 "#PWR?" H 3300 4800 50  0001 C CNN
F 1 "GND" H 3305 4877 50  0000 C CNN
F 2 "" H 3300 5050 50  0001 C CNN
F 3 "" H 3300 5050 50  0001 C CNN
	1    3300 5050
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74AHC595 U?
U 1 1 5FCFF640
P 3300 4350
F 0 "U?" H 3700 5050 50  0000 C CNN
F 1 "74AHC595" H 3700 4950 50  0000 C CNN
F 2 "" H 3300 4350 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74AHC_AHCT595.pdf" H 3300 4350 50  0001 C CNN
	1    3300 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2725 3425 2725 3950
Wire Wire Line
	2625 2300 2625 4150
Wire Wire Line
	2525 2600 2525 4450
Wire Wire Line
	2900 2700 2900 3200
Wire Wire Line
	2900 3200 3300 3200
Connection ~ 3300 3200
Wire Wire Line
	2900 4550 2900 5050
Wire Wire Line
	2900 5050 3300 5050
Connection ~ 3300 5050
Wire Wire Line
	1625 2600 2525 2600
Wire Wire Line
	2900 2400 2850 2400
Wire Wire Line
	2850 2400 2850 1875
Wire Wire Line
	2850 1875 3300 1875
Connection ~ 3300 1875
Wire Wire Line
	2900 4250 2825 4250
Wire Wire Line
	2825 4250 2825 3700
Wire Wire Line
	3300 3750 3300 3700
Wire Wire Line
	3300 3700 3425 3700
Wire Wire Line
	2825 3700 3300 3700
Connection ~ 3300 3700
$EndSCHEMATC
