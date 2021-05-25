#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>

typedef struct s_arg
{
	int		nb_of_ph;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_eat;
}				t_arg;

typedef struct s_philo
{
	int		id;
	int		action;
	void	*next;
	void	*previous;
}				t_philo;

int		ft_atoi(const char *str);

#endif