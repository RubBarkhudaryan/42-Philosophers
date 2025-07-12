/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:10:07 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/13 01:10:07 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	try_pick_forks(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);

		if (check_death(data))
		{
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);
		
		pthread_mutex_lock(philo->l_fork);
		if (check_death(data))
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);

		if (check_death(data))
		{
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}

		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);

		pthread_mutex_lock(philo->r_fork);
		if (check_death(data))
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}

		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);

	}

	return (0);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
