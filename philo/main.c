/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/04 19:26:50 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_think(philo))
			break ;
		if (ft_forks(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
	}
	return (NULL);
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
