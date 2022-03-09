/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:29:15 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/09 18:24:41 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	detruit et free les variables utilises par les philos,
 *	data, le tableau de threads et les mutex
 *	probleme avec destroy(death) => data race pourquoi ??? 
 */

void	clear(t_philo *p, pthread_t *t)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&p->d->print);
	pthread_mutex_destroy(&p->d->lmeal);
	while (i < p->d->nbp)
	{
		pthread_mutex_destroy(&p->d->forks_m[i]);
		free(p[i].id);
		free(p[i].lmeal);
		free(p[i].nm);
		i++;
	}
	free(p->d->forks_m);
	free(p->d->time);
	free(p->d->pmort);
	free(t);
}

/*
 *	initialise le tableau de forks(1 mu/philo)
 *	ainsi que les autres mutex (print death last_meal)
 */

int	init_mutex(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->nbp)
	{
		pthread_mutex_init(&p->forks_m[i], NULL);
		i++;
	}
	pthread_mutex_init(&p->print, NULL);
	pthread_mutex_init(&p->death, NULL);
	pthread_mutex_init(&p->lmeal, NULL);
	return (1);
}

/*
 *	affecte les variables dont le philo a besoin
 *	(lmeal = last_meal, nm = number meals)
 */

int	init_philo(t_philo *p, int i, t_data *d)
{
	p->id = malloc(sizeof(int));
	p->lmeal = malloc(sizeof(size_t));
	p->nm = malloc(sizeof(int));
	if (!p->id || !p->lmeal || !p->nm)
		return (error("problem in initializing t_philo"));
	*p->id = i;
	*p->lmeal = get_time();
	p->d = d;
	if (d->must_e != -1)
		*p->nm = 0;
	else
		*p->nm = -1;
	return (1);
}

/*
 *	affecte les variables provenant des args,
 *	ces variables sont partagees par tous les philos (philo->data)
 */

int	init_data(t_data *s, char **argv, int nb, int argc)
{
	s->nbp = nb;
	s->ttd = ft_atoi(argv[2]);
	s->tte = ft_atoi(argv[3]);
	s->tts = ft_atoi(argv[4]);
	if (argc == 6)
		s->must_e = ft_atoi(argv[5]);
	else
		s->must_e = -1;
	if (s->must_e == 0)
		return (0);
	s->forks_m = malloc(sizeof(pthread_mutex_t) * nb);
	s->time = malloc(sizeof(size_t));
	*s->time = get_time();
	s->pmort = malloc(sizeof(int));
	if (!s->forks_m || !s->time || !s->pmort)
	{
		error("problem in allocating data");
		return (0);
	}
	*s->pmort = -1;
	return (1);
}
