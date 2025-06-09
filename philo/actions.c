/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:22:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/09 20:02:08 by rbarkhud         ###   ########.fr       */
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

// int	forks_handle(t_philo *philo, t_data *data)
// {
// 	return (0);
// }

// int	eat_handle(t_philo *philo, t_data *data)
// {
// 	return (0);
// }

int	sleep_handle(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	print_action(philo, 's', data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(data->sleep);
	return (0);
}
