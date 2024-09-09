/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:29 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/09 11:47:45 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MEALS "/meal_sem"
# define FORKS "/forks_sem"
# define PRINT "/print_sem"
# define START "/start_simulation"
# define MAX_PHILO 2510

typedef struct s_philos
{
	int		nmb_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		number_of_times_epme;
	int		meals_counter;
	int		stop;
	int		id;
	pid_t	array[MAX_PHILO];
	size_t	start;
	size_t	begin;
	sem_t	*print_s;
	sem_t	*meal_s;
	sem_t	*forks;
	sem_t	*sim_start;
}			t_philos;

void		ft_routine(t_philos *philo);
char		get_inpt(t_philos *philo_time, char **argv);
size_t		ft_gettimeofday(void);
void		check_do(t_philos *philo, char *str, char update);
void		ft_usleep(t_philos *philo, size_t tt, int key);
void		*ft_check(void *p);
void		ft_free(t_philos *philo_data, pthread_t	*meals);
void		ft_fork_free(t_philos *philo);
#endif