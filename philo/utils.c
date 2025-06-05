/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:55:47 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/05 21:28:48 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

pthread_mutex_t	*init_forks(int count)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			break ;
		++i;
	}
	if (i != count)
	{
		count = i;
		i = 0;
		while (i < count)
		{
			pthread_mutex_destroy(&forks[i]);
			++i;
		}
		return (free(forks), NULL);
	}
	return (forks);
}

pthread_t	*init_threads(int count)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * count);
	if (!threads)
		return (NULL);
	return (threads);
}

void	*init_data(t_data *data, char **argv)
{
	data->forks = init_forks(ft_atoi(argv[1]));
	data->philos = init_threads(ft_atoi(argv[1]));
	if (!data->forks || !data->philos)
	{
		ft_error(5, 0);
		return (free(data), NULL);
	}
	data->count = ft_atoi(argv[1]);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (data);
}

t_philo	*init_philos(int count)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * count);
	if (!philos)
		return (NULL);
	while (i < count)
	{
		philos[i].id = i + 1;
		++i;
	}
	return (philos);
}
