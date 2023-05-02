/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:15 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/02 16:10:15 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_to_zero(t_vars *vars)
{
	vars->nb_philo = 0;
	vars->ttd = 0;
	vars->tte = 0;
	vars->tts = 0;
	vars->ttf = -1;
	vars->philos = NULL;
	vars->start_time = 0;
	vars->end = false;
	vars->ate_enough = 0;
	vars->synched = 0;
}

bool	parsing(int ac, char **av, t_vars *vars)
{
	set_to_zero(vars);
	if (atoi_def(av[1], &vars->nb_philo) == false)
		return (false);
	if (atoi_def(av[2], &vars->ttd) == false)
		return (false);
	if (atoi_def(av[3], &vars->tte) == false)
		return (false);
	if (atoi_def(av[4], &vars->tts) == false)
		return (false);
	if (ac == 6 && atoi_def(av[5], &vars->ttf) == false)
		return (false);
	vars->ttd *= 1000;
	vars->tte *= 1000;
	vars->tts *= 1000;
	return (true);
}
