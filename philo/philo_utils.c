#include "philo.h"

char is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (1);
        i++;
    }
    return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	num;

	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num);
}

char get_inpt(t_times *philo_time, char **argv)
{
    int i;
    int array[4];

    i = 1;
    while (argv[i])
    {
        if (is_digit(argv[i]))
        {
            printf("invalid argument\n");
            return (1);
        }
        array[i] = ft_atoi(argv[i]);
        i++;
    }
    philo_time->number_of_philosophers = array[0];
    philo_time->time_to_die = array[1];
    philo_time->time_to_eat = array[2];
    if (i < 4)
        philo_time->number_of_times_epme = -1;
    else
        philo_time->number_of_times_epme = array[3];
    return (0);
}
