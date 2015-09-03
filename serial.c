	//====================================================================================================//
	// Serial Port Programming using Win32 API in C                                                       //
	// (Writes data to serial port)                                                                       //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2014 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// Compiler/IDE  :	Microsoft Visual Studio Express 2013 for Windows Desktop(Version 12.0)            //
	//               :  gcc 4.8.1 (MinGW)                                                                 //
	// Library       :  Win32 API,windows.h,                                                              //
	// Commands      :  gcc -o serial serial.c                                                            //
	// OS            :	Windows(Windows 7)                                                                //
	// Programmer    :	Rahul.S                                                                           //
	// Date	         :	30-November-2014                                                                  //
	//====================================================================================================//

	//====================================================================================================//
	// Sellecting the COM port Number                                                                     //
    //----------------------------------------------------------------------------------------------------//
    // Use "Device Manager" in Windows to find out the COM Port number allotted to USB2SERIAL converter-  // 
    // -in your Computer and substitute in the  CreateFile()                                              //
	//                                                                                                    //
	// for eg:-                                                                                           //
	// If your COM port number is COM32 in device manager(will change according to system)                //
	// then                                                                                               //
	//			    CreateFile("\\\\.\\COM32", , , , );                                                   //
	//====================================================================================================//

	#include<Windows.h>
	#include<stdio.h>
	int main()
	{
		HANDLE hComm;
		hComm = CreateFile("\\\\.\\COM24",            //port name 
							GENERIC_READ | GENERIC_WRITE, //Read/Write   				 
							0,            // No Sharing                               
							NULL,         // No Security                              
							OPEN_EXISTING,// Open existing port only                     
							0,            // Non Overlapped I/O                           
							NULL);        // Null for Comm Devices
                             
		if (hComm == INVALID_HANDLE_VALUE)
			printf("Error in opening Serial port");		
		else
			printf("\nopening serial port successful\n");
   
		CloseHandle(hComm);//Closing the Serial Port
		return 0;
	}