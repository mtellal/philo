/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:30:56 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/09 18:24:13 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

/*
 *	cas d'un seul philo, prend une fourchette
 *	display, relache la fourchette et attend la mort 
 */

void	*philo_one(void	*philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&p->d->forks_m[0]);
	display(p, 0, "has taken a fork");
	pthread_mutex_unlock(&p->d->forks_m[0]);
	ft_sleep(p->d->ttd);
	return (NULL);
}

/*
 *	bloque les fourchettes, mange
 *	incremente nm si nombre de repas def (argc == 6)
 *	modifie lmeal et lache les fourchettes, affiche les etats et dort/pense
 */

int	actions(t_philo *p, int r, int l)
{
	t_data	*d;

	d = p->d;
	pthread_mutex_lock(&d->forks_m[r]);
	display(p, r, "has taken a fork");
	pthread_mutex_lock(&d->forks_m[l]);
	display(p, r, "has taken a fork");
	display(p, r, "is eating");
	pthread_mutex_lock(&p->d->lmeal);
	*p->lmeal = get_time();
	pthread_mutex_unlock(&p->d->lmeal);
	ft_sleep(d->tte);
	pthread_mutex_unlock(&d->forks_m[r]);
	pthread_mutex_unlock(&d->forks_m[l]);
	if (*p->nm != -1)
		*p->nm += 1;
	display(p, r, "is sleeping");
	ft_sleep(d->tts);
	display(p, r, "is thinking");
	return (0);
}

/*
 *	routine pour chaque philo, lance un thread 'verify'
 *	temporise les philo paires, pour les disposer en quinconce
 *	verifie qu'aucun philo n est mort 
 *	et les nombres de repas si argc == 6
 *	execute les actions selon leurs positions
 *	(gestion du premier et dernier philo)
 */

void	*routine(void *philo)
{
	t_philo		*p;
	t_data		*data;
	int			id;

	p = (t_philo *)philo;
	data = p->d;
	id = *p->id;
	if (id % 2)
		usleep(15000);
	while (p->d->must_e == -1 || p->d->must_e != *p->nm)
	{
		pthread_mutex_lock(&data->death);
		if (*p->d->pmort != -1)
		{
			pthread_mutex_unlock(&data->death);
			return (NULL);
		}
		pthread_mutex_unlock(&p->d->death);
		if (id == (data->nbp - 1))
			actions(p, id, 0);
		else
			actions(p, id, id + 1);
	}
	return (NULL);
}
