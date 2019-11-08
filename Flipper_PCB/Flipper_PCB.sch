EESchema Schematic File Version 4
LIBS:Flipper_PCB-cache
EELAYER 29 0
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
L Connector_Generic:ESP32_DevKitC_Right Right1
U 1 1 5DCD3C29
P 6450 2750
F 0 "Right1" H 6368 3867 50  0000 C CNN
F 1 "ESP32_DevKitC_Right" H 6368 3776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x19_P2.54mm_Vertical" H 6450 1700 50  0001 C CNN
F 3 "" H 6450 1700 50  0001 C CNN
	1    6450 2750
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:ESP32_DevKitC_Left Left1
U 1 1 5DCED2C2
P 5700 2800
F 0 "Left1" H 5780 2892 50  0000 C CNN
F 1 "ESP32_DevKitC_Left" H 5780 2801 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x19_P2.54mm_Vertical" H 5700 1800 50  0001 C CNN
F 3 "" H 5700 1800 50  0001 C CNN
	1    5700 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x12 MusicMaker_Left1
U 1 1 5DCF2197
P 3600 2350
F 0 "MusicMaker_Left1" H 3680 2342 50  0001 L CNN
F 1 "Conn_01x12" H 3680 2251 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 3600 2350 50  0001 C CNN
F 3 "~" H 3600 2350 50  0001 C CNN
	1    3600 2350
	1    0    0    -1  
$EndComp
Text Notes 4100 2150 0    50   ~ 0
MISO
Text Notes 4100 2250 0    50   ~ 0
MOSI
Text Notes 4100 2350 0    50   ~ 0
SCK
Text Notes 3650 2050 0    50   ~ 0
SD CS
Text Notes 3650 2150 0    50   ~ 0
MP3CS
Text Notes 3650 2250 0    50   ~ 0
DREQ
Text Notes 3650 2350 0    50   ~ 0
XDCS
Text Notes 3550 3100 0    50   ~ 0
L
Text Notes 4350 3500 0    50   ~ 0
R
Text Notes 3550 1700 0    50   ~ 0
Adafruit Music Maker
$Comp
L Connector_Generic:Conn_01x04 SERIAL1
U 1 1 5DD0CA6F
P 7600 1900
F 0 "SERIAL1" H 7680 1892 50  0001 L CNN
F 1 "Conn_01x04" H 7680 1801 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7600 1900 50  0001 C CNN
F 3 "~" H 7600 1900 50  0001 C CNN
	1    7600 1900
	1    0    0    -1  
$EndComp
Text Notes 7700 1800 0    50   ~ 0
VCC
Text Notes 7700 1900 0    50   ~ 0
TXD
Text Notes 7700 2000 0    50   ~ 0
RXD
Text Notes 7700 2100 0    50   ~ 0
GND
$Comp
L Connector:Screw_Terminal_01x02 ServoData-GND1
U 1 1 5DD13B37
P 7600 2550
F 0 "ServoData-GND1" H 7680 2542 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 7680 2451 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 7600 2550 50  0001 C CNN
F 3 "~" H 7600 2550 50  0001 C CNN
	1    7600 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 12V1
U 1 1 5DD14FF9
P 2350 950
F 0 "12V1" H 2268 817 50  0000 C CNN
F 1 "Conn_01x01" H 2430 901 50  0001 L CNN
F 2 "" H 2350 950 50  0001 C CNN
F 3 "~" H 2350 950 50  0001 C CNN
	1    2350 950 
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 GND1
U 1 1 5DD16AAC
P 2350 1250
F 0 "GND1" H 2268 1117 50  0000 C CNN
F 1 "Conn_01x01" H 2430 1201 50  0001 L CNN
F 2 "" H 2350 1250 50  0001 C CNN
F 3 "~" H 2350 1250 50  0001 C CNN
	1    2350 1250
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 5V1
U 1 1 5DD16FF6
P 2850 950
F 0 "5V1" H 2768 817 50  0000 C CNN
F 1 "Conn_01x01" H 2930 901 50  0001 L CNN
F 2 "" H 2850 950 50  0001 C CNN
F 3 "~" H 2850 950 50  0001 C CNN
	1    2850 950 
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 GND2
U 1 1 5DD172E1
P 2850 1250
F 0 "GND2" H 2768 1117 50  0000 C CNN
F 1 "Conn_01x01" H 2930 1201 50  0001 L CNN
F 2 "" H 2850 1250 50  0001 C CNN
F 3 "~" H 2850 1250 50  0001 C CNN
	1    2850 1250
	1    0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 12V-GND1
U 1 1 5DD10982
P 1250 950
F 0 "12V-GND1" H 1330 942 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 1330 851 50  0001 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1250 950 50  0001 C CNN
F 3 "~" H 1250 950 50  0001 C CNN
	1    1250 950 
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x16 J1
U 1 1 5DD1DD42
P 4350 2550
F 0 "J1" H 4268 3467 50  0001 C CNN
F 1 "Conn_01x16" H 4268 3376 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x16_P2.54mm_Vertical" H 4350 2550 50  0001 C CNN
F 3 "~" H 4350 2550 50  0001 C CNN
	1    4350 2550
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
