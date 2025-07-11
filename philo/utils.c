/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:11:56 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/11 21:44:49 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	free_data(t_data **data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(*data)->death_mutex);
	pthread_mutex_destroy(&(*data)->print_mutex);
	while (i < (*data)->count)
	{
		pthread_mutex_destroy(&(*data)->philos[i].eat_mutex);
		++i;
	}
	free((*data)->philos);
	free((*data)->forks);
	free((*data)->threads);
	free((*data));
}

void	ft_usleep(long long ms)
{
	long long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < ms)
		usleep(50);
}
