package main;

import java.awt.AWTException;
import java.awt.Robot;

public class MoveMouse implements Runnable
{
	Robot robot;
	
	public void run()
	{
		// These coordinates are screen coordinates
	    int xCoord = 500;
	    int yCoord = 500;
	    
	    //make the robot
		try
		{
			robot = new Robot();
		}
		catch (AWTException e)
		{
			e.printStackTrace();
		}
	    
		for(;;)
		{
			try
			{
			    // Move the cursor
			    robot.mouseMove(xCoord, yCoord);
			    Thread.sleep(5000);
			}
			catch (InterruptedException e)
			{
				return;
			}
		}
	}
}
