#include "airlines_database.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <math.h>
airport_type airports[100];
route_type routes[500];
flight_type flights[3000];
int num_airports = 0;
int num_routes = 0;
int num_flights = 0;
int initialize_database()
{
    char line[MAX_STRING];
    int i=0;//array index
    char trash;//variable to hold garbage character
    memset(line,'\0',MAX_STRING);
    int initializestatus = 1;//1 is pass zero is fail
    FILE *airports_file;
    FILE *routes_file;
    FILE *flights_file;
    airports_file = fopen("airports.txt","r");
    routes_file = fopen("routes.txt","r");
    flights_file = fopen("flights.txt","r");
    if(airports_file==NULL || routes_file==NULL || flights_file==NULL)
    {
        printf("Could not open database files\n");
        initializestatus = 0;
    }
    else
    {
        while(fgets(line,MAX_STRING,airports_file)!=NULL)
        {
            sscanf(line,"%s %[^\r\n]s",airports[i].aptcode,airports[i].aptlocation);
            if(i<10)
            {
                //printf("%s %s\n",airports[i].aptcode,airports[i].aptlocation);
            }
            i++;
            memset(line,'\0',MAX_STRING);
        }
        fclose(airports_file);
        num_airports = i;
        i = 0;
        while(fgets(line,MAX_STRING,routes_file)!=NULL)
        {
           sscanf(line,"%d %c %s %s",&routes[i].route_ID,&trash,routes[i].departurecode,routes[i].arrivalcode);
            if(i<10)
            {
                //printf("%d %c %s %s\n",routes[i].route_ID,trash,routes[i].departurecode,routes[i].arrivalcode);
            }
           i++;
           memset(line,'\0',MAX_STRING);
        }
        fclose(routes_file);
        num_routes = i;
        i=0;
        while(fgets(line,MAX_STRING,flights_file)!=NULL)
        {
           sscanf(line,"%d %d %d %c %d %c %d %c %d %c %s",&flights[i].flight_number,&flights[i].route_ID,&flights[i].departure_hour,&trash,&flights[i].departure_minute,&flights[i].meridian_designation1,&flights[i].arrival_hour,&trash,&flights[i].arrival_minute,&flights[i].meridian_designation2,flights[i].frequency);
            if(i<10)
            {
                //printf("%d %d %d %c %d %c %d %c %d %c %s\n",flights[i].flight_number,flights[i].route_ID,flights[i].departure_hour,trash,flights[i].departure_minute,flights[i].meridian_designation1,flights[i].arrival_hour,trash,flights[i].arrival_minute,flights[i].meridian_designation2,flights[i].frequency);
            }
           i++;
           memset(line,'\0',MAX_STRING);
        }
        fclose(flights_file);
        num_flights=i;
    }
    return initializestatus;
}

void display_menu()
{
    printf("Choose an option:\n");
    printf("1.  Print a flight\n");
    printf("2.  Print an airport\n");
    printf("3.  Find non-stop flights\n");
    printf("4.  Find 1-stop flights\n");
    printf("5.  Exit\n");
    printf("Enter option:  ");
}

int print_flights(int flight_number)
{
int i=0;
int returnstatus=0;//0 fail 1 success
for(i=0;i<num_flights;i++)
{
    if(flights[i].flight_number==flight_number)
    {
        returnstatus=1;
        printf("\nFlight %d ",flights[i].flight_number);
        print_flight_frequency(i);
        printf("\n    ");
        print_time_departure(i);
        print_meridian_designation1(i);
        print_departure_location_code(i);
        printf("\n    ");
        print_time_arrival(i);
        print_meridian_designation2(i);
        print_arrival_location_code(i);
        printf("\n");
        break;
    }
}
    if(returnstatus==0)
    {
        printf("Flight %d doesn't exist",flight_number);
    }
    return returnstatus;
}

int print_airports(char *aptcode)
{
    int returnstatus = 0;
    int i=0;
    for(i=0;i<num_airports;i++)
    {
        if(strcmp(airports[i].aptcode,aptcode)==0)
        {
            returnstatus=1;
            printf("\n%s (%s)\n",airports[i].aptlocation,airports[i].aptcode);
            printf("\n");
            print_departures_to(airports[i].aptcode);
            printf("\n");
            print_arrivals_from(airports[i].aptcode);
            printf("\n");
        }
    }
    if(returnstatus==0)
    {
        printf("Airport %s doesn't exist\n",aptcode);
    }
    return returnstatus;
}

