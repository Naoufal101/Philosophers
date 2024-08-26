#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_times
{
    int         number_of_philosophers;
    size_t      time_to_die;
    size_t      time_to_eat;
    size_t      time_to_sleep;
    int         number_of_times_epme;
    int         stop;
    int         simulation_stops;
    size_t      start;
    pthread_mutex_t print_m;
    pthread_mutex_t death_m;
    pthread_mutex_t ss_m;
}   t_times;

typedef struct s_philo
{
    pthread_t       thread;
    pthread_mutex_t fork;
    size_t          begin;
    int             id;
    t_times         *pt;
    int             end;
}   t_philo;

char get_inpt(t_times *philo_time, char **argv);
size_t ft_gettimeofday();
int check_do(t_philo *philo, char *str, char update);
int	ft_usleep_eat(t_philo *philo);
int	ft_usleep_sleep(t_philo *philo);
int	ft_usleep_sleep1(t_philo *philo);

void ft_check(t_philo *philo_data);
int ft_unlock(t_philo *philo, int key);
int ft_lock(t_philo *philo);
#endif