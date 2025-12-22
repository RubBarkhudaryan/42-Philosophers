/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:11:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/22 17:32:13 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static int	all_philos_ate(t_data *data)
{
	int	i;
	int	fullness;

	i = -1;
	fullness = 0;
	while (++i < data->count && !check_death(data))
	{
		pthread_mutex_lock(&data->philos[i].eat_mutex);
		if (data->must_eat > 0 && data->philos[i].eat_count >= data->must_eat)
			++fullness;
		pthread_mutex_unlock(&data->philos[i].eat_mutex);
	}
	return (fullness == data->count);
}

int	check_death(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->death_mutex);
	status = data->dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (status);
}

int	check_fullness(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->meal_mutex);
	status = data->full;
	pthread_mutex_unlock(&data->meal_mutex);
	return (status);
}

void	*monitoring_death(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (!check_death(data) && !check_fullness(data))
	{
		i = -1;
		while (++i < data->count)
		{
			if (get_last_meal(&data->philos[i]) >= data->die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				print_action(&data->philos[i], 'd', data->start_time);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}

void	*eat_monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_death(data) && !check_fullness(data))
	{
		if (all_philos_ate(data))
		{
			pthread_mutex_lock(&data->meal_mutex);
			data->full = 1;
			pthread_mutex_unlock(&data->meal_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
