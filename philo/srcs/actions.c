/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:24 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/05 13:43:37 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo, t_vars *vars)
{
	if (vars->ttf != -1 && philo->meal_number >= vars->ttf)
		return ;
	print_action(philo, EATING, vars);
	pthread_mutex_lock(&philo->m_last_eat);
	get_time(&philo->last_eat);
	pthread_mutex_unlock(&philo->m_last_eat);
	++(philo->meal_number);
	if (philo->meal_number == vars->ttf)
	{
		pthread_mutex_lock(&vars->m_ate_enough);
		++(vars->ate_enough);
		pthread_mutex_unlock(&vars->m_ate_enough);
	}
	ft_usleep(vars->tte);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

/*
	Philosophers have their own fork and also take the fork of the next philo
*/
void	take_forks(t_philo *philo, t_vars *vars)
{
	if (philo->nb == 2)
	{
		pthread_mutex_lock(&philo->fork);
		print_action(philo, TAKEN_FORK, vars);
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, TAKEN_FORK, vars);
		return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, TAKEN_FORK, vars);
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TAKEN_FORK, vars);
}
