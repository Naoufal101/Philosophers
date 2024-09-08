/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:26 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/08 18:59:11 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_died(t_philo *philo)
{
	if (philo->pt->stop > 0)
	{
		usleep(1500);
		pthread_mutex_lock(&(philo->pt->print_m));
		printf("%-5ld %-2d died\n", (ft_gettimeofday() - philo->pt->start),
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
