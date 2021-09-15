/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_waiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:15:11 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/15 16:11:55 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_time_last_meal(t_env *env, int i)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL)
		|| pthread_mutex_lock(&env->m_meal_time[i]))
		return (1);
	if (get_time_in_ms(time) - get_time_in_ms(env->ph[i].meal_time)
		>= env->time_to_die)
	{
		if (pthread_mutex_unlock(&env->m_meal_time[i])
			|| pthread_mutex_lock(&env->m_alive))
			return (1);
		env->alive = 1;
		if (pthread_mutex_unlock(&env->m_alive) || usleep(1000))
			return (1);
		env->who_is_dead = i + 1;
		if (gettimeofday(&time, NULL))
			return (1);
		print_result(-get_time_in_ms(env->start)
				+ get_time_in_ms(time), env->who_is_dead, " died\n");
		return (2);
	}
	if (pthread_mutex_unlock(&env->m_meal_time[i]))
		return (1);
	return (0);
}

void	*launch_waiter(void *arg)
{
	t_env			*env;
	int				i;
	int				ret;

	env = (t_env *)arg;
	while (check_alive(env) == 0)
	{
		i = 0;
		while (i < env->nb_of_ph)
		{			
			ret = check_time_last_meal(env, i);
			if (ret == 2)
			{
				i = -1;
				write(1, "DETACH\n", 8);
				while (++i < env->nb_of_ph)
					pthread_detach(env->ph[i].thread);
			}
			else if (ret == 1)
				return ("Error");
			usleep(1000);
			i++;
		}
	}
	return (NULL);
}
