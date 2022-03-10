/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:32:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/10 08:54:35 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	rassemble l'ensemble des threads une fois la simulation terminee 	
 */

void	join_threads(pthread_t *t, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_join(t[i], NULL) != 0)
		{
			error("problem in joining threads");
			return ;
		}
		i++;
	}
}

/*
 *	sous fonction de verify, s'execute lorsqu'un philo meurt
 */

void	*death(t_philo *p, t_data *data, int i)
{
	pthread_mutex_lock(&data->death);
	if (*data->pmort == -1)
		*data->pmort = *p[i].id;
	pthread_mutex_unlock(&data->death);
	printf(" %7lu | # %i died\n", (get_time() - *data->time), i + 1);
	return (NULL);
}

/*
 *	thread lance en parallele des philos
 *	tant que tous les philos n'ont pas manges ou nm non def
 *	verifire que le philo i n'est pas mort entre 2 repas
 */

void	*verify(void *philo)
{
	t_philo	*p;
	t_data	*data;
	int		i;

	p = (t_philo *)philo;
	data = p->d;
	i = 0;
	while (*p[i].nm == -1 || *p[i].nm != data->must_e)
	{
		pthread_mutex_lock(&data->lmeal);
		if ((get_time() - *p[i].lmeal) >= (size_t)data->ttd)
		{
			pthread_mutex_unlock(&p->d->lmeal);
			death(p, data, i);
			return (NULL);
		}
		pthread_mutex_unlock(&data->lmeal);
		if (i == data->nbp - 1)
			i = 0;
		else
			i++;
	}
	return (NULL);
}

int	init_and_verify(pthread_t *th, t_philo *p, int nb, t_data *d)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		init_philo(&p[i], i, d);
		i++;
	}
	if (pthread_create(th, NULL, verify, p) != 0)
		return (0);
	return (1);
}

/*
 *      creer et initialise un tableau de philo p
 *      et lance autant de threads qu'il n y a de philo
 */

void	create_threads(pthread_t *t, t_philo *p, int nb, t_data *d)
{
	int			i;
	pthread_t	th;

	i = 0;
	if (!init_and_verify(&th, p, nb, d))
		return ;
	if (d->nbp == 1)
	{
		if (pthread_create(&t[0], NULL, &philo_one, &p[0]) != 0)
			return ;
	}
	else
	{
		while (i < nb)
		{
			if (pthread_create(&t[i], NULL, &routine, &p[i]) != 0)
			{
				error("problem in creating threads");
				return ;
			}
			i++;
		}
	}
	pthread_detach(th);
}
