/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:55:47 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/13 22:01:04 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	cast_str_data(t_data **data, char **argv)
{
	(*data)->count = ft_atoi(argv[1]);
	(*data)->die = ft_atoi(argv[2]);
	(*data)->eat = ft_atoi(argv[3]);
	(*data)->sleep = ft_atoi(argv[4]);
	(*data)->must_eat = -1;
	if (argv[5])
		(*data)->must_eat = ft_atoi(argv[5]);
}

void	init_philo(t_philo *philo, t_data *data, int index)
{
	philo->id = index;
	philo->eat_count = 0;
	philo->last_meal = get_time_in_ms();
	philo->data = data;
	philo->l_fork = &data->forks[index];
	philo->r_fork = &data->forks[(index + 1) % data->count];
	pthread_mutex_init(&philo->eat_mutex, NULL);
}

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

t_data	*init_data(char **argv)
{
	int		i;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_error(5, 0), NULL);
	cast_str_data(&data, argv);
	data->start_time = get_time_in_ms();
	data->forks = init_forks(data->count);
	data->threads = init_threads(data->count);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->count);
	data->dead = 0;
	data->full = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	i = -1;
	while (++i < data->count)
		init_philo(&data->philos[i], data, i + 1);
	if (!data->forks || !data->threads || !data->philos)
		return (ft_error(5, 0), free_data(&data), NULL);
	return (data);
}
