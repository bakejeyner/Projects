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
	public long speed;
	
	//declare components
	public Container mainContainer;
	public JLabel stringDisplay;
	public JButton startButton;
	public JPanel speedPanel;
	public JTextField speedField;
	public JLabel speedDisplay;
	
	public MainFrame()
	{	
		//initialize variables
		myString = "Please Press the Start Button!";
		stringParser = new StringParser(myString);
		speed = 400;
		
		//initialize components
		mainContainer = this.getContentPane();
		stringDisplay = new JLabel(myString,0);
		stringDisplay.setFont(new Font("Dialog", Font.PLAIN, 24));
		startButton = new JButton("Start");
		speedField = new JTextField("400");
		speedField.setSize(new Dimension(100,100));
		speedDisplay = new JLabel("Speed(WPM)",0);
		speedDisplay.setSize(new Dimension(100,100));
		speedPanel = new JPanel();
		
		//initialize listeners
		startButton.addActionListener(this);
		this.addKeyListener(this);
		
		//set layout
		mainContainer.setLayout(new BorderLayout());
		speedPanel.setLayout(new GridLayout(0,1));
		
		//add componenets to speedFrame
		speedPanel.add(new JLabel());
		speedPanel.add(new JLabel());
		speedPanel.add(new JLabel());
		speedPanel.add(speedDisplay);
		speedPanel.add(speedField);
		speedPanel.add(new JLabel());
		speedPanel.add(new JLabel());
		speedPanel.add(new JLabel());
		
		
		//add components to MainFrame
		mainContainer.add(startButton, BorderLayout.PAGE_END);
		mainContainer.add(stringDisplay, BorderLayout.CENTER);
		mainContainer.add(speedPanel, BorderLayout.LINE_END);
		
		//display
		this.setFocusable(true);
		this.setSize(700,300);
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
	
	public void getSpeed()
	{
		//get speed from textField
		speed = Long.parseLong(speedField.getText(),10);
	}
	
	public void display()
	{
		getString();
		getSpeed();
		stringParser.setString(myString);
		for (int i=0; i<stringParser.getNumberOfWords(); i++)
		{
			myString = stringParser.getWord(i);
			refreshMainFrame();
			
			//sleep thread
			try
			{
				Thread.sleep(100000/speed);
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