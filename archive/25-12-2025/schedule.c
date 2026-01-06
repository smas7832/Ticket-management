#include "schedule.h"
#include "train.h"
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>

void set_time(schedule input_schedule, schedule *o_schedule) {}
/*
typedef struct schedule {
  schdl_status status; // flag for status of schedule
  char departure_station[NAME_LEN];
  char arrival_station[NAME_LEN];
  struct tm departure_timendate; // Departure time for
  struct tm arrival_timendate;
} schedule;*/

int change_schdl_status(schedule **curr_schedule, schdl_status status) {  
  (*curr_schedule)->schdl_status = status;
  if ((*curr_schedule)->schdl_status == status)
    return 1;
  else
    return 0;
}
int get_schdl_status(schedule *curr_schedule) {
  return (*curr_schedule).schdl_status;
}

int change_depart_station(train **curr_train, char station[]) {
  char *validate =
      strcpy((*curr_train)->train_schedule.departure_station, station);
  if (*validate == *station) {
    return 0;
  }
  return 1;
}

int change_arrival_station(train **curr_train, char station[]) {
  char *validate =
      strcpy((*curr_train)->train_schedule.arrival_station, station);
  if (*validate == *station) {
    return 0;
  }
  return 1;
}

int print_depart_station(schedule *curr_schedule) {
  if (curr_schedule->departure_station[0] != '\0') {
    puts(curr_schedule->departure_station);
    return 1;
  }
  return 0;
}

void print_schedule(schedule *curr_schedule) {
  // Validation check
  if (get_schdl_status(curr_schedule) == UNSET ||
      get_schdl_status(curr_schedule) == PARTIAL) {
    printf("\nError: Schedule is not set yet.");
    return;
  }
  char buffer[30];
  strftime(buffer, 30, "%x %X", &(curr_schedule->departure_timendate));
  printf("\nDeparture Date and Time:\t");
  puts(buffer);
  printf("\nDeparture Station:\t%s", curr_schedule->departure_station);
  strftime(buffer, 30, "%x %X", &(curr_schedule->arrival_timendate));
  printf("\nArrival Date, Time:\t");
  puts(buffer);
  printf("\nArrival Station:\t%s", curr_schedule->arrival_station);
}

void add_schedule(train **curr_train) {
  puts("Enter Departure station name:");
  char *station;
  scanf("%49s", station);
  int status = change_depart_station(curr_train, station);
  if (status != 0) {
    puts("Failed to Update Departure station name.");
  }
  puts("Enter Arrival station name:");
  scanf("%49s", station);
  change_arrival_station(curr_train, station);
  if (status != 0) {
    puts("Failed to Update Arrival station name.");
  }

  int hr, min, mday, month, year;
  puts("Enter Departure Date (dd/mm/yyyy): ");

  do {
    scanf("%d/%d/%d", &mday, &month, &year);
    if (mday > 31 || month > 12 || year < 1900) {
      printf("\nPlease enter Valid Departure Date:");
    }
  } while (mday > 31 || month > 12 || year < 1900);

  puts("Enter Departure Time and Date (HH:mm): ");
  do {
    scanf("%d:%d", &hr, &min);
    if (hr > 23 || min > 59) {
      printf("\nPlease enter Valid Departure Time:");
    }
  } while (hr > 23 || min > 59);
  struct tm *time =
      &((*curr_train)->train_schedule.departure_timendate);

  time->tm_hour = hr;
  time->tm_min = min;
  time->tm_mday = mday;
  time->tm_mon = month - 1;
  time->tm_year = year - 1900;
  time->tm_sec = 00;
  time->tm_isdst = -1;

  puts("Enter Arrival Date (dd/mm/yyyy): ");
  do {
    scanf("%d/%d/%d", &mday, &month, &year);
    if (mday > 31 || month > 12 || year < 1900) {
      printf("\nPlease enter Valid Arrival Date:");
    }
  } while (mday > 31 || month > 12 || year < 1900);

  puts("Enter Arrival Time (HH:mm): ");
  do {
    scanf("%d:%d", &hr, &min);
    if (hr > 23 || min > 59) {
      printf("\nPlease enter Valid Arrival Time:");
    }
  } while (hr > 23 || min > 59);
  time = &((*curr_train)->train_schedule.arrival_timendate);

  time->tm_hour = hr;
  time->tm_min = min;
  time->tm_mday = mday;
  time->tm_mon = month - 1;
  time->tm_year = year - 1900;
  time->tm_sec = 00;
  time->tm_isdst = -1;

  (*curr_train)->train_schedule.schdl_status = SET;
}
