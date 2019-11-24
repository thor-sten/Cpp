//
//  Kattis puzzle: Reversebinary
//  Thorsten on 2016-12
//

#include <stdio.h>

int main()
{
    unsigned int input, output=0, power=1, i, j;
    unsigned int binary[32]={0};    //empty array for 32bit binary number

    scanf("%d", &input);

    //convert input to binary:
    for(i=0; input!=0; i++)
    {
        binary[i]=(input%2);        //"division by two with remainder" method, gives reversed order
        input/=2;
    }

    //convert binary to integer:
    while(i>0)
    {
        if(binary[i-1]==1)
            output+=power;
        power*=2;                   //2^1, 2^2=2^1*2, 2^3=2^2*2, ...
        i--;
    }

    printf("%d\n", output);

    return 0;
}
