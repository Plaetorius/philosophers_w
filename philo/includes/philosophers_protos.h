/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_protos.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:29 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/02 21:28:29 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PROTOS_H
# define PHILOSOPHERS_PROTOS_H
# include "philosophers_structs.h"
# include "philosophers.h"
# include <stdbool.h>

typedef unsigned long	t_ul;

/* PARSING */
bool		parsing(int ac, char **av, t_vars *vars);

/* INIT */
bool		init(t_vars *vars);

/* MUTEXES */
int			init_mutexes(t_vars *vars);
int			destroy_mutexes(t_vars *vars);

/* ATOI DEF */
bool		atoi_def(const char *str, int *val);

/* TIME */
bool		print_action(t_philo *philo, int action, t_vars *vars);
bool		ft_usleep(t_ul sleep_time);
bool		get_time(t_ul *val);
bool		set_time_start(t_vars *vars);

/* MEMORY */
bool		memory_cleaning(t_vars *vars);
void		free_philos(t_philo *philo);
int			join_philo_threads(t_vars *vars, int failed_nb);

/* THREADS */
void		*simulation(void *arg);
void		monitor(t_philo *philo, t_vars *vars);
bool		must_simul_end(t_vars *vars);
void		sole_philo(t_philo *philo, t_vars *vars);

/* Actions */
void		eat(t_philo *philo, t_vars *vars);
void		take_forks(t_philo *philo, t_vars *vars);

/* Synchro */
void		thread_synching(t_vars *vars);

#endif
