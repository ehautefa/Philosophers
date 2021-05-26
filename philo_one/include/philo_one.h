#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int			id;
	int			action;
	pthread_t	thread;
}				t_philo;

typedef struct s_env
{
	int				nb_of_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				nb_forks;
	pthread_mutex_t	*forks;
	t_philo			*ph;
}				t_env;

int		ft_atoi(const char *str);
void	ft_free(t_env *env);
void	*init_thread(void *arg);
int		ft_init_thread(t_env *env);
int		ft_init_forks(t_env *env);
void	ft_putstr(char *str);

#endif