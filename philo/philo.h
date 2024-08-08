#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_times
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int number_of_times_epme;
}   t_times;

char get_inpt(t_times *philo_time, char **argv);
#endif