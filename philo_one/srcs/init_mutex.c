/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:13:22 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/17 13:51:27 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_a_fork(t_env *env, int n, int fork)
{
	struct timeval	time;

	if (n != fork)
		usleep(50);
	if (fork == env->nb_of_ph)
		fork = 0;
	if (check_alive(env) == 0)
	{
		if (pthread_mutex_lock(&env->forks[fork]) != 0)
			return (print_error("MUTEX LOCK FORK FAILED", -1));
		if (gettimeofday(&time, NULL) != 0)
			return (print_error("GET TIME OF DAY FAILED", -1));
		if (check_alive(env) == 0)
			print_result(-get_time_in_ms(env->start)
				+ get_time_in_ms(time), n, " has taken a fork\n");
	}	
	return (0);
}

int	ft_init_mutex_meal_time(t_env *env)
{
	int	i;

	i = 0;
	env->m_meal_time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->nb_of_ph);
	if (env->m_meal_time == NULL)
		return (print_error("ALLOCATION OF MEAL TIME FAILED", -1));
	while (i < env->nb_of_ph)
	{
		if (pthread_mutex_init(&env->m_meal_time[i], NULL) != 0)
			return (print_error("INIT MUTEX OF MEAL TIME FAILED", -1));
		i++;
	}
	return (0);
}

int	ft_init_forks(t_env *env)
{
	int	i;

	i = 0;
	env->m_nb_of_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->nb_of_ph);
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->nb_of_ph);
	if (env->forks == NULL || env->m_nb_of_meal == NULL)
		return (print_error("ALLOCATION OF FORKS FAILED", -1));
	while (i < env->nb_of_ph)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (print_error("INIT MUTEX OF FORKS FAILED", -1));
		if (pthread_mutex_init(&env->m_nb_of_meal[i], NULL) != 0)
			return (print_error("INIT MUTEX OF FORKS FAILED", -1));
		i++;
	}
	if (pthread_mutex_init(&env->m_alive, NULL) != 0)
		return (print_error("INIT MUTEX OF ALIVE FAILED", -1));
	return (0);
}
