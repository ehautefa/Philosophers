/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:00:41 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/27 18:45:09 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int	ft_atoi(const char *str)
{
	int			i;
	long		res;
	int			signe;
	int			tmp;

	i = 0;
	res = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	signe = 1;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
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
	while (i < env->nb_forks)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->m_alive);
	if (env->forks)
		free(env->forks);
	env->forks = NULL;
	if (env->ph)
		free(env->ph);
	env->ph = NULL;
}

long	get_time_in_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	struct timeval	start;
	long			start_in_ms;
	long			final_time;

	gettimeofday(&start, NULL);
	start_in_ms = get_time_in_ms(start);
	final_time = start_in_ms + time;
	while (start_in_ms < final_time)
	{
		gettimeofday(&start, NULL);
		start_in_ms = get_time_in_ms(start);
		usleep(100);
	} 
}
