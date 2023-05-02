/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:12 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/02 16:10:12 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	are_threads_synched(t_vars *vars)
{
	bool	all_synced;

	pthread_mutex_lock(&vars->synchro);
	all_synced = vars->synched == vars->nb_philo;
	all_synced &= vars->start_time != 0;
	pthread_mutex_unlock(&vars->synchro);
	return (all_synced);
}

void	thread_synching(t_vars *vars)
{
	pthread_mutex_lock(&vars->synchro);
	++(vars->synched);
	pthread_mutex_unlock(&vars->synchro);
	while (!are_threads_synched(vars))
	{
		if (must_simul_end(vars))
			return ;
	}
}
