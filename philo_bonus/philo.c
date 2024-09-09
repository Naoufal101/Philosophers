/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:23 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/09 11:47:12 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philos *philo)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	philo->start = ft_gettimeofday();
	while (i < philo->nmb_of_philo)
	{
		philo->id = i + 1;
		pid = fork();
		if (pid == -1)
		{
			ft_fork_free(philo);
			exit(4);
		}
		if (!pid)
			ft_routine(philo);
		philo->array[i] = pid;
		i++;
	}
	while (i--)
		sem_post(philo->sim_start);
}

void	check_input(t_philos *philo_time, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("The number of arguments must be either 4 or 5.\n");
		exit(1);
	}
	if (get_inpt(philo_time, argv))
	{
		printf("Invalid argument\n");
		exit(1);
	}
}

void	*ft_meals(void *p)
{
	t_philos	*philo;
	int			i;

	i = 0;
	philo = p;
	while (philo->stop < philo->nmb_of_philo)
	{
		sem_wait(philo->meal_s);
		philo->stop++;
	}
	while (i < philo->nmb_of_philo)
		kill(philo->array[i++], SIGTERM);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philos	philo_data;
	pthread_t	meals;

	check_input(&philo_data, argc, argv);
	philo_init(&philo_data);
	pthread_create(&meals, NULL, ft_meals, &philo_data);
	ft_free(&philo_data, &meals);
	exit(0);
}