void print_flight_frequency(int i)
{
    char weekdays[]="SMTWThFSa";
    char weekdays_edited[sizeof(weekdays)];
    memset(weekdays_edited, '\0',sizeof(weekdays_edited));
    char Daily[]="Daily";
    const char day_strings[7][3]={"S","M","T","W","Th","F","Sa"};
    int j=0;
    int k=0;
    if(strcmp(flights[i].frequency,Daily)==0)
    {
        printf("(%s)",weekdays);
    }
    else if(flights[i].frequency[0]=='X')
    {
        for(j=1;j<strlen(flights[i].frequency);j++)
        {
            if((flights[i].frequency[j]-'0')<=4)
            {
                weekdays[(flights[i].frequency[j]-'0')-1]=' ';
            }
            else if((flights[i].frequency[j]-'0')==5)
            {
                weekdays[4]=' ';
                weekdays[5]=' ';
            }
            else if((flights[i].frequency[j]-'0')==6)
            {
                weekdays[6]=' ';
            }
            else if((flights[i].frequency[j]-'0')==7)
            {
                weekdays[7]=' ';
                weekdays[8]=' ';
            }
        }
        for(j=0;j<strlen(weekdays);j++)
        {
            if(weekdays[j]!=' ')
            {
                weekdays_edited[k]=weekdays[j];
                k++;
            }
        }
        printf("(%s)",weekdays_edited);
    }
    else
    {
        printf("(");
        for(j=0;j<strlen(flights[i].frequency);j++)
        {
            printf("%s",day_strings[(flights[i].frequency[j]-'0')-1]);
        }
        printf(")");
    }
}

void print_time_arrival(int i)
{
    if(flights[i].arrival_hour<10)
    {
        if (flights[i].arrival_minute < 10)
        {
            printf("0%d:0%d", flights[i].arrival_hour, flights[i].arrival_minute);
        }
        else
            {
                printf("0%d:%d", flights[i].arrival_hour, flights[i].arrival_minute);
            }
    }
    else
    {
        if (flights[i].arrival_minute < 10)
        {
            printf("%d:0%d", flights[i].arrival_hour, flights[i].arrival_minute);
        }
        else
        {
            printf("%d:%d", flights[i].arrival_hour, flights[i].arrival_minute);
        }
    }
}

void print_time_departure(int i)
{
    if(flights[i].departure_hour<10)
    {
        if (flights[i].departure_minute < 10)
        {
            printf("0%d:0%d", flights[i].departure_hour, flights[i].departure_minute);
        }
        else
        {
            printf("0%d:%d", flights[i].departure_hour, flights[i].departure_minute);
        }
    }
    else
    {
        if (flights[i].departure_minute < 10)
        {
            printf("%d:0%d", flights[i].departure_hour, flights[i].departure_minute);
        }
        else
        {
            printf("%d:%d", flights[i].departure_hour, flights[i].departure_minute);
        }
    }
}

void print_meridian_designation1(int i)
{
    if(flights[i].meridian_designation1=='a')
    {
        printf("a.m. ");
    }
    else
    {
        printf("p.m. ");
    }
}

void print_meridian_designation2(int i)
{
    if(flights[i].meridian_designation2=='a')
    {
        printf("a.m. ");
    }
    else
    {
        printf("p.m. ");
    }
}

void print_departure_location_code(int i)
{
    int j =0;
    int k =0;
    for(j=0;j<num_routes;j++)
    {
        if(routes[j].route_ID==flights[i].route_ID)
        {
            for(k=0;k<num_airports;k++)
            {
                if(strcmp(airports[k].aptcode,routes[j].departurecode)==0)
                {
                    printf("%s (%s)",airports[k].aptlocation,airports[k].aptcode);
                }
            }
        }
    }
}

