/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/16 02:15:04 by rbarkhud         ###   ########.fr       */
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
		ft_usleep(data->die);
	if (philo->id % 2 == 0)
		ft_usleep(1);
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
	t_data		*data;
	int			i;

	if ((argc == 5 || argc == 6) && is_valid(argv))
	{
		data = init_data(argv);
		i = -1;
		while (++i < data->count)
			pthread_create(&data->threads[i], NULL,
				&routine, &data->philos[i]);
		pthread_create(&data->monitoring, NULL, &monitoring_death, data);
		pthread_create(&data->eat_thread, NULL, &eat_monitoring, (void *)data);
		i = -1;
		while (++i < data->count)
			pthread_join(data->threads[i], NULL);
		pthread_join(data->monitoring, NULL);
		pthread_join(data->eat_thread, NULL);
		i = -1;
		while (++i < data->count)
			pthread_mutex_destroy(&data->forks[i]);
		free_data(&data);
	}
	else
		ft_error(1, 0);
	return (0);
}
