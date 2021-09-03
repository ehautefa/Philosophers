/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisehautefaye <elisehautefaye@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 22:01:31 by elisehautef       #+#    #+#             */
/*   Updated: 2021/09/03 22:32:48 by elisehautef      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	write(2, "PHILO : ", 8);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (retur);
}

char	*ft_itoa(long num)
{
	int		count;
	long	tmp;
	char	*retur;
	int		i;

	i = 0;
	count = -1;
	tmp = num;
	while (tmp != 0 && ++tmp >= 0)
		tmp = tmp / 10;
	retur = malloc((count + 1) * sizeof(*retur));
	if (retur == NULL)
		return (NULL);
	while (i < count)
	{
		retur[count - 1 - i] = num % 10 - '0';
		num = num / 10;
		i++;
	}
	retur[count] = '\0';
	return (retur);
}

int	ft_print_long(long num)
{
	int		count;
	long	tmp;
	char	c;

	count = -1;
	tmp = num;
	while (tmp != 0 && ++count >= 0)
		tmp = tmp / 10;
	while (count > 0)
	{
		c = (num >> count) - '0';
		printf("count : %d num << count : %ld\n",count, num << count);
		write(1, &c, 1);
		num = num / 10;
		count--;
	}
	return (0);
}

int	print_result(long elapsed_time, int philo, char *msg)
{
	char c;
	char *str;

	str = ft_itoa(elapsed_time);
	if (str == NULL)
		return(print_error("MALLOC ERROR", -1));
	write(1, str, ft_strlen(str));
	free(str);
	write(1, " MS ", 4);
	str = ft_itoa((long)philo);
	if (str == NULL)
		return(print_error("MALLOC ERROR", -1));
	write(1, str, ft_strlen(str));
	free(str);
	write(1, msg, ft_strlen(msg));
	return(0);
}

int	main(int ac, char **av)
{
	ac -=1;
	while (ac > 0)
	{
		ft_print_long(atol(av[ac]));
		ac--;
		write(1, "\n", 1);
	}
	return (0);
}