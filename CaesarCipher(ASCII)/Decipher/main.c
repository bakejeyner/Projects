#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRINGSIZE 10000
#define ASCIISIZE 95
#define SETSIZE 4
#define WORDSIZE 50

void fgetsFix(char* input)
{
    int index = 0;

    while(input[index] != '\n')
        index++;

    input[index] = '\0';
}

void promptUser(char *input)
{
    //prompt user for string to cipher
    printf("What text would you like to decipher?\n");
    fgets(input,STRINGSIZE,stdin);
    fgetsFix(input);
    printf("\n\n");
}

int indexOf(char character, char *array)
{
    int i;

    for (i=0; i<strlen(array); i++)
    {
        if (array[i] == character)
            return i;
    }

    return -1;
}

void resolveChar(char *temp)
{
    int i;
    int flag;

    flag = 0;

    //check to see if character is upper case
    for (i=0; i<26; i++)
        if (*temp == i+65)
            flag = 1;

    //if it is upper case, make it lower case
    if (flag == 1)
        *temp = *temp+32;
}

int findInFile(char *String)
{
    int flag;
    int i;
    FILE *fp;
    char *temp;
    char *filename;
    char *read;

    //allocate memory
    filename = malloc(sizeof(*filename)*17);
    read = malloc(sizeof(*read)*WORDSIZE);


    temp = &String[0];

    //set the uppercase to lowercase
    resolveChar(temp);

    flag = 0;
    //set flag if word doesn't start with a letter
    for (i=0; i<26; i++)
        if(97+i == *temp)
            flag = 1;

    //if the flag was not set, return 0 to indicate miss
    if (flag == 0)
        return 0;

    //set up filename
    strcpy(filename,"Dictionary/ .txt");
    filename[11] = *temp;

    //open the file
    if ((fp =fopen(filename,"r")) == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }

    //keep reading through the file to try and find a match
    while (fgets(read,WORDSIZE,fp) != NULL)
    {
        fgetsFix(read);
        if (strcmp(String,read) == 0)
        {
            fclose(fp);
            free(filename);
            free(read);
            return 1;
        }
    }

    fclose(fp);
    free(filename);
    free(read);
    return 0;
}

void displayResults(char *output[])
{
    int i;
    int j;
    char *ratioChar[SETSIZE];

    //allocate memory
    for (i=0; i<SETSIZE; i++)
        ratioChar[i] = malloc(sizeof(char)*5);

    //copy the last 3 digits into ratioChar
    for (i=0; i<SETSIZE; i++)
        for (j=0; j<3; j++)
            ratioChar[i][j] = output[i][j+STRINGSIZE+1];

    //add a null terminating character
    for (i=0; i<SETSIZE; i++)
        ratioChar[i][3] = '\0';

    //print the results
    for (i=0; i<SETSIZE-1; i++)
    {
        if (strcmp(ratioChar[i],"") == 0 || strcmp(ratioChar[i],"0") == 0)
            printf("The %dth place match had no matches.\n\n",i+1);
        else
            printf("The %dth place match with a success rate of %s:\n\n%s\n\n",i+1,ratioChar[i],output[i]);
    }
}

void sortOutput(char *output[])
{
    int i;
    int j;
    int ratioInt[SETSIZE];
    char *temp;
    char *ratioChar[SETSIZE];

    //allocate memory
    for (i=0; i<SETSIZE; i++)
            ratioChar[i] = malloc(sizeof(char)*5);
    temp = malloc(sizeof(char)*STRINGSIZE+5);

    //copy the last 3 digits into ratioChar
    for (i=0; i<SETSIZE; i++)
        for (j=0; j<4; j++)
            ratioChar[i][j] = output[i][j+STRINGSIZE+1];

    //convert ratioChar into ratioInt
    for (i=0; i<SETSIZE; i++)
    {
        ratioChar[i][3] = '\0';
        ratioInt[i] = atoi(ratioChar[i]);
    }

    //organize the ratioInts from greatest to least
    for (i=3; i>=1; i--)
    {
        if (ratioInt[i] > ratioInt[i-1])
        {
            //swap the strings
            memcpy(temp,output[i],STRINGSIZE+5);
            memcpy(output[i],output[i-1],STRINGSIZE+5);
            memcpy(output[i-1],temp,STRINGSIZE+5);

            //swap the ratios to compare
            ratioInt[i-1] = ratioInt[i];
        }
    }

    //free memory
    for (i=0; i<SETSIZE; i++)
            free(ratioChar[i]);

    free(temp);
}

