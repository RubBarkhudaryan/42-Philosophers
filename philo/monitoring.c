/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:11:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/11 22:13:54 by rbarkhud         ###   ########.fr       */
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
	long	time_since_last_meal;

	data = (t_data *)arg;
	while (!check_death(data))
	{
		i = -1;
		while (++i < data->count)
		{
			pthread_mutex_lock(&data->philos[i].eat_mutex);
			time_since_last_meal = (get_time_in_ms() - data->philos[i].last_meal);
			pthread_mutex_unlock(&data->philos[i].eat_mutex);
			if (time_since_last_meal >= data->die && !data->philos[i].is_eating)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				print_action(&data->philos[i], 'd', data->start_time);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

			// pthread_mutex_lock(&data->print_mutex);
			// printf("get_time_in_ms() - data->philos[i].last_meal=%lld\ni = %d\n", get_time_in_ms() - data->philos[i].last_meal, i);
			// pthread_mutex_unlock(&data->print_mutex);
			