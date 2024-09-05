/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:14 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/03 15:29:06 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_gettimeofday(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("........ERORR........\n");
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	check_do(t_philos *philo, char *str, char update)
{
	sem_wait(philo->print_s);
	printf("%-5ld %-2d %s\n", (ft_gettimeofday() - philo->start), philo->id,
		str);
	sem_post(philo->print_s);
	if (update)
		philo->begin = ft_gettimeofday();
}

void	ft_usleep(t_philos *philo, size_t tt, int key)
{
	size_t	start;
	size_t	ttd;

	if (key)
		ttd = philo->time_to_die;
	else
		ttd = philo->time_to_die - philo->time_to_eat;
	start = ft_gettimeofday();
	while ((ft_gettimeofday() - start) < tt && (ft_gettimeofday() - start) < ttd)
		usleep(500);
}

// int	ft_free(t_times philo_time, t_philo *philo_data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo_time.nmb_of_philo)
// 	{
// 		if (pthread_join(philo_data[i].thread, NULL))
// 		{
// 			free(philo_data);
// 			return (3);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < philo_time.nmb_of_philo)
// 	{
// 		if (pthread_mutex_destroy(&(philo_data->fork)))
// 		{
// 			free(philo_data);
// 			return (4);
// 		}
// 		i++;
// 	}
// 	free(philo_data);
// 	return (0);
// }
