#include <stdio.h>


int main()
{
    int tab[2][2]={1};
    for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
    printf("%d", tab[i][j]);
}