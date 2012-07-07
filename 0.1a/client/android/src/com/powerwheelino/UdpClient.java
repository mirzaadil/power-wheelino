package com.powerwheelino;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import android.util.Log;

public class UdpClient {
	 String messageStr;
	 DatagramSocket s;;
	 int server_port;
	 InetAddress local;
	 int msg_length;
	 byte[] message;
	 
	public UdpClient (String ipAddress, int port){
		  server_port = port;
		  try {
			local = InetAddress.getByName(ipAddress);
			s = new DatagramSocket();
		} catch (Exception e) {
			e.printStackTrace();
			Log.d("Powerwheelino",e.getStackTrace() + "error");
		}		
	}
	
	public boolean sendData(byte drive, byte steering){
		byte drvByte = (byte) (drive & 0xFF);
		byte steerByte = (byte) (steering & 0xFF);
		message = new byte[2];
		message[0] = drvByte;
		message[1] = steerByte;
		msg_length = message.length;
		//message = messageStr.getBytes();
		try {	
		     DatagramPacket p = new DatagramPacket(message, msg_length,local,server_port);
		     s.send(p);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			Log.d("Powerwheelino", e.getStackTrace() +"ERROR ");
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
}
