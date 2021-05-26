/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:00:41 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/26 16:11:48 by ehautefa         ###   ########.fr       */
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
	if (env->forks)
		free(env->forks);
	env->forks = NULL;
	if (env->ph)
		free(env->ph);
	env->ph = NULL;
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		usleep(100000);
		i++;
	}
}