int main()
{
    //define variables
    int i;
    int j;
    int k;
    int words;
    int successes;
    int ratio;
    char *ratioChar;
    int tempIndex;
    char tempChar;
    char *again;
    char *input;
    char *output[SETSIZE];
    char *token;
    char *tokenData;
    char *asciiTable;
    char *cipherTable;

    //allocate memory (+1 because of null terminating character)
    input = malloc(sizeof(*input)*(STRINGSIZE+1));
    asciiTable = malloc(sizeof(*asciiTable)*(ASCIISIZE+1));
    cipherTable = malloc(sizeof(*cipherTable)*(ASCIISIZE+1));
    again = malloc(sizeof(*again)*3);
    ratioChar = malloc(sizeof(*ratioChar)*5);
    tokenData = malloc(sizeof(char)*STRINGSIZE+5);

    for (i=0; i<SETSIZE; i++)
    {
        output[i] = malloc(sizeof(char)*STRINGSIZE+5);
    }

    //fill in ascii table
    strcpy(asciiTable," !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

    //load y into initial value of again
    strcpy(again,"y");

    //loop if wanted
    while (strcmp(again,"n") != 0 && strcmp(again,"N") != 0 )
    {
        //reset output array
        for (i=0; i<SETSIZE; i++)
            memset(output[i],0,sizeof(char)*STRINGSIZE+5);

        //prompt the user for shift amount and string to cipher
        promptUser(input);

        //Brute Force Hack: do this for all 95 cases
        for (i=0; i<ASCIISIZE; i++)
        {
            words = 0;
            successes = 0;

            //shift ascii table by shifter to create new table
            for (j=0; j<ASCIISIZE; j++)
                cipherTable[j] = asciiTable[(j+i)%ASCIISIZE];

            //add null terminating character to cipherTable
            cipherTable[ASCIISIZE] = '\0';

            //cipher the input string
            for(j=0; j<strlen(input); j++)
            {
                tempChar = input[j];

                //find the index of the input character in the ascii table
                tempIndex = indexOf(tempChar,asciiTable);

                //if the character was not found in the table, print error message and set i to something weird
                if (tempIndex == -1)
                {
                    printf("Error: The message does not use characters 32-126 of ascii\n");
                    j=strlen(input)+1;
                }

                //write the correct ciphered text into the output string
                output[SETSIZE-1][j] = cipherTable[tempIndex];
            }

            //add a null terminating character
            output[SETSIZE-1][strlen(input)] = '\0';

            //copy the output to a string that holds the data to tokenize
            strcpy(tokenData,output[SETSIZE-1]);

            //continue if no error
            if (j != strlen(input)+1)
            {
                token = strtok(tokenData," ");

                //while the input can still be tokenized
                do
                {
                    words++;

                    //findInFile returns 1 if found and 0 if not found
                    successes += findInFile(token);

                } while ((token = strtok(NULL," ")) != NULL);

                //set ratio
                ratio = successes*100/words;
                itoa(ratio,ratioChar,10);

                //parse ratio to the end of output
                for(k=0; k<3; k++)
                    output[SETSIZE-1][k+STRINGSIZE+1] = ratioChar[k];

                //add a null terminating character
                output[SETSIZE-1][STRINGSIZE+4] = '\0';

                sortOutput(output);
            }
        }

        //display results
        displayResults(output);

        //prompt user to run again
        printf("Run again?\n[y/n]?\n");
        fgets(again,3,stdin);
        fgetsFix(again);
    }

    //free memory before exiting
    free(input);
    free(asciiTable);
    free(cipherTable);
    free(again);
    free(ratioChar);
    free(tokenData);

    for (i=0; i<SETSIZE; i++)
        free(output[i]);

    return 1;
}
