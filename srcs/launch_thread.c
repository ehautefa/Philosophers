/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:14:17 by ehautefa          #+#    #+#             */
/*   Updated: 2021/09/05 10:49:35 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *ph)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	print_result(-get_time_in_ms(ph->env->start)
					+ get_time_in_ms(time), ph->id + 1, " is eating\n");
	if (ft_usleep(ph->env->time_to_eat) != 0)
		return (1);
	return (0);
}

int	sleeping(t_philo *ph)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	print_result(-get_time_in_ms(ph->env->start)
					+ get_time_in_ms(time), ph->id + 1, " is sleeping\n");
	if (ft_usleep(ph->env->time_to_sleep) != 0)
		return (1);
	return (0);
}

int	thinking(t_philo *ph)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	print_result(-get_time_in_ms(ph->env->start)
					+ get_time_in_ms(time), ph->id + 1, " is thinking\n");
	return (0);
}

int	ft_manage_forks(t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		if (take_a_fork(ph->env, ph->id + 1, ph->id) != 0)
			return (1);
		if (take_a_fork(ph->env, ph->id + 1, ph->id + 1) != 0)
			return (1);
	}
	else
	{
		if (take_a_fork(ph->env, ph->id + 1, ph->id + 1) != 0)
			return (1);
		if (take_a_fork(ph->env, ph->id + 1, ph->id) != 0)
			return (1);
	}
	return (0);
}

void	*launch_thread(void *arg)
{
	t_philo			*ph;
	struct timeval	time;	

	ph = (t_philo *)arg;
	while (ph->num_of_eat != 0 && check_alive(ph->env) == 0)
	{
		if (ft_manage_forks(ph)
			|| pthread_mutex_lock(&ph->env->m_meal_time[ph->id])
			|| gettimeofday(&ph->meal_time, NULL)
			|| pthread_mutex_unlock(&ph->env->m_meal_time[ph->id]))
			return ("Error");
		if (check_alive(ph->env) == 0 && eating(ph))
			return ("Error");
		if (gettimeofday(&time, NULL)
			|| pthread_mutex_unlock(&ph->env->forks[ph->id])
			|| pthread_mutex_unlock(&ph->env->forks[(ph->id + 1)
					% ph->env->nb_forks]))
			return ("Error");
		if (check_alive(ph->env) == 0 && sleeping(ph))
			return ("Error");
		if (check_alive(ph->env) == 0 && thinking(ph))
			return ("Error");
		ph->num_of_eat--;
	}
	return (NULL);
}
