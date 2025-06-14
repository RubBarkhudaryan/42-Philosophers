/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/09 20:05:57 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (true)
	{
		if (think_handle(philo, data))
			break ;
		// if (forks_handle(philo, data))
		// 	break ;
		// if (eat_handle(philo, data))
		// 	break ;
		if (sleep_handle(philo, data))
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
			pthread_create(&data->threads[i], NULL, &routine, (void *)&data->philos[i]);
		i = -1;
		while (++i < data->count)
			pthread_join(data->threads[i], NULL);
		i = -1;
		while (++i < data->count)
			pthread_mutex_destroy(&data->forks[i]);
		free_data(&data);
	}
	else if (argc < 5)
		ft_error(1, 0);
	return (0);
}
