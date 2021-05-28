/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:13:22 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/28 12:04:22 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	take_a_fork(t_env *env, int n, int fork)
{
	struct timeval	time;

	if (fork >= env->nb_forks)
		fork = 0;
	pthread_mutex_lock(&env->forks[fork]);
	gettimeofday(&time, NULL);
	if (check_alive(env) == 0)
		printf("%-3d MS %d has taken the %d fork\n",
			(int)(-get_time_in_ms(env->start)
				+ get_time_in_ms(time)), n, fork);
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
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->nb_forks);
	if (env->forks == NULL)
		return (1);
	while (i < env->nb_forks)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&env->m_alive, NULL) != 0)
		return (1);
	return (0);
}
