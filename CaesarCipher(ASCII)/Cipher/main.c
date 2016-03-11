#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRINGSIZE 10000
#define ASCIISIZE 95

void fgetsFix(char* input)
{
    int index = 0;

    while(input[index] != '\n')
        index++;

    input[index] = '\0';
}

void promptUser(int *shift, char *input)
{
    //prompt user for shift amount
    printf("How much would you like to shift by?\n");
    fgets(input,STRINGSIZE,stdin);
    fgetsFix(input);
    *shift = atoi(input);

    //prompt user for string to cipher
    printf("What text would you like to cipher?\n");
    fgets(input,STRINGSIZE,stdin);
    fgetsFix(input);
    printf("\n");
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

int main()
{
    //define variables
    int shift;
    int i;
    int tempIndex;
    char tempChar;
    char *again;
    char *input;
    char *output;
    char *asciiTable;
    char *cipherTable;

    //allocate memory (+1 because of null terminating character)
    input = malloc(sizeof(*input)*(STRINGSIZE+1));
    output = malloc(sizeof(*output)*(STRINGSIZE+1));
    asciiTable = malloc(sizeof(*asciiTable)*(ASCIISIZE+1));
    cipherTable = malloc(sizeof(*cipherTable)*(ASCIISIZE+1));
    again = malloc(sizeof(*again)*3);

    //fill in ascii table
    strcpy(asciiTable," !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

    //load y into initial value of again
    strcpy(again,"y");

    //loop if wanted
    while (strcmp(again,"n") != 0 && strcmp(again,"N") != 0 )
    {
        //prompt the user for shift amount and string to cipher
        promptUser(&shift,input);

        //shift ascii table by shifter to create new table
        for (i=0; i<ASCIISIZE; i++)
            cipherTable[i] = asciiTable[(i+shift)%ASCIISIZE];

        //add null terminating character to cipherTable
        cipherTable[ASCIISIZE] = '\0';

        //cipher the input string
        for(i=0; i<strlen(input); i++)
        {
            tempChar = input[i];

            //find the index of the input character in the ascii table
            tempIndex = indexOf(tempChar,asciiTable);

            //if the character was not found in the table, print error message and set i to something weird
            if (tempIndex == -1)
            {
                printf("Error: The message does not use characters 32-126 of ascii\n");
                i=strlen(input)+1;
            }

            //write the correct ciphered text into the output string
            output[i] = cipherTable[tempIndex];
        }

        //add a null terminating character
        output[strlen(input)] = '\0';


        //print the ciphered string if no errors with ciphering
        if (i != strlen(input)+1)
            printf("The ciphered message is:\n%s\n\n",output);

        //prompt user to run again
        printf("Run again?\n[y/n]?\n");
        fgets(again,3,stdin);
        fgetsFix(again);
    }

    //free memory before exiting
    free(input);
    free(output);
    free(asciiTable);
    free(cipherTable);
    free(again);

    return 1;
}
