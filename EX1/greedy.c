#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // ask for change
    printf("O Hai. How much change is owed?\n");
    // get floating value
    float change = GetFloat();
    // check if float is positive
    if (change < 0.0)
    {
        // keep checking until value is positive
        do
        {
            printf("How much change is owed?\n");
            change = GetFloat();
        }
        while(change <= 0.00);
    }
    // add more values to the floating point to increase accuracy
    change = change + .0001;
    // convert the floating value to an integer of 100 times it's size
    int ch100= (int) (change * 100);
    int coins = 0;
    // determine if change can be given in quarters
    if (ch100 >= 25)
    {
        // this pattern will be followed by all next parts of the program
        coins = ch100 / 25;
        ch100 = ch100 - (coins * 25);
    }
    // if possible to give dimes, give dimes.
    if (ch100 >= 10)
    {
        int dimes;
        dimes = ch100 / 10;
        coins = coins + dimes;
        ch100 = ch100 - (dimes * 10);
    }
    // if possible to give nickels, give nickels
    if ( ch100 >= 5 )
    {
        int nicks;
        nicks = ch100 / 5;
        coins = coins + nicks;
        ch100 = ch100 - (nicks * 5);
    }
    // if possible to give dimes, give dimes
    if ( ch100 >= 1)
    {
        int pennies;
        pennies = ch100;
        coins = coins + pennies;
        ch100 = ch100 - pennies;
    }
    // print the total number of coins
    printf("%d\n",coins);
}