void print_arrival_location_code(int i)
{
    int j =0;
    int k =0;
    for(j=0;j<num_routes;j++)
    {
        if(routes[j].route_ID==flights[i].route_ID)
        {
            for(k=0;k<num_airports;k++)
            {
                if(strcmp(airports[k].aptcode,routes[j].arrivalcode)==0)
                {
                    printf("%s (%s)",airports[k].aptlocation,airports[k].aptcode);
		//printf("%s",airports[k].aptlocation);
                }
            }
        }
    }
}

void print_departures_to(char *i)
{
    int j=0;
    int k=0;
    printf("Departures to:\n");
    for(j=0;j<num_routes;j++)
    {
        if(strcmp(routes[j].departurecode,i)==0)
        {
            for(k=0;k<num_airports;k++)
            {
                if(strcmp(routes[j].arrivalcode,airports[k].aptcode)==0)
                {
                    printf("   %s (%s)\n",airports[k].aptlocation,airports[k].aptcode);
                }
            }
        }
    }
}

void print_arrivals_from(char *i)
{
    int j=0;
    int k=0;
    printf("Arrivals from:\n");
    for(j=0;j<num_routes;j++)
    {
        if(strcmp(routes[j].arrivalcode,i)==0)
        {
            for(k=0;k<num_airports;k++)
            {
                if(strcmp(routes[j].departurecode,airports[k].aptcode)==0)
                {
                    printf("   %s (%s)\n",airports[k].aptlocation,airports[k].aptcode);
                }
            }
        }
    }
}

int non_stop_flights(char *departure_apt, char *arrival_apt)
{
    int i=0;
    int day=0;
    int returnstatus = 0;
    int departure_index=0;
    int arrival_index=0;
    int departure_status=0;
    int arrival_status=0;
    int printflag=1;
    for(i=0;i<num_airports;i++)
    {
        if(strcmp(airports[i].aptcode,departure_apt)==0)
        {
            departure_index=i;
            departure_status=1;
            break;
        }
    }
    for(i=0;i<num_airports;i++)
    {
        if(strcmp(airports[i].aptcode,arrival_apt)==0)
        {
            arrival_index=i;
            arrival_status=1;
            break;
        }
    }
    if(departure_status==1 && arrival_status==1)
    {
        returnstatus=1;
        printf("Enter a day of the week (1-7, or 0 for all days):  ");
        scanf("%d",&day);
        if(day<0 || day>7)//safety check on input
        {
            printf("Invalid day goodbye!");
            exit(-1);
        }
        for(i=0;i<num_routes;i++)
        {
            if(strcmp(routes[i].departurecode,airports[departure_index].aptcode)==0 && strcmp(routes[i].arrivalcode,airports[arrival_index].aptcode)==0)
            {
                if(print_non_stop_flights(day,routes[i].route_ID,airports[departure_index].aptlocation,departure_apt,airports[arrival_index].aptlocation,arrival_apt)==1)
                {
                    printflag=0;
                    break;
                }
            }
        }
        if(printflag==1)//no valid route found
        {
            printf("Route %s to %s has no non-stop flights on the specified days",departure_apt,arrival_apt);
        }
    }
    else
    {
        printf("Either airport %s or %s doesn't exist",departure_apt,arrival_apt);
    }
    return returnstatus;
}

