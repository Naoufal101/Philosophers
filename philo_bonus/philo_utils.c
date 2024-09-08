/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:26 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/08 19:14:02 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sem_init(t_philos *philo_time)
{
	sem_unlink(START);
	philo_time->sim_start = sem_open(START, O_CREAT, 0666, 0);
	if (philo_time->sim_start == SEM_FAILED)
		exit(8);
	sem_unlink(PRINT);
	philo_time->print_s = sem_open(PRINT, O_CREAT, 0666, 1);
	if (philo_time->print_s == SEM_FAILED)
		exit(8);
	sem_unlink(MEALS);
	philo_time->meal_s = sem_open(MEALS, O_CREAT, 0666, 0);
	if (philo_time->meal_s == SEM_FAILED)
		exit(8);
	sem_unlink(FORKS);
	philo_time->forks = sem_open(FORKS, O_CREAT, 0666,
			philo_time->nmb_of_philo);
	if (philo_time->forks == SEM_FAILED)
		exit(8);
}

void	ft_ckeck_death(t_philos *philo)
{
	size_t	ttd;

	ttd = philo->time_to_die;
	if (philo->begin && ((ft_gettimeofday() - philo->begin) >= ttd))
	{
		sem_wait(philo->print_s);
		printf("%-5ld %-2d died\n", (ft_gettimeofday() - philo->start),
			philo->id);
		exit(1);
	}
}

void	*ft_check(void *p)
{
	t_philos	*philo;

	philo = p;
	while (1)
	{
		ft_ckeck_death(philo);
		usleep(500);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9' && i < 10)
		num = num * 10 + (str[i++] - '0');
	if (str[i] || num > INT_MAX)
	{
		return (-1);
	}
	return (num * sign);
}

char	get_inpt(t_philos *philo_time, char **argv)
{
	int	i;
	int	array[5];

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
		return (1);
	philo_time->nmb_of_philo = array[0];
	philo_time->time_to_die = array[1];
	philo_time->time_to_eat = array[2];
	philo_time->time_to_sleep = array[3];
	philo_time->number_of_times_epme = array[4];
	philo_time->meals_counter = 1;
	philo_time->begin = 0;
	philo_time->stop = 0;
	ft_sem_init(philo_time);
	return (0);
}
