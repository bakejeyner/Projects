package gui;

import stringParser.StringParser;

import java.awt.*;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.*;
import javax.swing.*;
import java.io.IOException;

@SuppressWarnings("serial")
public class MainFrame extends JFrame implements ActionListener, KeyListener
{
	//declare variables
	public StringParser stringParser;
	public String myString;
	public String tokenString;
	
	//declare components
	public Container mainContainer;
	public JLabel stringDisplay;
	public JButton startButton;
	
	public MainFrame()
	{	
		//initialize variables
		myString = "Please Press the Start Button!";
		stringParser = new StringParser(myString);
		
		//initialize components
		mainContainer = this.getContentPane();
		stringDisplay = new JLabel(myString,0);
		stringDisplay.setFont(new Font("Dialog", Font.PLAIN, 24));
		startButton = new JButton("Start");
		
		//initialize listeners
		startButton.addActionListener(this);
		this.addKeyListener(this);
		
		//set layout
		mainContainer.setLayout(new BorderLayout());
		
		//add components to JFrame
		mainContainer.add(startButton, BorderLayout.PAGE_END);
		mainContainer.add(stringDisplay, BorderLayout.CENTER);
		
		//display
		this.setFocusable(true);
		this.setSize(500,500);
		this.setVisible(true);
	}
	
	public void refreshMainFrame()
	{
		stringDisplay.setText(myString);
		stringDisplay.paintImmediately(stringDisplay.getBounds());
		mainContainer.revalidate();
		mainContainer.repaint();
	}
	
	public void getString()
	{
		//get string from clipboard
		try
		{
			myString = (String)Toolkit.getDefaultToolkit().getSystemClipboard().getData(DataFlavor.stringFlavor);
		}
		catch (HeadlessException | UnsupportedFlavorException | IOException e1)
		{
			e1.printStackTrace();
		}
	}
	
	public void display()
	{
		for (int i=0; i<stringParser.getNumberOfWords(); i++)
		{
			myString = stringParser.getWord(i);
			refreshMainFrame();
			
			//sleep thread
			try
			{
				Thread.sleep(500);
			} catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}
	
	
	@Override
	public void actionPerformed(ActionEvent e)
	{
		display();
	}

	@Override
	public void keyPressed(KeyEvent e)
	{
		
	}

	@Override
	public void keyReleased(KeyEvent e)
	{
		
	}

	@Override
	public void keyTyped(KeyEvent e)
	{
		if (e.getKeyChar() == ' ')
		{
			display();
		}
	}
}