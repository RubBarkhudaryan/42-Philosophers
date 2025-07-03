/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:11:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/03 21:52:48 by rbarkhud         ###   ########.fr       */
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
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (true)
	{
		i = -1;
		while (++i < data->count)
		{
			pthread_mutex_lock(&data->eat_mutex);
			if ((get_time_in_ms() - data->philos[i].last_meal) > data->die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_lock(&data->print_mutex);
				print_action(&data->philos[i], 'd', data->start_time);
				pthread_mutex_unlock(&data->print_mutex);
				return (pthread_mutex_unlock(&data->eat_mutex), NULL);
			}
			pthread_mutex_unlock(&data->eat_mutex);
		}
		ft_usleep(1000);
	}
	return (NULL);
}
