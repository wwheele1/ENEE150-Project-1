#include <stdio.h>
#include "airlines_database.h"
#include <stdlib.h>
int main()
{
    int exit_loop=0;
    int user_input=0;
    if(initialize_database()==1)
    {
        printf("Welcome to the ENEE Airlines Flight Database\n");
        display_menu();
        while(exit_loop==0)
        {
            scanf("%d",&user_input);
            if(user_input<1 || user_input>5)
            {
                printf("Invalid option.  Try again.\n");
                printf("Enter option:  ");
            }
            else
            {
                if(process_user_input(user_input)==1)
                {
                    exit_loop=1;
                }
                else
                {
                    display_menu();
                }
            }
        }
    }
    else
    {
        exit(-1);
    }
}