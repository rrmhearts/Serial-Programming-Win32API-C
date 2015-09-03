
	//====================================================================================================//
	// Serial Port Programming using Win32 API in C                                                       //
	// (Reads data from serial port)                                                                      //
	//====================================================================================================//
	
	//====================================================================================================//
	// www.xanthium.in										                                              //
	// Copyright (C) 2014 Rahul.S                                                                         //
	//====================================================================================================//
	
	//====================================================================================================//
	// The Program runs on the PC side and uses Win32 API to communicate with the serial port or          //
	// USB2SERIAL board and reads the data from it.                                                       //       
	//----------------------------------------------------------------------------------------------------//
	// Program runs on the PC side (Windows) and receives a string of characters.                         //            
	// Program uses CreateFile() function to open a connection serial port(COMxx).                        //
	// Program then sets the parameters of Serial Comm like Baudrate,Parity,Stop bits in the DCB struct.  //
	// After setting the Time outs,the Program waits for the reception of string of characters by setting-//
	// -up the  WaitCommEvent().                                                                          //
	// When a character is reeived bythe PC UART WaitCommEvent() returns and the received string is read- //
	// -using ReadFile(); function.The characters are then displayed on the Console.                      //
	//----------------------------------------------------------------------------------------------------// 
	// BaudRate     -> 9600                                                                               //
	// Data formt   -> 8 databits,No parity,1 Stop bit (8N1)                                              //
	// Flow Control -> None                                                                               //
	//----------------------------------------------------------------------------------------------------//
	
	
	//====================================================================================================//
	// Compiler/IDE  :	Microsoft Visual Studio Express 2013 for Windows Desktop(Version 12.0)            //
	//               :  gcc 4.8.1 (MinGW)                                                                 //
	//                                                                                                    //
	// Library       :  Win32 API,windows.h,                                                              //
	// Commands      :  gcc -o USB2SERIAL_Read_W32 USB2SERIAL_Read_W32.c                                  //
	// OS            :	Windows(Windows 7)                                                                //
	// Programmer    :	Rahul.S                                                                           //
	// Date	         :	30-November-2014                                                                  //
	//====================================================================================================//

	//====================================================================================================//
	// Sellecting the COM port Number                                                                     //
	//----------------------------------------------------------------------------------------------------//
	// Use "Device Manager" in Windows to find out the COM Port number allotted to USB2SERIAL converter-  // 
	// -in your Computer and substitute in the  "ComPortName[]" array.                                    //
	//                                                                                                    //
	// for eg:-                                                                                           //
	// If your COM port number is COM32 in device manager(will change according to system)                //
	// then                                                                                               //
	//			char   ComPortName[] = "\\\\.\\COM32";                                                    //
	//====================================================================================================//

	#include <Windows.h>
	#include <stdio.h>
	
	void main(void)
		{
			HANDLE hComm;                          // Handle to the Serial port
			char  ComPortName[] = "\\\\.\\COM24";  // Name of the Serial port(May Change) to be opened,
			BOOL  Status;                          // Status of the various operations 
			DWORD dwEventMask;                     // Event mask to trigger
			char  TempChar;                        // Temperory Character
			char  SerialBuffer[256];               // Buffer Containing Rxed Data
			DWORD NoBytesRead;                     // Bytes read by ReadFile()
			int i = 0;

			printf("\n\n +==========================================+");
			printf("\n |    Serial Port  Reception (Win32 API)    |");
			printf("\n +==========================================+\n");
			/*---------------------------------- Opening the Serial Port -------------------------------------------*/
			
			hComm = CreateFile( ComPortName,                  // Name of the Port to be Opened
		                        GENERIC_READ | GENERIC_WRITE, // Read/Write Access
								0,                            // No Sharing, ports cant be shared
								NULL,                         // No Security
							    OPEN_EXISTING,                // Open existing port only
		                        0,                            // Non Overlapped I/O
		                        NULL);                        // Null for Comm Devices

			if (hComm == INVALID_HANDLE_VALUE)
				printf("\n    Error! - Port %s can't be opened\n", ComPortName);
			else
				printf("\n    Port %s Opened\n ", ComPortName);

			/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/
			
			DCB dcbSerialParams = { 0 };                         // Initializing DCB structure
			dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

			Status = GetCommState(hComm, &dcbSerialParams);      //retreives  the current settings

			if (Status == FALSE)
				printf("\n    Error! in GetCommState()");

			dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
			dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
			dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
			dcbSerialParams.Parity = NOPARITY;        // Setting Parity = None 

			Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

			if (Status == FALSE)
				{
					printf("\n    Error! in Setting DCB Structure");
				}
			else //If Successfull display the contents of the DCB Structure
				{
					printf("\n\n    Setting DCB Structure Successfull\n");
					printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
					printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
					printf("\n       StopBits = %d", dcbSerialParams.StopBits);
					printf("\n       Parity   = %d", dcbSerialParams.Parity);
				}

			/*------------------------------------ Setting Timeouts --------------------------------------------------*/
			
			COMMTIMEOUTS timeouts = { 0 };
			timeouts.ReadIntervalTimeout         = 50;
			timeouts.ReadTotalTimeoutConstant    = 50;
			timeouts.ReadTotalTimeoutMultiplier  = 10;
			timeouts.WriteTotalTimeoutConstant   = 50;
			timeouts.WriteTotalTimeoutMultiplier = 10;
			
			if (SetCommTimeouts(hComm, &timeouts) == FALSE)
				printf("\n\n    Error! in Setting Time Outs");
			else
				printf("\n\n    Setting Serial Port Timeouts Successfull");

			/*------------------------------------ Setting Receive Mask ----------------------------------------------*/
			
			Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception
	
			if (Status == FALSE)
				printf("\n\n    Error! in Setting CommMask");
			else
				printf("\n\n    Setting CommMask successfull");

			
           /*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/
			
			printf("\n\n    Waiting for Data Reception");

			Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received
	
			/*-------------------------- Program will Wait here till a Character is received ------------------------*/				

			if (Status == FALSE)
				{
					printf("\n    Error! in Setting WaitCommEvent()");
				}
			else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
				{
					printf("\n\n    Characters Received");
					do
						{
							Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
							SerialBuffer[i] = TempChar;
							i++;
					    }
					while (NoBytesRead > 0);

					

					/*------------Printing the RXed String to Console----------------------*/

					printf("\n\n    ");
					int j =0;
					for (j = 0; j < i-1; j++)		// j < i-1 to remove the dupliated last character
						printf("%c", SerialBuffer[j]);
		
				}	
		
				CloseHandle(hComm);//Closing the Serial Port
				printf("\n +==========================================+\n");
				_getch();
		}//End of Main()