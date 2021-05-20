/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:45:53 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/20 16:11:56 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int		ft_check_arg(t_arg *arg)
{
	if (arg->nb_of_ph < 0 ||
		arg->time_to_die < 0 ||
		arg->time_to_sleep < 0 ||
		arg->time_to_eat < 0)
	{
		printf("Error,\nNegative arguments.");
		return (-1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_arg	arg;

	if (ac != 5 && ac != 6)
	{
		printf("Error,\nWrong number of arguments.");
		return (-1);
	}
	arg.nb_of_ph = ft_atoi(av[1]);
	arg.time_to_die = ft_atoi(av[2]);
	arg.time_to_eat = ft_atoi(av[3]);
	arg.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg.num_of_eat = ft_atoi(av[5]);
	ft_check_arg(&arg);	
}