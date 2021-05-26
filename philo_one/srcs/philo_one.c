/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:45:53 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/26 16:12:33 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int	ft_check_env(t_env *env)
{
	if (env->nb_of_ph < 0 || env->time_to_die < 0
		|| env->time_to_sleep < 0 || env->time_to_eat < 0)
	{
		printf("Error,\nNegative envuments.");
		return (1);
	}
	return (0);
}

int	ft_init_env(int	ac, char **av, t_env *env)
{
	int	i;
	int	j;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9')
				return (1);
			i++;
		}
		j++;
	}
	env->nb_of_ph = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env->num_of_eat = ft_atoi(av[5]);
	return (0);
}

int	main(int ac, char **av)
{
	t_env		env;

	if (ac != 5 && ac != 6)
	{
		printf("Error,\nWrong number of envuments.");
		return (1);
	}
	if (ft_init_env(ac, av, &env) || ft_check_env(&env)
		|| ft_init_forks(&env) || ft_init_thread(&env))
	{
		printf("Error,\narguments corrupted");
		return (1);
	}
	ft_free(&env);
	pthread_exit(NULL);
	return (0);
}
