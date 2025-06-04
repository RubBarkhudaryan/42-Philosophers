/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:55:47 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/04 19:40:24 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

t_philo	*init_philos(char **argv)
{
	int		i;
	int		count;
	t_philo	*philos;

	i = -1;
	count = ft_atoi(argv[1]);
	philos = (t_philo *)malloc(sizeof(t_philo) * count);
	if (!philos)
		return (ft_error(5, 0), NULL);
	while (++i < count)
	{
		philos[i].id = i + 1;
		philos[i].die = ft_atoi(argv[2]);
		philos[i].eat = ft_atoi(argv[3]);
		philos[i].sleep = ft_atoi(argv[4]);
		if (argv[5])
			philos[i].must_eat = ft_atoi(argv[5]);
		else
			philos[i].must_eat = -1;
		if (pthread_create(&philos[i].philo, NULL, &routine, (void *)(philos + i)))
			return (free_philos(philos, i), NULL);
		usleep(42);
	}
	return (init_forks(&philos, count), philos);
}

void	init_forks(t_philo **philos, int count)
{
    int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&(*philos)[i].l_fork, NULL);
		pthread_mutex_init(&(*philos)[i].r_fork, NULL);
		++i;
	}
}

long long	get_current_time(	)