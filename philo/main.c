/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/22 17:34:35 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->count == 1)
	{
		ft_usleep(data->die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(data->eat / 2);
	while (!check_death(data) && !check_fullness(data))
	{
		if (forks_handle(philo, data))
			break ;
		if (eat_handle(philo, data))
			break ;
		if (sleep_handle(philo, data))
			break ;
		if (think_handle(philo, data))
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;

	if ((argc == 5 || argc == 6) && is_valid(argv))
	{
		data = init_data(argv);
		i = -1;
		while (++i < data->count)
			pthread_create(&data->threads[i], NULL,
				&routine, &data->philos[i]);
		pthread_create(&data->monitoring, NULL, &monitoring_death, data);
		pthread_create(&data->eat_thread, NULL, &eat_monitoring, data);
		i = -1;
		while (++i < data->count)
			pthread_join(data->threads[i], NULL);
		pthread_join(data->monitoring, NULL);
		pthread_join(data->eat_thread, NULL);
		i = -1;
		while (++i < data->count)
			pthread_mutex_destroy(&data->forks[i]);
		if (!data->dead && data->full)
			print_action(&data->philos[0], 'q', data->start_time);
		return (free_data(&data), 0);
	}
	return (ft_error(1, 0), 1);
}
