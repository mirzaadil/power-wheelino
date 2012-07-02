package com.powerwheelino;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.text.Html.TagHandler;
import android.util.AttributeSet;
import android.util.FloatMath;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
 
public class MyView extends View {
  
 Paint paint;
 Path path;
 String messageStr;
 DatagramSocket s;;
 int server_port;
 InetAddress local;
 int msg_length;
 byte[] message;
 
 public MyView(Context context, int port, String server) {
  super(context);
  messageStr = "hello android";
  server_port = port;
  try {
	local = InetAddress.getByName(server);
	s = new DatagramSocket();
} catch (Exception e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
	Log.d("Powerwheelino",e.getStackTrace() + "error");
	
}
  msg_length= messageStr.length();
  message = messageStr.getBytes();
  
  init();
  
 }
 
 public MyView(Context context, AttributeSet attrs) {
  super(context, attrs);
  init();
 }
 
 public MyView(Context context, AttributeSet attrs, int defStyle) {
  super(context, attrs, defStyle);
  init();
 }
  
 private void init(){
  paint = new Paint();
  paint.setColor(Color.GRAY);
  paint.setStrokeWidth(5);
  paint.setStyle(Paint.Style.STROKE);
 
 }
 
 @Override
 protected void onDraw(Canvas canvas) {
  // TODO Auto-generated method stub
  super.onDraw(canvas);
  
  canvas.drawRect(20, 50, 150, 350, paint);
  //canvas.drawRect(100, 100, 300, 400, paint);
  //drawRect(left, top, right, bottom, paint)
  float circlex = (float) (super.getWidth()*(.75));
  float circley = (float) (super.getHeight()*(.75));
  canvas.drawCircle(circlex, circley, 75, paint);
  
 
 }
 
 
@Override
 public boolean onTouchEvent(MotionEvent event){
	 super.onTouchEvent(event);
//     switch (event.getAction()) {
//	     case MotionEvent.ACTION_MOVE: {
	         Log.d("Powerwheelino", " getX: " + event.getX() + " getY: " + event.getY());
//	         break;
//	     }
//     }
	        
     
     
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
