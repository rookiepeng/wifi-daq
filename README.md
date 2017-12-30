# WiFi DAQ

WiFi DAQ: A system, including hardware and software, can continuously sample analog signal with 62.5 ksps and send the data to PC client through WiFi.

## Hardware

The hardware is TI Simplelink CC3200, which is an ARM micro-controller with a WiFi subsystem.

Either CC3200 LaunchPad or the customized WiFi DAQ board can be used.

## Firmware

The firmware source code of CC3200 can be found in

```
/CC3200
```

### Build

Build the source code with TI Code Composer Studio (CCS).

Dependency:

* [CC3200 SDK 1.3.0](http://www.ti.com/tool/CC3200SDK)
* [CC3200 Service Pack 1.0.1.11-2.10.0.0](http://www.ti.com/tool/CC3200SDK)

The built binary file must be downloaded into CC3200 by using [Uniflash v3.4.1](http://www.ti.com/tool/UNIFLASH).

## Client

Currently, there is only a PC client avaiable, which is built by Qt5.
The source code of the PC client can be found in

```
/PC Client
```

### Build

The source code can be compiled with [Qt5](https://www.qt.io/) in Windows, Linux and MacOS. Qt Creator can be used.

## Usage

Here are the steps to setup the system:

1. Connect the ananlog signal to **ADC 2** of the WiFi DAQ board (Pin 59) **(Signal voltage must be in 0 - 1.48 V)**.
2. On the PC, search the WiFi hotspot named **WiFi-DAQ** and connect it.
3. Open the PC Client, on the **Network** tab, click **Refresh** button to update IP address.
4. Set **TCP IP** to **192.168.1.1**, **TCP Port** to **1234** and **UDP Port** to **1234**.
5. Click **Connect** button to connect with the board.
6. Send **ADC START** to start data sampling.
7. Send **ADC STOP** to stop data sampling. 

## *Todo list*

Help is always welcome. Please contact me if you want to make a contribution to this project.

*Firmware*

1. Implement watchdog to reset CC3200 automatically when the firmware stops working.
2. Selectable among different ADC channels.
3. Improve connection reliablity.

*Client*

1. Replace command-line confguration with buttons.

## *Known issues*

1. ADC will stop working after start and stop 4 times. (The problem may in the firmware)
2. Occasionally, ADC will stop working after running for a while.

