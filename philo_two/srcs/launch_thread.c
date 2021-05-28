/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:14:17 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/28 12:45:50 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	eating(t_philo *ph)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%-3d MS %d is eating\n", (int)(-get_time_in_ms(ph->env->start)
			+ get_time_in_ms(time)), ph->id + 1);
	ft_usleep(ph->env->time_to_eat);
}

void	sleeping(t_philo *ph)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%-3d MS %d is sleeping\n", (int)(-get_time_in_ms(ph->env->start)
			+ get_time_in_ms(time)), ph->id + 1);
	ft_usleep(ph->env->time_to_sleep);
}

void	thinking(t_philo *ph)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%-3d MS %d is thinking\n", (int)(-get_time_in_ms(ph->env->start)
			+ get_time_in_ms(time)), ph->id + 1);
}

void	stop_simulation(t_env *env)
{
	sem_wait(env->s_alive);
	env->alive = 1;
	sem_post(env->s_alive);
}

void	*launch_thread(void *arg)
{
	t_philo			*ph;
	struct timeval	time;	

	ph = (t_philo *)arg;
	while (ph->num_of_eat != 0 && check_alive(ph->env) == 0)
	{
		take_a_fork(ph->env, ph->id + 1);
		take_a_fork(ph->env, ph->id + 1);
		pthread_mutex_lock(&ph->env->m_meal_time[ph->id]);
		gettimeofday(&ph->meal_time, NULL);
		pthread_mutex_unlock(&ph->env->m_meal_time[ph->id]);
		if (check_alive(ph->env) == 0)
			eating(ph);
		gettimeofday(&time, NULL);
		sem_post(ph->env->forks);
		sem_post(ph->env->forks);
		if (check_alive(ph->env) == 0)
			sleeping(ph);
		if (check_alive(ph->env) == 0)
			thinking(ph);
		ph->num_of_eat--;
		if (ph->num_of_eat == 0)
			stop_simulation(ph->env);
	}
	return (NULL);
}
