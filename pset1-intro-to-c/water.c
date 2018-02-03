#include <stdio.h>
#include <cs50.h>

int main(void)
{
//prompts user for minutes spent showering
printf("How many minutes do you usually spend showering?\n");
int minutes = get_int();
//prints value multiplied by 12
printf("You use %i bottles of water\n", minutes * 12);
}