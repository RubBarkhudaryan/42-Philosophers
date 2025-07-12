/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:11:56 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/12 20:12:03 by rbarkhud         ###   ########.fr       */
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

void	print_action(t_philo *philo, char action, long long timestamp)
{
	long long	curr_time;

	curr_time = get_time_in_ms();
	if (action == 'f')
		printf("%lld %d has taken a fork\n", curr_time - timestamp, philo->id);
	else if (action == 'e')
		printf("%lld %d is eating\n", curr_time - timestamp, philo->id);
	else if (action == 's')
		printf("%lld %d is sleeping\n", curr_time - timestamp, philo->id);
	else if (action == 't')
		printf("%lld %d is thinking\n", curr_time - timestamp, philo->id);
	else if (action == 'd')
		printf("%lld %d died\n", curr_time - timestamp, philo->id);
}
