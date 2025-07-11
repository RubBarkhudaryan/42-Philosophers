/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:22:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/11 22:16:29 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	think_handle(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return (1);
	print_action(philo, 't', data->start_time);
	ft_usleep(1);
	return (0);
}

int	try_pick_forks(t_philo *philo, t_data *data)
{
	size_t			left;
	size_t			right;

	if (check_death(data))
		return (1);

	left = philo->id - 1;
	right = philo->id % data->count;

	philo->l_fork = &data->forks[left];
	philo->r_fork = &data->forks[right];

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);

		if (check_death(data))
		{
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}

		print_action(philo, 'f', data->start_time);

		pthread_mutex_lock(philo->l_fork);
		if (check_death(data))
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
		print_action(philo, 'f', data->start_time);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);

		if (check_death(data))
		{
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}

		print_action(philo, 'f', data->start_time);

		pthread_mutex_lock(philo->r_fork);
		if (check_death(data))
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}
		print_action(philo, 'f', data->start_time);
	}

	return (0);
}

int	forks_handle(t_philo *philo, t_data *data)
{
	if (check_death(data) || try_pick_forks(philo, data))
		return (1);
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

int	eat_handle(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return (1);
	print_action(philo, 'e', data->start_time);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->is_eating = 1;
	ft_usleep(data->eat);
	philo->eat_count++;
	philo->last_meal = get_time_in_ms();
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eat_mutex);
	drop_forks(philo);
	return (0);
}

int	sleep_handle(t_philo *philo, t_data *data)
{
	if (check_death(data))
		return (1);
	print_action(philo, 's', data->start_time);
	ft_usleep(data->sleep);
	return (0);
}
