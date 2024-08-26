#include "philo.h"

int	ft_usleep_eat(t_philo *philo)
{
    size_t  start;
    size_t  tte;
    size_t  ttd;

    start = philo->begin;
    tte = philo->pt->time_to_eat;
    ttd  = philo->pt->time_to_die;
	while ((ft_gettimeofday() - start) < tte && (ft_gettimeofday() - start) < ttd && !philo->pt->stop)
		usleep(500);
    if ((ft_gettimeofday() - start) == ttd)
        return (1);
	return (0);
}

size_t ft_gettimeofday()
{
    struct timeval time;

    if(gettimeofday(&time, NULL) == -1)
        printf("........ERORR........\n");
    return((time.tv_sec * 1000 + time.tv_usec / 1000));
}

int check_do(t_philo *philo, char *str, char update)
{

    if (philo->pt->stop)
        return (1);
    if (((ft_gettimeofday() - philo->begin) >= philo->pt->time_to_die))
    {
        pthread_mutex_lock(&(philo->pt->death_m));
        if (!philo->pt->stop)
            philo->pt->stop = philo->id;
        pthread_mutex_unlock(&(philo->pt->death_m));
        return(1);
    }

    pthread_mutex_lock(&(philo->pt->print_m));
    printf("%-5ld %-2d %s\n", (ft_gettimeofday() - philo->pt->start), philo->id, str);
    pthread_mutex_unlock(&(philo->pt->print_m));
    if (update)
        philo->begin = ft_gettimeofday();
    return (0);
}

int	ft_usleep_sleep(t_philo *philo)
{
    size_t  start;
    size_t  tts;
    size_t  ttd;

    start = ft_gettimeofday();
    tts = philo->pt->time_to_sleep;
    ttd  = philo->pt->time_to_die - philo->pt->time_to_eat;
	while ((ft_gettimeofday() - start) < tts && (ft_gettimeofday() - start) < ttd && !philo->pt->stop)
		usleep(250);
    if ((ft_gettimeofday() - start) == ttd)
        return (1);
	return (0);
}

int	ft_usleep_sleep1(t_philo *philo)
{
    size_t  start;
    size_t  tts;
    size_t  ttd;

    start = ft_gettimeofday();
    tts = philo->pt->time_to_sleep;
    ttd  = philo->pt->time_to_die;
	while ((ft_gettimeofday() - start) < tts && (ft_gettimeofday() - start) < ttd && !philo->pt->stop)
		usleep(500);
    if ((ft_gettimeofday() - start) == ttd)
        return (1);
	return (0);
}