#include<stdio.h>

char string[11], substring[4], *availability;

void check(char one[4], char two[11])
{
    for (int i=0; i<=7; i++)
    {
        if ((one[0] == two[i])&(one[1] == two[i+1])&(one[2] == two[i+2]))
        {
            availability="Yes, there is.";
            i=11;
        }
        else
            availability="No, there isn't.";
    }
    printf("Answer: %s\n",availability);
}

int main(void)
{

    printf("Question:Is there a substring in the string?\n");
    printf("Input string of 10 characters:\n");
    scanf("%c%c%c%c%c%c%c%c%c%c%c",&string[0],&string[1],&string[2],&string[3],&string[4],&string[5],&string[6],&string[7],&string[8],&string[9], &string[10]);
    printf("Input substring of 3 characters:\n");
    scanf("%c%c%c%c",&substring[0],&substring[1],&substring[2], &substring[3]);
    check(substring, string);

    return 0;
}