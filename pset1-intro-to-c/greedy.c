#include <stdio.h>
#include <cs50.h>

int main(void)
{
   
    float Change_Owed;
    do
    {
    //Prompt user for change owed
    printf("How much change is owed?");
    Change_Owed = get_float();
    }
    while (Change_Owed<0);
    
    //Creates a variable for cents, rounds up to the nearest cent (due to C's truncation of numbers)
    int Cents = (int) ((Change_Owed+0.005)*100);

    //Counts the coins while reducing the unaccounted cents variables
    //Divides by 25(quarters), then 10(dimes), then 5(nickels), then 1(pennies)
    int Coin_Count;
    Coin_Count = 0;
    Coin_Count += Cents/25;
    Cents -= Cents/25 * 25;
    Coin_Count += Cents/10;
    Cents -= Cents/10 * 10;
    Coin_Count += Cents/5;
    Cents -= Cents/5 * 5;
    Coin_Count += Cents;
    Cents -= Cents;

    printf("%i\n", Coin_Count);
}
