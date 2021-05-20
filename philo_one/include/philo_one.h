/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:34:38 by ehautefa          #+#    #+#             */
/*   Updated: 2021/05/20 15:02:38 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

typedef struct	s_arg
{
	int		nb_of_ph;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_eat;
}				t_arg;

int		ft_atoi(const char *str);
