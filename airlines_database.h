
#include <stdio.h>

#ifndef ENEE_150_PROJECT2_AIRLINES_DATABASE_H
#define ENEE_150_PROJECT2_AIRLINES_DATABASE_H
#endif //ENEE_150_PROJECT2_AIRLINES_DATABASE_H
#define MAX_STRING 80
typedef struct airports
{
    char aptcode[4];
    char aptlocation[MAX_STRING];
} airport_type;

typedef struct routes
{
  int route_ID;
  char departurecode[4];
  char arrivalcode[4];
} route_type;

typedef struct flights
{
    int flight_number;
    int route_ID;
    int departure_hour;
    int departure_minute;
    char meridian_designation1;
    int arrival_hour;
    int arrival_minute;
    char meridian_designation2;
    char frequency[MAX_STRING];
} flight_type;

int initialize_database();

void display_menu();

int print_flights(int flight_number);

int print_airports(char *aptcode);

void print_flight_frequency(int i);

void print_time_departure(int i);

void print_time_arrival(int i);

int non_stop_flights(char *departure_apt, char *arrival_apt);

int one_stop_flights(char *departure_apt, char *arrival_apt);

void print_meridian_designation1(int i);

void print_meridian_designation2(int i);

void print_departure_location_code(int i);

void print_arrival_location_code(int i);

void print_departures_to(char *i);

void print_arrivals_from(char *i);

int print_non_stop_flights(int day, int route, char *departure_location, char *departure_apt, char*arrival_location, char *arrival_apt);

int check_layover(int day, int route_one, int route_two, char *departure_location, char *departure_apt, char*arrival_location, char *arrival_apt);

int check_day(int day,int route_index);

int check_time(int flight_one,int flight_two);

int print_flights_one_stop(int flight_number);

int process_user_input(int user_input);