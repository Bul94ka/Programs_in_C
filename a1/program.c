#include <stdio.h>
#include <string.h>


int main() 
{
    int d, m, y;
    char date[11];
    while(1)
    {
        if(fgets(date, 11, stdin) == NULL) 
        {
            break;
        }
        char *dot = strchr(date, '.');
        if(dot == NULL) 
        {
            /*puts("Neplatny datum.\n");*/
            break;
        }
        dot = strchr(dot+1, '.');
        if(dot == NULL) 
        {
            /*puts("Neplatny datum.\n");*/
            break;
        }
        if(sscanf(date, "%d.%d.%d", &d, &m, &y) != 3) 
        {
            continue;
        }
           
        if(y < 1900 || y > 2100) 
        {
            puts("Neplatny datum.\n");
            continue;
        }

        int d_in_m;
        switch(m) 
        {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                d_in_m = 31;
                break;
            case 4: case 6: case 9: case 11:
                d_in_m = 30;
                break;
            case 2:
                d_in_m = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 29 : 28;
                break;
            default:
                puts("Neplatny datum");
                break;
        }
        if(d < 1 || d > d_in_m) 
        {
            puts("Neplatny datum");
            continue;
        }
        d += 7;
        if(d > d_in_m) 
        {
            d -= d_in_m;
            m++;
            if(m > 12) 
            {
                m = 1;
                y++;
            }
        }
        if(d >= 10 && m >= 10)
        {
            printf("%2d.%2d.%4d\n",d, m, y);
            printf("\n");
        }
        else if(d >= 10 && m < 10)
        {
            printf("%2d.%d.%4d\n",d, m, y);
            printf("\n");
        }
        else if(d < 10 && m >= 10)
        {
            printf("%d.%2d.%4d\n",d, m, y);
            printf("\n");
        }
        else
        {
            printf("%d.%d.%4d\n",d, m, y);
            printf("\n");
        }
        
    }
    
    return 0;
}