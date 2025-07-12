/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:11:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/12 20:11:45 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	check_death(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->death_mutex);
	status = data->dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (status);
}

void	*monitoring_death(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (!check_death(data))
	{
		i = -1;
		while (++i < data->count)
		{
			pthread_mutex_lock(&data->philos[i].eat_mutex);
			if (get_time_in_ms() - data->philos[i].last_meal >= data->die)
			{
				pthread_mutex_unlock(&data->philos[i].eat_mutex);
				pthread_mutex_lock(&data->death_mutex);
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_lock(&data->print_mutex);
				print_action(&data->philos[i], 'd', data->start_time);
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].eat_mutex);
		}
		usleep(100);
	}
	return (NULL);
}
