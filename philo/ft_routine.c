/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:20 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/08 19:04:23 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo, char key, char key2)
{
	int	j;

	j = 0;
	if (check_do(philo, "is sleeping", key))
		return (1);
	j = ft_usleep(philo, philo->pt->time_to_sleep, key2);
	if (j)
	{
		pthread_mutex_lock(&(philo->pt->death_m));
		if (!philo->pt->stop)
			philo->pt->stop = philo->id;
		pthread_mutex_unlock(&(philo->pt->death_m));
		return (1);
	}
	return (0);
}

int	ft_eat(t_philo *philo, char key, char key2)
{
	int	j;

	j = 0;
	if (ft_lock(philo))
		return (1);
	if (check_do(philo, "is eating", key))
	{
		ft_unlock(philo, 0);
		return (1);
	}
	j = ft_usleep(philo, philo->pt->time_to_eat, key2);
	if (j)
	{
		pthread_mutex_lock(&(philo->pt->death_m));
		if (!philo->pt->stop)
			philo->pt->stop = philo->id;
		pthread_mutex_unlock(&(philo->pt->death_m));
		ft_unlock(philo, 0);
		return (1);
	}
	ft_unlock(philo, 0);
	return (0);
}

void	ft_meals_counter(t_philo *philo, int *i)
{
	if (philo->pt->number_of_times_epme)
	{
		if (*i == philo->pt->number_of_times_epme)
		{
			pthread_mutex_lock(&(philo->pt->ss_m));
			philo->pt->stop_sim++;
			pthread_mutex_unlock(&(philo->pt->ss_m));
		}
		(*i)++;
	}
}

void	*ft_routine(void *d)
{
	t_philo	*philo;
	int		meals_counter;

	philo = (t_philo *)d;
	meals_counter = 1;
	philo->begin = philo->pt->start;
	if (philo->id % 2 == 0)
	{
		if (ft_sleep(philo, 0, 1))
			return (NULL);
	}
	while (philo->pt->stop_sim != philo->pt->nmb_of_philo)
	{
		if (check_do(philo, "is thinking", 0))
			break ;
		if (ft_eat(philo, 1, 1))
			break ;
		ft_meals_counter(philo, &meals_counter);
		if (ft_sleep(philo, 0, 0))
			break ;
	}
	philo->end = 1;
	return (NULL);
}

int	ft_mutex_init(t_times *philo_time)
{
	if (pthread_mutex_init(&(philo_time->print_m), NULL))
		return (1);
	if (pthread_mutex_init(&(philo_time->death_m), NULL))
		return (1);
	if (pthread_mutex_init(&(philo_time->ss_m), NULL))
		return (1);
	return (0);
}
