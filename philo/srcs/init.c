/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:18 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/10 15:16:28 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*new_philo(int nb, t_vars *vars)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->nb = nb;
	philo->meal_number = 0;
	philo->last_eat = 0;
	philo->vars = vars;
	philo->next = philo;
	philo->prev = philo;
	return (philo);
}

static bool	init_philos(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 1;
	while (i < vars->nb_philo + 1)
	{
		philo = new_philo(i, vars);
		if (!philo)
			return (free_philos(vars->philos), false);
		if (vars->philos)
		{
			philo->next = vars->philos;
			philo->prev = vars->philos->prev;
			vars->philos->prev->next = philo;
			vars->philos->prev = philo;
		}
		else
			vars->philos = philo;
		++i;
	}
	return (true);
}

static bool	init_philo_threads(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = vars->philos;
	while (i < vars->nb_philo)
	{
		if (pthread_create(&philo->thread, NULL, &simulation, (void *)philo))
		{
			join_philo_threads(vars, philo->nb);
			vars->end = true;
			return (false);
		}
		philo = philo->next;
		++i;
	}
	return (true);
}

bool	init(t_vars	*vars)
{
	if (init_philos(vars) == false)
		return (free_philos(vars->philos), false);
	if (vars->nb_philo == 1)
		return (sole_philo(vars->philos, vars), true);
	if (init_mutexes(vars) == false)
		return (destroy_mutexes(vars), free_philos(vars->philos), false);
	if (init_philo_threads(vars) == false)
		return (destroy_mutexes(vars), free_philos(vars->philos), false);
	if (set_time_start(vars) == false)
		return (join_philo_threads(vars, vars->nb_philo),
			destroy_mutexes(vars), free_philos(vars->philos), false);
	monitor(vars->philos, vars);
	return (true);
}
