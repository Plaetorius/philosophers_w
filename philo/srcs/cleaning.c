/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:21 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/10 22:54:27 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_philo_threads(t_vars *vars, int failed_nb)
{
	int		i;
	int		failed;
	t_philo	*philo;

	i = 0;
	philo = vars->philos;
	if (vars->nb_philo == 1)
		return (0);
	while (i < failed_nb)
	{
		failed = pthread_join(philo->thread, NULL);
		if (failed)
		{
			printf("Failed joining philo %d code %d\n", philo->nb, failed);
			pthread_detach(philo->thread);
		}
		philo = philo->next;
		++i;
	}
	return (failed);
}

/*
	Free Philos
	The condition "philo != NULL" is to protect against a failure that might
	happen when this function is being called in create_philos, in case of a
	malloc fail
*/
void	free_philos(t_philo *philo)
{
	const int	nb_philo = philo->vars->nb_philo;
	int			i;
	t_philo		*tmp;

	i = 0;
	while (i < nb_philo && philo != NULL)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		++i;
	}
	philo = NULL;
}
