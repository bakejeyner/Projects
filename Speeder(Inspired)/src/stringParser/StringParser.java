package stringParser;

import java.util.StringTokenizer;

public class StringParser
{
	private int numberOfWords;
	private String[] wordArray = new String[10000];
	private StringTokenizer stringTokenizer;
	
	//constructor
	public StringParser(String stringToParse)
	{
		setString(stringToParse);
	}
	
	
	public void setString(String stringToParse)
	{
		numberOfWords = 0;
		stringTokenizer = new StringTokenizer(stringToParse, " ");
		parseString();
	}
	
	public void parseString()
	{
		//go through the long string and sort into word array
		while (stringTokenizer.hasMoreTokens())
		{
			wordArray[numberOfWords] = stringTokenizer.nextToken();
			numberOfWords++;
		}
	}
	
	public String getWord(int index)
	{
		return wordArray[index];
	}
	
	public int getNumberOfWords()
	{
		return numberOfWords;
	}
}
