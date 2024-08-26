#include "philo.h"

int ft_died(t_philo *philo)
{
    if (philo->pt->stop && philo->pt->stop != 1337)
        printf("%-5ld %-2d died\n", (ft_gettimeofday()- philo->pt->start), philo->pt->stop);
    if(philo->pt->stop && philo->pt->number_of_philosophers == 1)
    {
        if (pthread_mutex_unlock(&(philo[0].fork)))
        {
            free(philo);
            return (1);
        }
    }
    return (0);
}

void ft_check(t_philo *philo)
{
    int i;
    
    i = 0;
    while (!philo->pt->stop && !philo[i].end)
    {
        while (i < philo->pt->number_of_philosophers && (!philo->pt->stop))
        {
            if (((ft_gettimeofday() - philo[i].begin) >= philo[i].pt->time_to_die) && philo[i].begin && !philo[i].end)
            {
                pthread_mutex_lock(&(philo->pt->death_m));
                if (!philo->pt->stop)
                    philo->pt->stop = philo->id;
                pthread_mutex_unlock(&(philo->pt->death_m));
                return;
            }
            if (philo->pt->simulation_stops == philo->pt->number_of_philosophers)
            {
                philo->pt->stop = 1337;
                return;
            }
            i++;
        }
        i = 0;
        usleep(1000);
    }
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
    if (str[i])
    {
        return (-1);
    }
	return (num * sign);
}

char get_inpt(t_times *philo_time, char **argv)
{
    int i;
    int array[5];

    i = 1;
    array[4] = 0;
    while (argv[i])
    {
        array[i - 1] = ft_atoi(argv[i]);
        if (array[i - 1] <= 0)
            return (1);
        i++;
    }
    if (i == 6 && array[4] == 0)
        return(1);
    philo_time->stop = 0;
    philo_time->number_of_philosophers = array[0];
    philo_time->time_to_die = array[1];
    philo_time->time_to_eat = array[2];
    philo_time->time_to_sleep = array[3];
    philo_time->number_of_times_epme = array[4];
    pthread_mutex_init(&(philo_time->print_m), NULL);
    pthread_mutex_init(&(philo_time->death_m), NULL);
    pthread_mutex_init(&(philo_time->ss_m), NULL);
    philo_time->simulation_stops = 0;
    return (0);
}

int ft_free(t_times philo_time, t_philo *philo_data)
{
    int i;
    
    i = 0;
    while (i < philo_time.number_of_philosophers)
    {
        if (pthread_join(philo_data[i].thread, NULL))
        {
            free(philo_data);
            return (3);
        }
        i++;
    }
    i = 0;
    while (i < philo_time.number_of_philosophers)
    {
        if (pthread_mutex_destroy(&(philo_data->fork)))
        {
            free(philo_data);
            return (4);
        }
        i++;
    }
    free(philo_data);
    return (0);
}