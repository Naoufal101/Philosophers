/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:14 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/08 17:56:18 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_gettimeofday(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
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
	while ((ft_gettimeofday() - start) < tt && (ft_gettimeofday()
			- start) < ttd)
		usleep(500);
}

int	ft_free(t_philos *philo_data)
{
	if (sem_close(philo_data->forks) == -1)
		exit(5);
	if (sem_close(philo_data->meal_s) == -1)
		exit(5);
	if (sem_close(philo_data->print_s) == -1)
		exit(5);
	if (sem_close(philo_data->sim_start) == -1)
		exit(5);
	if (sem_unlink(FORKS) == -1)
		exit(5);
	if (sem_unlink(MEALS) == -1)
		exit(5);
	if (sem_unlink(PRINT) == -1)
		exit(5);
	if (sem_unlink(START) == -1)
		exit(5);
}
