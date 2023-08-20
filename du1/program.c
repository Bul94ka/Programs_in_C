#include <stdio.h>

#define MAX_BYTES 409

int main() 
{
    int c;
    int b = 0;
    int count = 0; 
    
    while ((c = getchar()) != EOF && b < MAX_BYTES - 1) 
    {
        if (c == '\n' ) 
        {
            count++; 
        }
        else if (c >= 'a' && c <= 'z') 
        {
            c = c - 'a' + 'A'; 
        }
        else if (c >= 'A' && c <= 'Z') 
        {
            c = c - 'A' + 'a'; 
        }
        

        putchar(c);

        b++;     
    }
   
    printf("\nPočet riadkov: %d\n", count);

    return 0;
}









