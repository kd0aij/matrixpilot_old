MAVLink Micro Air Vehicle Message Marshalling Library

This is a library for lightweight communication between
Micro Air Vehicles (swarm) and/or ground control stations.

It serializes C-structs for serial channels and can be used with
any type of radio modem.

To generate/update packets, select mavlink_standard_message.xml
in the QGroundControl station settings view, select mavlink/include as
the output directory and click on "Save and Generate".
You will find the newly generated/updated message_xx.h files in
the mavlink/include/generated folder.

To use MAVLink, #include the <mavlink.h> file, not the individual
message files. In some cases you will have to add the main folder to the include search path as well. To be safe, we recommend these flags:

gcc -I mavlink/include -I mavlink/include/<your message set, e.g. common>

For more information, please visit:

http://pixhawk.ethz.ch/wiki/software/mavlink/

(c) 2009-2011 Lorenz Meier <pixhawk@switched.com> / PIXHAWK Team



ADDITIONAL INFORMATION REGARDING MAVLINK FOR MATRIXPILOT

This Mavlink directory has been created using the followign recipe:

* Downloaded and installed Windows GIT Tool from here
  http://code.google.com/p/msysgit/downloads/detail?name=Git-1.7.3.1-preview20101002.exe&can=2&q=

* Downloaded source code for Mavlink (XML data structures) from dev branch here:-
  https://github.com/pixhawk/mavlink

* Added in the file inttypes.h to the MAVLink include directory.

* Edited the QGroundControl website template to create matrixpilot_mavlink_bridge_header.h
  in the MAVLink include directory.

* Edited protocol.h to avoid compiler error that must be unique to dspic C30 compiler.
  Have to define integer used in for loop outside of the for loop. As  follows:-

  static inline void mavlink_send_uart(mavlink_channel_t chan, mavlink_message_t* msg)
  {
	// ARM7 MCU board implementation
	// Create pointer on message struct
	// Send STX
	comm_send_ch(chan, MAVLINK_STX);
	comm_send_ch(chan, msg->len);
	comm_send_ch(chan, msg->seq);
	comm_send_ch(chan, msg->sysid);
	comm_send_ch(chan, msg->compid);
	comm_send_ch(chan, msg->msgid);
	uint16_t i = 0;
	for(i = 0; i < msg->len; i++)
	{
		comm_send_ch(chan, msg->payload[i]);
	}
	comm_send_ch(chan, msg->ck_a);
	comm_send_ch(chan, msg->ck_b);
  }

* Added all the *.h files in MAVLink include directory and MAVLink/include/common directory
  to the MPLAB project list for MatrixPilot (relative file addressing). 
  (we are currently only using the "common" message types.


Pete Hollands 02 December 2010

  

