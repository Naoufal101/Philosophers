#include "philo.h"

int ft_lock(t_philo *philo)
{
    pthread_mutex_lock(&((philo)->fork));
    if (philo->pt->stop)
    {
        ft_unlock(philo, 1);
        return (1);
    }
    pthread_mutex_lock(&(philo->pt->print_m));
    printf("%-5ld %-2d has taken a fork\n", (ft_gettimeofday() - philo->pt->start), philo->id);
    pthread_mutex_unlock(&(philo->pt->print_m));

    if (philo->id != philo->pt->number_of_philosophers)
        pthread_mutex_lock(&((philo + 1)->fork));
    else
        pthread_mutex_lock(&((philo - (philo->pt->number_of_philosophers - 1))->fork));
    if (philo->pt->stop)
    {
        ft_unlock(philo, 1);
        return (1);
    }
    pthread_mutex_lock(&(philo->pt->print_m));
    printf("%-5ld %-2d has taken a fork\n", (ft_gettimeofday() - philo->pt->start), philo->id);
    pthread_mutex_unlock(&(philo->pt->print_m));
    return (0);
}

int ft_unlock(t_philo *philo, int key)
{ 
    pthread_mutex_unlock(&((philo)->fork));
    if (key)
        return (1);
    if (philo->id != philo->pt->number_of_philosophers)
        pthread_mutex_unlock(&((philo+1)->fork));
    else
        pthread_mutex_unlock(&((philo - (philo->pt->number_of_philosophers - 1))->fork));
    return (0);
}

void *ft_routine(void *d)
{
    t_philo *philo = (t_philo *)d;
    int i;
    int j;
    
    i = 1;
    j = 0;
    philo->begin = philo->pt->start;
    if (philo->id % 2 == 0)
    {
        if(check_do(philo, "is sleeping", 0))
            return (NULL);
        j = ft_usleep(philo, philo->pt->time_to_sleep);
        if (j)
        {
            pthread_mutex_lock(&(philo->pt->death_m));
            if (!philo->pt->stop)
                philo->pt->stop = philo->id;
            pthread_mutex_unlock(&(philo->pt->death_m));
            return (NULL);
        }
    }

    while (philo->pt->simulation_stops != philo->pt->number_of_philosophers)
    {
        if (check_do(philo, "is thinking", 0))
            break;
        if (ft_lock(philo))
            break;
        if (check_do(philo, "is eating", 1))
        {
            ft_unlock(philo, 0); 
            break;
        }
        j = ft_usleep(philo, philo->pt->time_to_eat);
        if (j)
        {
            pthread_mutex_lock(&(philo->pt->death_m));
            if (!philo->pt->stop)
                philo->pt->stop = philo->id;
            pthread_mutex_unlock(&(philo->pt->death_m));
            ft_unlock(philo, 0);
            break;
        }
        ft_unlock(philo, 0);
       
        if (philo->pt->number_of_times_epme)
        {
            if (i == philo->pt->number_of_times_epme)
            {
                pthread_mutex_lock(&(philo->pt->ss_m));
                philo->pt->simulation_stops++;
                pthread_mutex_unlock(&(philo->pt->ss_m));
            }
            i++;
        }

        if(check_do(philo, "is sleeping", 0))
            break;
        j = ft_usleep_sleep(philo);
        if (j)
        {
            pthread_mutex_lock(&(philo->pt->death_m));
            if (!philo->pt->stop)
                philo->pt->stop = philo->id;
            pthread_mutex_unlock(&(philo->pt->death_m));
            break;
        }
    }
    philo->end = 1;
    return (NULL);
}

int     philo_init(t_philo *philo_data, t_times *philo_time)
{
    int i;

    i = 0;
    while(i < philo_time->number_of_philosophers)
    {
        philo_data[i].id = i + 1;
        philo_data[i].begin = 0;
        philo_data[i].end = 0;
        philo_data[i].pt = philo_time;
        if (pthread_mutex_init(&philo_data[i].fork, NULL))
        {
            free(philo_data);
            return (2);
        }
        i++;
    }
    i = 0;
    philo_time->start = ft_gettimeofday();
    while (i < philo_time->number_of_philosophers)
    {
        if (pthread_create(&philo_data[i].thread, NULL, ft_routine, &philo_data[i]))
        {
            free(philo_data);
            return (2);
        }
        i++;
    }
    return (0);
}

t_philo *check_input(t_times *philo_time, int argc, char **argv)
{
    t_philo *philo_data;

    if (argc != 5 && argc != 6)
    {
        printf("The number of arguments must be either 4 or 5.\n");
        return (NULL);
    }

    if (get_inpt(philo_time, argv))
    {
        printf("Invalid argument\n");
        return (NULL);
    }
    philo_data = malloc(philo_time->number_of_philosophers * sizeof(t_philo));
    return (philo_data);
}

int main(int argc, char **argv)
{
    t_times philo_time;
    t_philo *philo_data;

    philo_data = check_input(&philo_time, argc, argv);
    if (!philo_data)
        return (1);
    if (philo_init(philo_data, &philo_time))
        return (2);
    ft_check(philo_data);
    if(ft_died(philo_data))
        return(3);
    if(ft_free(philo_time, philo_data))
        return (4);
    return (0);
}
