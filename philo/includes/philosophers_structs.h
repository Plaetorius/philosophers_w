/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:28 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/02 16:14:44 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_STRUCTS_H
# define PHILOSOPHERS_STRUCTS_H
# include "philosophers_protos.h"
# include "philosophers.h"
# include <pthread.h>
# include <stdbool.h>

typedef struct s_vars	t_vars;
typedef unsigned long	t_ul;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	int					nb;
	t_ul				last_eat;
	pthread_mutex_t		mutex_last_eat;
	int					meal_number;
	bool				is_eating;
	struct s_philo		*next;
	struct s_philo		*prev;
	t_vars				*vars;
}				t_philo;

typedef struct s_vars
{
	int					nb_philo;
	int					ttd;
	int					tte;
	int					tts;
	int					ttf;
	pthread_mutex_t		message;
	t_philo				*philos;
	t_ul				start_time;
	bool				end;
	pthread_mutex_t		mutex_end;
	int					ate_enough;
	pthread_mutex_t		mutex_ate_enough;
	pthread_mutex_t		synchro;
	int					synched;
}						t_vars;

/*
	TTD: Time To Die
	TTE: Time To Eat
	TTS: Time To Sleep
	TTF: Times To Finish

	Start Time must be initialized when all threads are created
*/

#endif
