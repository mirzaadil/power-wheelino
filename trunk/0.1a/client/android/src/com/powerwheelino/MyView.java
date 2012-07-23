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
 UdpClient udp;
 int boxwidth = 100;
 int boxheight = 100;
 float left;
 float top;
 float right;
 float bottom;
 
 public MyView(Context context, int port, String serverIp) {
  super(context);
  init();
  udp = new UdpClient(serverIp, port);
  left = Math.round(getMeasuredWidth() *.75) - (boxwidth / 2);
  top = Math.round(getMeasuredHeight() *.75) - (boxheight / 2);
  right = Math.round(getMeasuredWidth() *.75) + (boxwidth / 2);
  bottom = Math.round(getMeasuredHeight() *.75) + (boxheight / 2);

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
	  super.onDraw(canvas);
	  canvas.drawRect(10, 10, 110, 210, paint);
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
	         int tx = Math.round(event.getY());
	         byte drive = (byte) (tx & 0x000000FF);
	         
	         int ty = Math.round(event.getX());
	         byte steer = (byte) (ty & 0x000000FF);
	         
	         udp.sendData(drive, steer);
	         return true;
	}

}
