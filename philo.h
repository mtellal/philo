/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <mtellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:42:44 by mtellal           #+#    #+#             */
/*   Updated: 2022/03/09 18:23:41 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <pthread.h>
# include <sys/time.h>

typedef struct s_data {
	int				nbp;
	int				ttd;
	int				tte;
	int				tts;
	int				must_e;
	int				*pmort;
	size_t			*time;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	lmeal;
}		t_data;

typedef struct s_philo {
	int		*id;
	size_t	*lmeal;
	int		*nm;
	t_data	*d;
}		t_philo;

/////	   PARSE    /////

int		ft_atoi(char *s);
int		only_digit(char *s);
int		verif_args(int i, char **argv);

/////      INIT     /////

int		init_mutex(t_data *p);
int		init_philo(t_philo *p, int i, t_data *d);
int		init_data(t_data *d, char **argv, int nb, int argc);

void	clear(t_philo *p, pthread_t *t);

/////    THREADS    /////

void	*create_tab(int nb);
void	create_threads(pthread_t *t, t_philo *p, int nb, t_data *d);
void	join_threads(pthread_t *t, int nb);

/////	 ROUTINE    /////

void	*philo_one(void *p);
int		actions(t_philo *p, int r, int l);
void	*verify(void *philo);
void	*routine(void *philo);

/////      UTILS    /////

int		error(char *s);
void	display(t_philo *p, int i, char *msg);
size_t	get_time(void);
void	ft_sleep(size_t time);

#endif
