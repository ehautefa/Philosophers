/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:00:41 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/19 12:44:39 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long		res;
	int			signe;
	int			tmp;

	i = 0;
	res = 0;
	signe = 1;
	tmp = i;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - 48;
	if ((res > 9223372036854775807 || (i - tmp) > 20) && signe == -1)
		return (0);
	else if ((res > 9223372036854775807 || (i - tmp) > 20) && signe == 1)
		return (-1);
	else
		return (res * signe);
}

void	ft_free(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_of_ph)
	{
		pthread_mutex_destroy(&env->forks[i]);
		pthread_mutex_destroy(&env->m_nb_of_meal[i]);
		pthread_mutex_destroy(&env->m_meal_time[i]);
		i++;
	}
	pthread_mutex_destroy(&env->m_alive);
	free(env->m_meal_time);
	if (env->forks)
		free(env->forks);
	if (env->m_nb_of_meal)
		free(env->m_nb_of_meal);
	if (env->ph)
		free(env->ph);
}

long	get_time_in_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(long time, t_env *env)
{
	struct timeval	start;
	long			start_in_ms;
	long			final_time;

	if (gettimeofday(&start, NULL))
		return (1);
	start_in_ms = get_time_in_ms(start);
	final_time = start_in_ms + time;
	while (check_alive(env) == 0 && start_in_ms < final_time)
	{
		if (gettimeofday(&start, NULL))
			return (1);
		start_in_ms = get_time_in_ms(start);
		usleep(50);
	}
	return (0);
}
