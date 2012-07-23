package com.powerwheelino;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.DatagramSocketImpl;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketAddress;

import android.util.Log;

public class UdpClient {
	 String messageStr;
	 DatagramSocket s;;
	 int server_port;
	 InetAddress local;
	 int msg_length;
	 byte[] message;
	 boolean connected = false;
	 String srvMessage;
	 
	public UdpClient (String ipAddress, int port){
		  message = new byte[2];
		  server_port = port;
		  try {
			local = InetAddress.getByName(ipAddress);
			s = new DatagramSocket();
			//s.setBroadcast(true);
			//s.connect(local, port);
//			s.bind(new InetSocketAddress(51000));
		  } catch (Exception e) {
			e.printStackTrace();
			Log.d("powerwheelino",e.getMessage());
			Log.d("Powerwheelino",e.getStackTrace() + "error");
		  }		
		  byte[] rcvdata = new byte[256];
		  DatagramPacket rPacket = new DatagramPacket(rcvdata, rcvdata.length);
		  sendData((byte)0, (byte)0);
		
		  try {
			//  s.bind(null);
			  s.setSoTimeout(1000);
			  s.receive(rPacket);
		} catch (IOException e) {
			e.printStackTrace();
		}
		  if (rcvdata[0] > 0){
			  connected = true;
			  srvMessage = new String(rcvdata,0,rPacket.getLength());
		  }
	}
	
	public boolean sendData(byte drive, byte steering){
//		byte drvByte = (byte) (drive & 0xFF);
//		byte steerByte = (byte) (steering & 0xFF);
//		message[0] = drvByte;
//		message[1] = steerByte;
		message[0] = (byte) (drive & 0xFF);
		message[1] = (byte) (steering & 0xFF);
		//msg_length = message.length;
		//message = messageStr.getBytes();
		
		try {	
		     DatagramPacket p = new DatagramPacket(message, message.length,local,server_port);
		     s.send(p);
		} catch (Exception e) {
			Log.d("Powerwheelino", e.getStackTrace() +"ERROR ");
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	public boolean isConnected (){
		return connected;
	}
	public String getServerMessage() {
		return srvMessage;
	}
	
}
