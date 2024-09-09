/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:26 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/09 10:10:49 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_died(t_philo *philo)
{
	if (philo->pt->stop > 0)
	{
		usleep(1500);
		pthread_mutex_lock(&(philo->pt->print_m));
		printf("%-5lu %-2d died\n", (ft_gettimeofday() - philo->pt->start),
			philo->pt->stop);
		pthread_mutex_unlock(&(philo->pt->print_m));
	}
	if (philo->pt->stop && philo->pt->nmb_of_philo == 1)
	{
		if (pthread_mutex_unlock(&(philo[0].fork)))
		{
			free(philo);
			return (1);
		}
	}
	return (0);
}

int	ft_ckeck_death(t_philo *philo, int i)
{
	if (((ft_gettimeofday() - philo[i].begin) >= philo[i].pt->time_to_die)
		&& philo[i].begin && !philo[i].end)
	{
		pthread_mutex_lock(&(philo->pt->death_m));
		if (!philo->pt->stop)
			philo->pt->stop = philo[i].id;
		pthread_mutex_unlock(&(philo->pt->death_m));
		return (1);
	}
	return (0);
}

void	ft_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (!philo->pt->stop && !philo[i].end)
	{
		while (i < philo->pt->nmb_of_philo && (!philo->pt->stop))
		{
			if (ft_ckeck_death(philo, i))
				return ;
			if (philo->pt->stop_sim == philo->pt->nmb_of_philo)
			{
				philo->pt->stop = -1;
				return ;
			}
			i++;
		}
		i = 0;
		usleep(500);
	}
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	num;

	i = 0;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9' && num <= LONG_MAX)
		num = num * 10 + (str[i++] - '0');
	if (str[i] || num > LONG_MAX)
	{
		return (-1);
	}
	return (num);
}

int	ft_unlock(t_philo *philo, int key)
{
	pthread_mutex_unlock(&((philo)->fork));
	if (key)
		return (1);
	if (philo->id != philo->pt->nmb_of_philo)
		pthread_mutex_unlock(&((philo + 1)->fork));
	else
		pthread_mutex_unlock(&((philo - (philo->pt->nmb_of_philo - 1))->fork));
	return (0);
}
