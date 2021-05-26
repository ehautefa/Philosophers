/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:09:40 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/26 16:16:00 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

void	*init_thread(void *arg)
{
	int		n;
	int		prev;
	int		next;
	t_env	*env;

	n = 10;
	env = (t_env *)arg;
	prev = (n - 1) % env->nb_of_ph;
	next = (n + 1) % env->nb_of_ph;
	if (env->ph[n].action == 2 && env->ph[prev].action != 0
		&& env->ph[next].action != 0)
	{
		env->ph[n].action = 0;
		printf("TIME %d is eating\n", env->ph[n].id);
	}
	return (env);
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
		env->ph[i].id = i;
		pthread_create(&env->ph[i].thread, NULL, init_thread, (void *)&env);
		i++;
	}
	return (0);
}

int	ft_init_forks(t_env *env)
{
	int		i;

	i = 0;
	env->nb_forks = env->nb_of_ph;
	if (env->nb_forks == 1)
		env->nb_forks = 2;
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->nb_forks);
	if (env->forks == NULL)
		return (1);
	while (i < env->nb_forks)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
