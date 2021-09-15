/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:09:40 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/15 16:06:03 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_alive(t_env *env)
{
	int	flag;

	if (pthread_mutex_lock(&env->m_alive))
		return (-1);
	flag = env->alive;
	if (pthread_mutex_unlock(&env->m_alive))
		return (-1);
	return (flag);
}

int	ft_init_meal_time(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_of_ph)
	{
		if (pthread_mutex_lock(&env->m_meal_time[i]))
			return (print_error("MUTEX LOCK ERROR (meal_time)", -1));
		env->ph[i].meal_time.tv_sec = env->start.tv_sec;
		env->ph[i].meal_time.tv_usec = env->start.tv_usec;
		if (pthread_mutex_unlock(&env->m_meal_time[i]))
			return (print_error("MUTEX UNLOCK ERROR (meal_time)", -1));
		i++;
	}
	return (0);
}

int	ft_init_thread(t_env *env)
{
	int	i;

	i = -1;
	env->ph = (t_philo *)malloc((env->nb_of_ph + 1) * sizeof(t_philo));
	if (env->ph == NULL || ft_init_meal_time(env))
		return (1);
	// if (pthread_create(&env->ph[env->nb_of_ph].thread, NULL,
	// 		launch_waiter, (void *)env) != 0)
	// 	return (print_error("PTHREAD CREATE ERROR", -1));
	while (++i < env->nb_of_ph)
	{
		env->ph[i].id = i;
		env->ph[i].num_of_eat = env->num_of_eat;
		env->ph[i].env = env;
		if (pthread_create(&env->ph[i].thread, NULL, launch_thread,
				(void *)&env->ph[i]) != 0)
			return (1);
		usleep(50);
	}
	if (launch_waiter(env) || ft_join_thread(env))
		return (1);
	return (0);
}
