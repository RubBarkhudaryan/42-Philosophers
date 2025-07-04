/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:11:56 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/03 21:51:10 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long long	get_time_in_ms(void)
{
	long long		ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	free_data(t_data **data)
{
	pthread_mutex_destroy(&(*data)->death_mutex);
	pthread_mutex_destroy(&(*data)->eat_mutex);
	pthread_mutex_destroy(&(*data)->print_mutex);
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
		usleep(100);
}
