/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_def.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:10:22 by tgernez           #+#    #+#             */
/*   Updated: 2023/05/09 10:38:25 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	aux_atoi_def(const char *str, long *nb, int i)
{
	while ('0' <= str[i] && str[i] <= '9')
	{
		*nb = *nb * 10 + str[i] - '0';
		if (*nb > INT_MAX)
			return (false);
		i++;
	}
	return (true);
}

bool	atoi_def(const char *str, int *val)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i] == ' ' || (8 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (false);
	else if (str[i] == '+')
		i++;
	if (aux_atoi_def(str, &nb, i) == false)
		return (false);
	*val = nb;
	if (nb == 0)
		return (false);
	return (true);
}
