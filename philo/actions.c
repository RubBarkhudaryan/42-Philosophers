/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:22:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/22 17:31:25 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	think_handle(t_philo *philo, t_data *data)
{
	if (check_death(data) || check_fullness(data))
		return (1);
	print_action(philo, 't', data->start_time);
	ft_usleep(1);
	return (0);
}

int	forks_handle(t_philo *philo, t_data *data)
{
	size_t	left;
	size_t	right;

	left = philo->id - 1;
	right = philo->id % data->count;
	philo->l_fork = &data->forks[left];
	philo->r_fork = &data->forks[right];
	if (philo->id % 2 == 0)
	{
		if (check_death(data) || check_fullness(data)
			|| try_pick_forks_evens(philo, data))
			return (1);
	}
	else
	{
		if (check_death(data) || check_fullness(data)
			|| try_pick_forks_odds(philo, data))
			return (1);
	}
	return (0);
}

int	eat_handle(t_philo *philo, t_data *data)
{
	if (check_death(data) || check_fullness(data))
		return (1);
	print_action(philo, 'e', data->start_time);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_usleep(data->eat);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_mutex);
	drop_forks(philo);
	return (0);
}

int	sleep_handle(t_philo *philo, t_data *data)
{
	if (check_death(data) || check_fullness(data))
		return (1);
	print_action(philo, 's', data->start_time);
	ft_usleep(data->sleep);
	return (0);
}
