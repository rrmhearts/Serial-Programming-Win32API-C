##Serial Port Programming using Win32 API and C language

This repo contains code for transmitting and receiving characters (Strings) serially between an x86 Windows PC and a Microcontroller (MSP430G2553 on Launchpad).

<img src="http://s25.postimg.org/bqw6jzqfz/Serial_port_write_windows.jpg" alt ="Screenshot of the serial port programming code running on windows 7">

Full code explanation along with screenshots can be <a href = http://xanthium.in/Serial-Port-Programming-using-Win32-API> found here on the xanthium website </a>

The Microcontroller and PC are connected in null modem configuration using  3 signals (TX,RX and Ground).

The code uses standard Win32 API's to intialize the PC serial port and transmit a character to the microcontroller board.
- The PC side code is written in **C** using **Win32 API** 
- and can be compiled using **GCC** or **Microsoft Visual Studio Express**.

The Code will Work With Standard **RS232 Serial ports** or any **USB to Serial Converter**.

More info about the  <a href = "http://xanthium.in/USB-to-Serial-RS232-RS485-Converter">USB to Serial/RS232/RS485 Converter used in the above tutorial can be found here</a>

<img src = "http://s25.postimg.org/ucb73bztr/usb_to_rs485_converter_250px.jpg"  href="http://xanthium.in/USB-to-Serial-RS232-RS485-Converter"/>

The Microcontroller side code is written in **Embedded C** and Compiled using **IAR embedded Workbench for MSP430**.

The Hardware used is MSP430G2553 on Launch pad development board.
 
