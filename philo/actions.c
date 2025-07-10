/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:22:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/10 16:30:29 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	pick_fork(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(&data->print_mutex);
		print_action(philo, 'f', data->start_time);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

int	think_handle(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return (1);
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 't', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

int	forks_handle(t_philo *philo, t_data *data)
{
	int	left;
	int	right;

	if (check_death(data))
		return (1);
	left = philo->id - 1;
	right = (philo->id) % data->count;
	philo->l_fork = &data->forks[left];
	philo->r_fork = &data->forks[right];
	pick_fork(philo, data);
	return (0);
}

int	eat_handle(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return (1);
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 'e', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(data->eat);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eat_count++;
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->eat_mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	return (0);
}

int	sleep_handle(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return (1);
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 's', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(data->sleep);
	return (0);
}
