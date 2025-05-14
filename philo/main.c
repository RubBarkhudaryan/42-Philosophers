/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/05/14 19:03:10 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	*print()
{
	printf("Thread created\n");
	return (NULL);
}

static void	free_philos(t_philo *philos, int count)
{
	philos = (void *)philos;
	count = (long) count;
	printf("freeing philos array...\n");
}

static t_philo	*init_philos(char **argv)
{
	int		i;
	int		count;
	t_philo	*philos;

	i = 0;
	count = ft_atoi(argv[1]);
	philos = (t_philo *)malloc(sizeof(t_philo) * count);
	if (!philos)
		return (ft_error(5, 0), NULL);
	while (i < count)
	{
		philos[i].id = i + 1;
		philos[i].die = ft_atoi(argv[2]);
		philos[i].eat = ft_atoi(argv[3]);
		philos[i].sleep = ft_atoi(argv[4]);
		if (argv[5])
			philos[i].must_eat = ft_atoi(argv[5]);
		else
			philos[i].must_eat = -1;
		if (pthread_create(&philos[i].philo, NULL, &print, NULL) != 0)
			return (free_philos(philos, i), NULL);
		usleep(42);
		++i;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	
	if ((argc == 5 || argc == 6) && is_valid(argv))
	{
		philos = init_philos(argv);
		if (!philos)
			ft_error(5, 0);
	}
	else if (argc < 5)
		ft_error(1, 0);
	return (0);
}
