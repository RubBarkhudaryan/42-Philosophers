/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:22:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/03 17:22:12 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	think_handle(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 't', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

int	forks_handle(t_philo *philo, t_data *data)
{
	int	right;
	int	left;

	right = (philo->id + 1) % data->count;
	left = philo->id;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[right]);
		pthread_mutex_lock(&data->forks[left]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[left]);
		pthread_mutex_lock(&data->forks[right]);
	}
	philo->r_fork = &data->forks[right];
	philo->l_fork = &data->forks[left];
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 'f', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

/*
[even]
picks right then left
puts left then right

[odd]
picks left then right
puts right then left
*/

int	eat_handle(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 'e', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(data->eat);
	pthread_mutex_lock(&data->eat_mutex);
	philo->eat_count++;
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

int	sleep_handle(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 's', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(data->sleep);
	return (0);
}
