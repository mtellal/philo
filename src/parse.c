/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:51:39 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/09 16:02:42 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nptr)
{
	int		i;
	int		s;

	i = 0;
	s = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			s = s * -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		i = (10 * i) + (*nptr - '0');
		nptr++;
	}
	i = i * s;
	return (i);
}

int	only_digit(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	verif_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i <= argc)
	{
		if (!only_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
