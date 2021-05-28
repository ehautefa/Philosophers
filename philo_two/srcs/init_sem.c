/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:13:22 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/28 12:49:53 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	take_a_fork(t_env *env, int n)
{
	struct timeval	time;

	sem_wait(env->forks);
	gettimeofday(&time, NULL);
	if (check_alive(env) == 0)
		printf("%-3d MS %d has taken a fork\n",
			(int)(-get_time_in_ms(env->start)
				+ get_time_in_ms(time)), n);
}

int	ft_init_mutex_meal_time(t_env *env)
{
	int	i;

	i = 0;
	env->m_meal_time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->nb_of_ph);
	if (env->m_meal_time == NULL)
		return (1);
	i = 0;
	while (i < env->nb_of_ph)
	{
		if (pthread_mutex_init(&env->m_meal_time[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_forks(t_env *env)
{
	int	i;

	i = 0;
	env->nb_forks = env->nb_of_ph;
	if (env->nb_forks == 1)
		env->nb_forks = 2;
	env->forks = sem_open("s_fork", O_CREAT, S_IRWXU, env->nb_forks);
	// if (ft_strcmp(env->forks, "SEM_FAILED") == 0)
		// return (1);
	env->s_alive = sem_open("s_alive", O_CREAT, S_IRWXU, 1);
	// if (ft_strcmp(env->s_alive, "SEM_FAILED") == 0)
	// 	return (1);
	return (0);
}
