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

    printf("%i\n", Coin_Count);
    
}
