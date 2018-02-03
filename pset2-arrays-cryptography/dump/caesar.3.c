#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char CapAlph[25] = { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z }
    char CapAlph[25];
    CapAlph[0] = 'A';
    CapAlph[1] = 'B';
    CapAlph[2] = 'C';
    CapAlph[3] = 'D';
    CapAlph[4] = 'E';
    CapAlph[5] = 'F';
    CapAlph[6] = 'G';
    CapAlph[7] = 'H';
    CapAlph[8] = 'I';
    CapAlph[9] = 'J';
    CapAlph[10] = 'K';
    CapAlph[11] = 'L';
    CapAlph[12] = 'M';
    CapAlph[13] = 'N';
    CapAlph[14] = 'O';
    CapAlph[15] = 'P';
    CapAlph[16] = 'Q';
    CapAlph[17] = 'R';
    CapAlph[18] = 'S';
    CapAlph[19] = 'T';
    CapAlph[20] = 'U';
    CapAlph[21] = 'V';
    CapAlph[22] = 'W';
    CapAlph[23] = 'X';
    CapAlph[24] = 'Y';
    CapAlph[25] = 'Z';
    
    printf("%c", CapAlph[1]);
}