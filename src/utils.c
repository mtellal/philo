/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:43:14 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/09 18:24:55 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *s)
{
	printf("%s\n", s);
	return (0);
}

/*
 * 	temps en ms (1sec = 1000msec, 1msec = 1000usec) 
 */

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

/*
 *	usleep pas assez precis ou perte de microsec par l'os
 *	donc previligier cette approche pour etre sur de respecter les 10ms apres mort
 *	et les cas tricky comme 2 410 200 200 / 3 610 200 200 etc 	
 */

void	ft_sleep(size_t time)
{
	size_t	t;

	t = get_time() + time;
	while (get_time() < t)
		usleep(10);
}

/*
 *	lock le mutex 'print' et print le msg 
 */

void	display(t_philo *p, int i, char *msg)
{
	pthread_mutex_lock(&p->d->print);
	pthread_mutex_lock(&p->d->death);
	if (*p->d->pmort == -1)
		printf(" %7lu | # %i %s\n", (get_time() - *p->d->time), i + 1, msg);
	pthread_mutex_unlock(&p->d->death);
	pthread_mutex_unlock(&p->d->print);
}
