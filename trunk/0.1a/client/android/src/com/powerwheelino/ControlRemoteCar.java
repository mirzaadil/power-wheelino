package com.powerwheelino;

import android.app.Activity;
import android.os.Bundle;

public class ControlRemoteCar extends Activity {
    /** Called when the activity is first created. */
	MyView mainview; 
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //JoystickView joystick = new JoystickView(this);
        //setContentView(joystick);
        mainview = new MyView(this,50000,"192.168.1.128");
        setContentView(mainview);
        
    }
    


}

//Paint paint = new Paint(); 
//paint.setColor(Color.WHITE); 
//paint.setStyle(Style.FILL); 
//canvas.drawPaint(paint); 
//
//paint.setColor(Color.BLACK); 
//paint.setTextSize(20); 
//canvas.drawText("Some Text", 10, 25, paint); 