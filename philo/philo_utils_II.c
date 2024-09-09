/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:14 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/09 10:35:35 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_lock(t_philo *philo)
{
	pthread_mutex_lock(&((philo)->fork));
	if (philo->pt->stop)
	{
		ft_unlock(philo, 1);
		return (1);
	}
	pthread_mutex_lock(&(philo->pt->print_m));
	printf("%-5lu %-2d has taken a fork\n", (ft_gettimeofday()
			- philo->pt->start), philo->id);
	pthread_mutex_unlock(&(philo->pt->print_m));
	if (philo->id != philo->pt->nmb_of_philo)
		pthread_mutex_lock(&((philo + 1)->fork));
	else
		pthread_mutex_lock(&((philo - (philo->pt->nmb_of_philo - 1))->fork));
	if (philo->pt->stop)
	{
		ft_unlock(philo, 1);
		return (1);
	}
	pthread_mutex_lock(&(philo->pt->print_m));
	printf("%-5lu %-2d has taken a fork\n", (ft_gettimeofday()
			- philo->pt->start), philo->id);
	pthread_mutex_unlock(&(philo->pt->print_m));
	return (0);
}

size_t	ft_gettimeofday(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	check_do(t_philo *philo, char *str, char update)
{
	if (philo->pt->stop)
		return (1);
	if (((ft_gettimeofday() - philo->begin) >= philo->pt->time_to_die))
	{
		pthread_mutex_lock(&(philo->pt->death_m));
		if (!philo->pt->stop)
			philo->pt->stop = philo->id;
		pthread_mutex_unlock(&(philo->pt->death_m));
		return (1);
	}
	pthread_mutex_lock(&(philo->pt->print_m));
	printf("%-5lu %-2d %s\n", (ft_gettimeofday() - philo->pt->start), philo->id,
		str);
	pthread_mutex_unlock(&(philo->pt->print_m));
	if (update)
		philo->begin = ft_gettimeofday();
	return (0);
}

int	ft_usleep(t_philo *philo, size_t tt, int key)
{
	size_t	start;
	size_t	ttd;

	if (key)
		ttd = philo->pt->time_to_die;
	else
		ttd = philo->pt->time_to_die - philo->pt->time_to_eat;
	start = ft_gettimeofday();
	while ((ft_gettimeofday() - start) < tt && (ft_gettimeofday() - start) < ttd
		&& !philo->pt->stop)
		usleep(500);
	if ((ft_gettimeofday() - start) == ttd)
		return (1);
	return (0);
}

int	ft_free(t_times philo_time, t_philo *philo_data)
{
	int	i;

	i = 0;
	while (i < philo_time.nmb_of_philo)
	{
		if (pthread_join(philo_data[i].thread, NULL))
		{
			free(philo_data);
			return (3);
		}
		i++;
	}
	i = 0;
	while (i < philo_time.nmb_of_philo)
	{
		if (pthread_mutex_destroy(&(philo_data[i].fork)))
		{
			free(philo_data);
			return (4);
		}
		i++;
	}
	free(philo_data);
	return (0);
}
