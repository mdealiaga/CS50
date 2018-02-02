#include <stdio.h>
#include <cs50.h>

int main(void)
{
   
    float Change_Owed;
    do
    {
    printf("How much change is owed?");
    Change_Owed = get_float();
    }
    while (Change_Owed<0);
    
    int Cents = (int) (Change_Owed * 100);

    int Coin_Count;
    Coin_Count = 0;
    Coin_Count += Cents/25;
    Cents -= Cents/25 * 25;
    printf("%i after quarters dealt with\n", Cents);
    Coin_Count += Cents/10;
    Cents -= Cents/10 * 10;
    printf("%i after dimes dealt with\n", Cents);
    Coin_Count += Cents/5;
    Cents -= Cents/5 * 5;
    printf("%i after nickels dealt with\n", Cents);
    Coin_Count += Cents;
    Cents -= Cents;
    printf("%i after pennies dealt with\n", Cents);

    printf("%i\n", Coin_Count);
    
}
