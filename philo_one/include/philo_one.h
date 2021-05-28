#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env	t_env;

typedef struct s_philo
{
	int				id;
	struct timeval	meal_time;
	int				num_of_eat;
	pthread_t		thread;
	t_env			*env;
}				t_philo;

struct s_env
{
	int				nb_of_ph;
	int				time_to_die;
	struct timeval	start;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				nb_forks;
	int				alive;
	int				who_is_dead;
	pthread_mutex_t	*m_meal_time;
	pthread_mutex_t	m_alive;
	pthread_mutex_t	*forks;
	t_philo			*ph;
};

/*
** PHILO_ONE.C
*/
int		ft_check_env(t_env *env);
int		ft_init_env(int	ac, char **av, t_env *env);

/*
** INIT_THREAD.C
*/
int		ft_init_meal_time(t_env *env);
int		ft_init_thread(t_env *env);
int		check_alive(t_env *env);
/*
** PHILO_UTILS.C
*/
int		ft_atoi(const char *str);
void	ft_free(t_env *env);
long	get_time_in_ms(struct timeval time);
int		ft_usleep(long time);
int		ft_join_thread(t_env *env);
/*
** INIT_MUTEX.C
*/
int		take_a_fork(t_env *env, int n, int fork);
int		ft_init_forks(t_env *env);
int		ft_init_mutex_meal_time(t_env *env);
/*
** LAUNCH_THREAD.C
*/
int		eating(t_philo *ph);
int		sleeping(t_philo *ph);
int		thinking(t_philo *ph);
int		ft_manage_forks(t_philo *ph);
void	*launch_thread(void *arg);

/*
** LAUNCH_WAITER.C
*/
void	*launch_waiter(void *arg);
int		check_time_last_meal(t_env *env, int i);

#endif