/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:09:40 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/28 11:21:56 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int	check_alive(t_env *env)
{
	int	flag;

	pthread_mutex_lock(&env->m_alive);
	flag = env->alive;
	pthread_mutex_unlock(&env->m_alive);
	return (flag);
}

void	ft_init_meal_time(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_of_ph)
	{
		pthread_mutex_lock(&env->m_meal_time[i]);
		env->ph[i].meal_time.tv_sec = env->start.tv_sec;
		env->ph[i].meal_time.tv_usec = env->start.tv_usec;
		pthread_mutex_unlock(&env->m_meal_time[i]);
		i++;
	}
}

int	ft_init_thread(t_env *env)
{
	int	i;

	i = 0;
	env->ph = (t_philo *)malloc((env->nb_of_ph + 1) * sizeof(t_philo));
	if (env->ph == NULL)
		return (1);
	ft_init_meal_time(env);
	pthread_create(&env->ph[i].thread, NULL, launch_waiter, (void *)env);
	while (i < env->nb_of_ph)
	{
		env->ph[i].id = i;
		env->ph[i].num_of_eat = env->num_of_eat;
		env->ph[i].env = env;
		pthread_mutex_lock(&env->m_meal_time[i]);
		env->ph[i].meal_time.tv_sec = env->start.tv_sec;
		env->ph[i].meal_time.tv_usec = env->start.tv_usec;
		pthread_mutex_unlock(&env->m_meal_time[i]);
		pthread_create(&env->ph[i].thread, NULL, launch_thread,
			(void *)&env->ph[i]);
		usleep(10);
		i++;
	}
	if (ft_join_thread(env))
		return (1);
	return (0);
}
