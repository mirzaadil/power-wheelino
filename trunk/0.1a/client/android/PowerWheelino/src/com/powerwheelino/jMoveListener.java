package com.powerwheelino;

import android.util.Log;

public class jMoveListener implements JoystickMovedListener {
	UdpClient udp;
	
	jMoveListener(String serverIP, int serverPort){
		udp = new UdpClient(serverIP, serverPort);
		
	}
	@Override
	public void OnMoved(int pan, int tilt) {
		// TODO Auto-generated method stub
		Log.d("powerwheelino", "x: " + pan + " y: " + tilt);
		sendData(pan,tilt);
	}

	@Override
	public void OnReleased() {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnReturnedToCenter() {
		// TODO Auto-generated method stub

	}

	public boolean sendData(int x, int y){
		boolean xInBounds = (x > -128 && x < 128);
		boolean yInBounds = (y > -128 && y < 128);
		
		if (xInBounds && yInBounds){
			byte drive = (byte) (y & 0x000000FF);
			byte steering = (byte) (x & 0x000000FF);
			udp.sendData(drive, steering);
			return true;
		}
		
		return false;
	}
}
