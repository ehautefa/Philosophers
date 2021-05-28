/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_waiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:15:11 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/28 12:44:15 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

int	check_time_last_meal(t_env *env, int i)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&env->m_meal_time[i]);
	if (get_time_in_ms(time) - get_time_in_ms(env->ph[i].meal_time)
		>= env->time_to_die)
	{
		pthread_mutex_unlock(&env->m_meal_time[i]);
		sem_wait(env->s_alive);
		env->alive = 1;
		sem_post(env->s_alive);
		usleep(1000);
		env->who_is_dead = i + 1;
		gettimeofday(&time, NULL);
		printf("%-3d MS %d died\n", (int)(-get_time_in_ms(env->start)
				+ get_time_in_ms(time)), env->who_is_dead);
		return (1);
	}
	pthread_mutex_unlock(&env->m_meal_time[i]);
	return (0);
}

void	*launch_waiter(void *arg)
{
	t_env			*env;
	int				i;

	env = (t_env *)arg;
	sem_wait(env->s_alive);
	while (env->alive == 0)
	{
		sem_post(env->s_alive);
		i = 0;
		while (i < env->nb_of_ph)
		{
			if (check_time_last_meal(env, i) == 1)
				return (NULL);
			usleep(1000);
			i++;
		}
	}
	sem_post(env->s_alive);
	return (NULL);
}
