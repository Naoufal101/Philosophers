/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:01:29 by nhimad            #+#    #+#             */
/*   Updated: 2024/09/09 09:38:40 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_times
{
	int				nmb_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_times_epme;
	int				stop;
	int				stop_sim;
	size_t			start;
	pthread_mutex_t	print_m;
	pthread_mutex_t	death_m;
	pthread_mutex_t	ss_m;
}					t_times;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	size_t			begin;
	int				id;
	t_times			*pt;
	int				end;
}					t_philo;

void				*ft_routine(void *d);
char				get_inpt(t_times *philo_time, char **argv);
int					ft_atoi(const char *str);
int					ft_mutex_init(t_times *philo_time);
size_t				ft_gettimeofday(void);
int					check_do(t_philo *philo, char *str, char update);
int					ft_usleep(t_philo *philo, size_t tt, int key);
void				ft_check(t_philo *philo_data);
int					ft_died(t_philo *philo);
int					ft_free(t_times philo_time, t_philo *philo_data);
int					ft_unlock(t_philo *philo, int key);
int					ft_lock(t_philo *philo);
#endif