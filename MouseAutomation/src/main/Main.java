package main;

import java.awt.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class Main
{
	public final static AtomicInteger xCord = new AtomicInteger(0);
	public final static AtomicInteger yCord = new AtomicInteger(0);
	public static Robot robot;
	
	public static Semaphore read = new Semaphore(1);
	
	private static class mouseMover implements Runnable
	{
		//0 means down, 1 means up
		public static int state;
		
		public void run()
		{
			state = 0;
		    
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
				//lock the thingy
				try
				{
					read.acquire();
				}
				catch (InterruptedException e)
				{
					System.out.println("Interupt Detected");
					return;
				}
				
				//update the cursor
				UpdateCoord();
				
				//move the cursor
				robot.mouseMove(xCord.get(), yCord.get());
				
				//unlock the thingy
				read.release();
				
				try
				{
					Thread.sleep(10);
				}
				catch (InterruptedException e)
				{
					System.out.println("Interupt Detected");
					return;
				}
			}
		}
		
		public void UpdateCoord()
		{
			int x = xCord.get();
			int y = yCord.get();
			
			//if down
			if (state == 0)
			{
				//if at bottom
				if (x == 500)
					state = 1;
				else
				{
					xCord.addAndGet(25);
					yCord.addAndGet(25);
				}
			}
			
			//if up
			if (state == 1)
			{
				//if at top
				if (x == 0)
					state = 0;
				else
				{
					xCord.addAndGet(-25);
					yCord.addAndGet(-25);
				}
			}
		}
	}
		
	public static void main(String[] args) throws InterruptedException
	{
			Point mousePoint;
			int x;
			int y;
			
			Thread t = new Thread(new mouseMover());
			t.start();
			
			Thread.sleep(1000);
			
			for (;;)
			{
				//lock the thingy
				try
				{
					read.acquire();
				}
				catch (InterruptedException e)
				{
					e.printStackTrace();
				}
				mousePoint = MouseInfo.getPointerInfo().getLocation();
				x = xCord.get();
				y = yCord.get();
				
				
				//System.out.println("Main x:" + mousePoint.getX() + "\nMain y:" + mousePoint.getY() + "\n + MouseMover x:" + x + "\nMouseMover y:" + y + "\n");
				if (mousePoint.getX() > x+1 || mousePoint.getX() < x-1 || mousePoint.getY() > y+1 || mousePoint.getY() < y-1)
				{
					t.interrupt();
					t.join();
					return;
				}
				
				//unlock the thingy
				read.release();
				
				Thread.sleep(10);
			}
	}
}