int print_non_stop_flights(int day, int route, char *departure_location, char *departure_apt, char*arrival_location, char *arrival_apt)
{
    int i=0;
    int j=0;
    int returnstatus = 0;
    int Xstatus=1;
    char Daily[] = "Daily";
    int printflag=1;
    for(i=0;i<num_flights;i++)
    {
        if(flights[i].route_ID == route)
        {
            if (strcmp(flights[i].frequency, Daily) == 0)
            {
                if(printflag==1)
                {
                    printf("\nNon-stop flights from %s (%s) to %s (%s):\n",departure_location, departure_apt, arrival_location, arrival_apt);
                    printflag=0;
                }
                print_flights(flights[i].flight_number);
                returnstatus=1;
            }

            else
            {
                if (flights[i].frequency[0] == 'X')
                {
                    for (j = 1; j < strlen(flights[i].frequency); j++)
                    {
                        if ((flights[i].frequency[j] - '0') == day)
                        {
                            Xstatus=0;
                            break;
                        }
                    }
                    if(Xstatus==1)
                    {
                        if(printflag==1)
                        {
                            printf("\nNon-stop flights from %s (%s) to %s (%s):\n",departure_location, departure_apt, arrival_location, arrival_apt);
                            printflag=0;
                        }
                        print_flights(flights[i].flight_number);
                        returnstatus=1;
                    }
                    else
                    {
                        Xstatus=1;
                    }
                }
                else
                {
                    for (j = 0; j < strlen(flights[i].frequency); j++)
                    {
                        if ((flights[i].frequency[j] - '0') == day)
                        {
                            if(printflag==1)
                            {
                                printf("\nNon-stop flights from %s (%s) to %s (%s):\n",departure_location, departure_apt, arrival_location, arrival_apt);
                                printflag=0;
                            }
                            print_flights(flights[i].flight_number);
                            returnstatus=1;
                        }
                    }
                    if(day==0)
                    {
                        if(printflag==1)
                        {
                            printf("\nNon-stop flights from %s (%s) to %s (%s):\n",departure_location, departure_apt, arrival_location, arrival_apt);
                            printflag=0;
                        }
                        print_flights(flights[i].flight_number);
                        returnstatus=1;
                    }
                }
            }
        }
    }
    return returnstatus;
}

int one_stop_flights(char *departure_apt, char *arrival_apt)
{
    int i=0;
    int j=0;
    int day=0;
    int returnstatus = 0;
    int route_one_index=0;
    int route_two_index=0;
    int departure_index=0;
    int arrival_index=0;
    int departure_status=0;
    int arrival_status=0;
    for(i=0;i<num_airports;i++)
    {
        if(strcmp(airports[i].aptcode,departure_apt)==0)
        {
            departure_index=i;
            departure_status=1;
            break;
        }
    }
    for(i=0;i<num_airports;i++)
    {
        if(strcmp(airports[i].aptcode,arrival_apt)==0)
        {
            arrival_index=i;
            arrival_status=1;
            break;
        }
    }
    if(!(departure_status==1 && arrival_status==1))
    {
        printf("Either airport %s or %s doesn't exist\n",departure_apt,arrival_apt);
    }
    else
    {
        printf("Enter a day of the week (1-7, or 0 for all days):  ");
        scanf("%d",&day);
        if(day<0 || day>7)//safety check on input
        {
            printf("Invalid day goodbye!");
            exit(-1);
        }
        for(i=0;i<num_routes;i++)
        {
            if(strcmp(routes[i].departurecode,departure_apt)==0 && strcmp(routes[i].arrivalcode,arrival_apt)!=0)
            {
                route_one_index=i;
                for(j=0;j<num_routes;j++)
                {
                    if(strcmp(routes[i].arrivalcode,routes[j].departurecode)==0 && strcmp(routes[j].arrivalcode,arrival_apt)==0)
                    {
                        route_two_index=j;
                        if(check_layover(day,route_one_index,route_two_index,airports[departure_index].aptlocation,departure_apt,airports[arrival_index].aptlocation,arrival_apt)==1)
                        {
                            returnstatus=1;
                        }
                    }
                }
            }
        }
        if(returnstatus==0)
        {
            printf("Route %s to %s has no 1-stop flights on the specified days\n",departure_apt,arrival_apt);
        }
    }
    return returnstatus;
}


