/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:45:53 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/28 16:30:44 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_env(t_env *env)
{
	if (env->nb_of_ph < 0 || env->time_to_die < 0
		|| env->time_to_sleep < 0 || env->time_to_eat < 0)
		return (print_error("INVALID ARGUMENTS", -1));
	if (env->nb_of_ph == 0)
		return (print_error(NULL, -1));
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
				return (print_error("ARGUMENT AREN'T NUMBER", -1));
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
	else
		env->num_of_eat = -1;
	env->alive = 0;
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	print_error(char *error, int retur)
{
	if (error == NULL)
		return (retur);
	write(2, "philo :", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (retur);
}

int	main(int ac, char **av)
{
	t_env		env;

	if (gettimeofday(&env.start, NULL) != 0)
		return (print_error("FIRST GET_TIME_OF_DAY_FAILED", -1));
	if (ac != 5 && ac != 6)
		return (print_error("NOT ENOUGH OR TOO MANY ARGUMENTS", -1));
	if (ft_init_env(ac, av, &env) || ft_check_env(&env)
		|| ft_init_forks(&env) || ft_init_mutex_meal_time(&env))
		return (1);
	if (ft_init_thread(&env))
		return (1);
	ft_free(&env);
	return (0);
}
