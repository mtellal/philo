/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:38:32 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/10 08:51:14 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *      creer un tableau de threads
 */

void	*create_tab(int nb)
{
	pthread_t	*tab;

	tab = malloc(sizeof(pthread_t) * nb);
	if (!tab)
		return (NULL);
	return (tab);
}

int	main(int argc, char **argv)
{
	pthread_t	*t;
	t_data		d;
	t_philo		*p;
	int			nb;

	if (argc >= 5 && argc <= 6)
	{
		if (!verif_args(argc, argv))
			return (0);
		nb = ft_atoi(argv[1]);
		if (!(init_data(&d, argv, nb, argc)) || !init_mutex(&d))
			return (0);
		t = (pthread_t *)create_tab(nb);
		p = malloc(sizeof(t_philo) * nb);
		if (!p)
			return (0);
		create_threads(t, p, nb, &d);
		join_threads(t, nb);
		clear(p, t);
		free(p);
	}
	return (0);
}
