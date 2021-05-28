/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:09:40 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/28 11:07:30 by ehautefa         ###   ########.fr       */
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

void	*launch_thread(void *arg)
{
	int				prev;
	int				next;
	t_philo			*ph;
	struct timeval	time;	

	ph = (t_philo *)arg;
	prev = (ph->id - 1) % ph->env->nb_of_ph;
	next = (ph->id + 1) % ph->env->nb_of_ph;
	while (ph->num_of_eat != 0 && check_alive(ph->env) == 0)
	{
		take_a_fork(ph->env, ph->id + 1, ph->id);
		take_a_fork(ph->env, ph->id + 1, ph->id + 1);
		pthread_mutex_lock(&ph->env->m_meal_time[ph->id]);
		gettimeofday(&ph->meal_time, NULL);
		pthread_mutex_unlock(&ph->env->m_meal_time[ph->id]);
		if (check_alive(ph->env) == 0)
		{
			gettimeofday(&time, NULL);
			printf("%-3d MS %d is eating\n", (int)(-get_time_in_ms(ph->env->start)
					+ get_time_in_ms(time)), ph->id + 1);
			ft_usleep(ph->env->time_to_eat);
		}
		gettimeofday(&time, NULL);
		pthread_mutex_unlock(&ph->env->forks[ph->id]);
		pthread_mutex_unlock(&ph->env->forks[(ph->id + 1) % ph->env->nb_forks]);
		if (check_alive(ph->env) == 0)
		{
			gettimeofday(&time, NULL);
			printf("%-3d MS %d is sleeping\n", (int)(-get_time_in_ms(ph->env->start)
					+ get_time_in_ms(time)), ph->id + 1);
			ft_usleep(ph->env->time_to_sleep);
		}
		if (check_alive(ph->env) == 0)
		{
			gettimeofday(&time, NULL);
			printf("%-3d MS %d is thinking\n", (int)(-get_time_in_ms(ph->env->start)
					+ get_time_in_ms(time)), ph->id + 1);
		}
		ph->num_of_eat--;
		if (ph->num_of_eat == 0)
		{
			pthread_mutex_lock(&ph->env->m_alive);
			ph->env->alive = 1;
			pthread_mutex_unlock(&ph->env->m_alive);
		}
	}
	return (NULL);
}

void	*check_time_last_meal(void *arg)
{
	t_env			*env;
	struct timeval	time;
	int				i;

	i = 0;
	env = (t_env *)arg;
	
	pthread_mutex_lock(&env->m_alive);
	while (env->alive == 0)
	{
		pthread_mutex_unlock(&env->m_alive);
		i = 0;
		while (i < env->nb_of_ph)
		{
			gettimeofday(&time, NULL);
			pthread_mutex_lock(&env->m_meal_time[i]);
			if (get_time_in_ms(time) - get_time_in_ms(env->ph[i].meal_time) >= env->time_to_die)
			{
				pthread_mutex_unlock(&env->m_meal_time[i]);
				pthread_mutex_lock(&env->m_alive);
				env->alive = 1;
				pthread_mutex_unlock(&env->m_alive);
				usleep(1000);
				env->who_is_dead = i + 1; 
				gettimeofday(&time, NULL);
				printf("%-3d MS %d died\n", (int)(-get_time_in_ms(env->start)
						+ get_time_in_ms(time)), env->who_is_dead);
				return (NULL);
			}
			pthread_mutex_unlock(&env->m_meal_time[i]);
			usleep(1000);
			i++;
		}
	}
	pthread_mutex_unlock(&env->m_alive);
	return (NULL);
}

int	ft_join_thread(t_env *env)
{
	int	i;

	i = -1;
	while (++i <= env->nb_of_ph)
		pthread_join(env->ph[i].thread, NULL);
	return (0);
}

int	ft_init_thread(t_env *env)
{
	int	i;

	i = 0;
	env->ph = (t_philo *)malloc((env->nb_of_ph + 1) * sizeof(t_philo));
	if (env->ph == NULL)
		return (1);
	while (i < env->nb_of_ph)
	{
		pthread_mutex_lock(&env->m_meal_time[i]);
		env->ph[i].meal_time.tv_sec = env->start.tv_sec;
		env->ph[i].meal_time.tv_usec = env->start.tv_usec;
		pthread_mutex_unlock(&env->m_meal_time[i]);
		i++;
	}
	i = 0;
	pthread_create(&env->ph[i].thread, NULL, check_time_last_meal, (void *)env);
	while (i < env->nb_of_ph)
	{
		env->ph[i].id = i;
		env->ph[i].num_of_eat = env->num_of_eat;
		env->ph[i].env = env;
		pthread_mutex_lock(&env->m_meal_time[i]);
		env->ph[i].meal_time.tv_sec = env->start.tv_sec;
		env->ph[i].meal_time.tv_usec = env->start.tv_usec;
		pthread_mutex_unlock(&env->m_meal_time[i]);
		pthread_create(&env->ph[i].thread, NULL, launch_thread, (void *)&env->ph[i]);
		usleep(10);
		i++;
	}
	if (ft_join_thread(env))
		return (1);
	return (0);
}
