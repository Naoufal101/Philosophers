/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:20 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/05 17:00:32 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_fork(t_philos *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->print_s);
	printf("%-5ld %-2d has taken a fork\n", (ft_gettimeofday()
			- philo->start), philo->id);
	sem_post(philo->print_s);
}

void	ft_sleep(t_philos *philo, char key, char key2)
{
	check_do(philo, "is sleeping", key);
	ft_usleep(philo, philo->time_to_sleep, key2);
}

void	ft_eat(t_philos *philo, char key, char key2)
{
	ft_print_fork(philo);
	ft_print_fork(philo);
	check_do(philo, "is eating", key);
	ft_usleep(philo, philo->time_to_eat, key2);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	ft_meals_counter(t_philos *philo)
{
	if (philo->number_of_times_epme)
	{
		if (philo->meals_counter == philo->number_of_times_epme)
			sem_post(philo->meal_s);
		philo->meals_counter++;
	}
}

void	ft_routine(t_philos	*philo)
{
	pthread_t thread;
	
	philo->begin = philo->start;
	if (pthread_create(&thread, NULL, ft_check, philo))
		exit (3);
	if (pthread_detach(thread))
		exit (4);
	sem_wait(philo->sim_start);
	if (philo->id % 2 == 0)
		ft_sleep(philo, 0, 1);
	while (1)
	{
		check_do(philo, "is thinking", 0);
		ft_eat(philo, 1, 1);
		ft_meals_counter(philo);
		ft_sleep(philo, 0, 0);
	}
}
