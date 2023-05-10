/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:07 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/10 22:44:00 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sole_philo(t_philo *philo, t_vars *vars)
{
	t_ul			time;

	time = 0;
	get_time(&vars->start_time);
	get_time(&philo->last_eat);
	get_time(&time);
	printf("%lu %d has taken a fork\n", (time - vars->start_time) / 1000,
		philo->nb);
	while (true)
	{
		get_time(&time);
		if ((int)(time - philo->last_eat) >= vars->ttd)
			break ;
		ft_usleep(200);
	}
	printf("%lu %d died\n", (time - vars->start_time) / 1000, philo->nb);
	vars->end = true;
}

bool	must_simul_end(t_vars *vars)
{
	bool	must_end;

	pthread_mutex_lock(&vars->m_end);
	must_end = vars->end;
	pthread_mutex_unlock(&vars->m_end);
	pthread_mutex_lock(&vars->m_ate_enough);
	if (vars->ate_enough >= vars->nb_philo)
		must_end = true;
	pthread_mutex_unlock(&vars->m_ate_enough);
	return (must_end);
}

void	*simulation(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	thread_synching(philo->vars);
	if (philo->nb % 2 == 0)
		ft_usleep(10000);
	while (!must_simul_end(vars))
	{
		take_forks(philo, vars);
		eat(philo, vars);
		give_back_forks(philo, vars);
		print_action(philo, SLEEPING, vars);
		ft_usleep(vars->tts);
		print_action(philo, THINKING, vars);
		ft_usleep(1000);
	}
	return (NULL);
}

void	monitor(t_philo *philo, t_vars *vars)
{
	t_ul	time;

	ft_usleep(20000);
	while (true)
	{
		pthread_mutex_lock(&philo->m_last_eat);
		get_time(&time);
		if ((int)(time - philo->last_eat) >= vars->ttd)
		{
			pthread_mutex_unlock(&philo->m_last_eat);
			pthread_mutex_lock(&vars->m_end);
			vars->end = true;
			pthread_mutex_unlock(&vars->m_end);
			printf("%lu %d died\n", (time - vars->start_time) / 1000,
				philo->nb);
			break ;
		}
		pthread_mutex_unlock(&philo->m_last_eat);
		if (must_simul_end(vars))
			break ;
		philo = philo->next;
	}
}