int check_layover(int day, int route_one, int route_two, char *departure_location, char *departure_apt, char*arrival_location, char *arrival_apt)
{
    static int print_status_check_layover=1;//print status for check layover
    int i=0;
    int j=0;
    int returnstatus=0;
    for(i=0;i<num_flights;i++)
    {
        if(flights[i].route_ID==route_one)
        {
            if(check_day(day, i)==1)
            {
               for(j=0;j<num_flights;j++)
               {
                   if(flights[j].route_ID==route_two)
                   {
                       if(check_day(day,j)==1)
                       {
                           if(check_time(i,j)==1)
                           {
                               returnstatus=1;
                               if(print_status_check_layover==1)
                               {
                                   printf("\n1-stop flights from %s (%s) to %s (%s):\n", departure_location, departure_apt, arrival_location, arrival_apt);
                               print_status_check_layover=0;
                               }
                               print_flights_one_stop(flights[i].flight_number);
                               print_flights_one_stop(flights[j].flight_number);
                               printf("\n");
                           }
                       }
                   }
               }
            }
        }
    }
    return returnstatus;
}
 int check_day(int day, int route_index)
 {
    int j;
    int returnstatus=0;
    int Xstatus=1;
    char Daily[] = "Daily";
     if (strcmp(flights[route_index].frequency, Daily) == 0)
     {
         returnstatus=1;
     }
     else
         {
         if (flights[route_index].frequency[0] == 'X')
         {
             for (j = 1; j < strlen(flights[route_index].frequency); j++)
             {
                 if ((flights[route_index].frequency[j] - '0') == day)
                 {
                     Xstatus = 0;
                     break;
                 }
             }
             if (Xstatus == 1)
             {
                 returnstatus = 1;
             }
             else
                 {
                    Xstatus = 1;
                 }
         }
         else
             {
             for (j = 0; j < strlen(flights[route_index].frequency); j++)
             {
                 if ((flights[route_index].frequency[j] - '0') == day)
                 {
                     print_flights(flights[route_index].flight_number);
                     returnstatus = 1;
                 }
             }
             if (day == 0)
             {
                 returnstatus = 1;
             }
         }
     }
     return returnstatus;
 }

int check_time(int flight_one,int flight_two)
{
    int time_one=0;
    int time_two=0;
    //printf("flight one: %d",flights[flight_one].flight_number);
    //printf("flight two: %d",flights[flight_two].flight_number);
    int returnstatus=0;
    if(flights[flight_one].meridian_designation2=='a')
    {
        time_one=(flights[flight_one].arrival_hour)*60 + flights[flight_one].arrival_minute;
    }
    else
    {
        time_one=(flights[flight_one].arrival_hour)*60 + 12*60 + flights[flight_one].arrival_minute;
    }
    if(flights[flight_two].meridian_designation1=='a')
    {
        time_two=(flights[flight_two].departure_hour)*60 + flights[flight_two].departure_minute;
    }
    else
    {
        time_two=(flights[flight_two].departure_hour)*60 + 12*60 + flights[flight_two].departure_minute;
    }
    if((time_two-time_one)>=60 && (time_two-time_one)<=120)
    {
        returnstatus=1;
    }
    return returnstatus;
}

int print_flights_one_stop(int flight_number)
{
    int i=0;
    int returnstatus=0;//0 fail 1 success
    for(i=0;i<num_flights;i++)
    {
        if(flights[i].flight_number==flight_number)
        {
            returnstatus=1;
            printf("\nFlight %d ",flights[i].flight_number);
            print_flight_frequency(i);
            printf("\n    ");
            print_time_departure(i);
            print_meridian_designation1(i);
            print_departure_location_code(i);
            printf("\n    ");
            print_time_arrival(i);
            print_meridian_designation2(i);
            print_arrival_location_code(i);
            break;
        }
    }
    if(returnstatus==0)
    {
        printf("Flight %d doesn't exist",flight_number);
    }
    return returnstatus;
}

int process_user_input(int user_input)
{
    int returnstatus=0;//1 means terminate program
    if(user_input==1)
    {
        int user_flight_number=0;
        printf("Enter a flight number:  ");
        scanf("%d",&user_flight_number);
        print_flights(user_flight_number);
        printf("\n");
    }
    else if(user_input==2)
    {
        char user_apt_code[4];
        printf("Enter airport code:  ");
        scanf("%s",user_apt_code);
        print_airports(user_apt_code);
    }
    else if(user_input==3)
    {
        char departure_apt[4];
        char arrival_apt[4];
        printf("Enter departure and arrival airport codes:  ");
        scanf("%s %s",departure_apt,arrival_apt);
        non_stop_flights(departure_apt,arrival_apt);
        printf("\n");
    }
    else if(user_input==4)
    {
        char one_stop_departure_apt[4];
        char one_stop_arrival_apt[4];
        printf("Enter departure and arrival airport codes:  ");
        scanf("%s %s",one_stop_departure_apt,one_stop_arrival_apt);
        one_stop_flights(one_stop_departure_apt,one_stop_arrival_apt);
        printf("\n");
    }
    else if(user_input==5)
    {
        returnstatus=1;
    }
    return returnstatus;
}