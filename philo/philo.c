/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:23 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/08 19:01:25 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	get_inpt(t_times *philo_time, char **argv)
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
	philo_time->stop = 0;
	philo_time->nmb_of_philo = array[0];
	philo_time->time_to_die = array[1];
	philo_time->time_to_eat = array[2];
	philo_time->time_to_sleep = array[3];
	philo_time->number_of_times_epme = array[4];
	philo_time->stop_sim = 0;
	return (ft_mutex_init(philo_time));
}

int	philo_init(t_philo *philo_data, t_times *philo_time)
{
	int	i;

	i = 0;
	while (i < philo_time->nmb_of_philo)
	{
		philo_data[i].id = i + 1;
		philo_data[i].begin = 0;
		philo_data[i].end = 0;
		philo_data[i].pt = philo_time;
		if (pthread_mutex_init(&philo_data[i].fork, NULL))
			return (2);
		i++;
	}
	i = 0;
	philo_time->start = ft_gettimeofday();
	while (i < philo_time->nmb_of_philo)
	{
		if (pthread_create(&philo_data[i].thread, NULL, ft_routine,
				&philo_data[i]))
			return (2);
		i++;
	}
	return (0);
}

t_philo	*check_input(t_times *philo_time, int argc, char **argv)
{
	t_philo	*philo_data;

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
	philo_data = malloc(philo_time->nmb_of_philo * sizeof(t_philo));
	return (philo_data);
}

int	main(int argc, char **argv)
{
	t_times	philo_time;
	t_philo	*philo_data;

	philo_data = check_input(&philo_time, argc, argv);
	if (!philo_data)
		return (1);
	if (philo_init(philo_data, &philo_time))
	{
		free(philo_data);
		return (2);
	}
	ft_check(philo_data);
	if (ft_died(philo_data))
		return (3);
	if (ft_free(philo_time, philo_data))
		return (4);
	return (0);
}
