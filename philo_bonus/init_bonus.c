/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:55:47 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/17 20:27:13 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

// void	cast_str_data(t_data **data, char **argv)
// {
// 	(*data)->count = ft_atoi(argv[1]);
// 	(*data)->die_time = ft_atoi(argv[2]);
// 	(*data)->eat_time = ft_atoi(argv[3]);
// 	(*data)->sleep_time = ft_atoi(argv[4]);
// 	(*data)->must_eat = -1;
// 	if (argv[5])
// 		(*data)->must_eat = ft_atoi(argv[5]);
// }

t_philo *init_philo(t_data *data, int index, t_sems *sems)
{
	t_philo *philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = index;
	philo->eat_count = 0;
	philo->last_meal = get_time_in_ms();
	philo->data = data;
	philo->sems = sems;
	return (philo);
}

t_sems *init_semaphores(int count)
{
	t_sems *sems;

	sems = (t_sems *)malloc(sizeof(t_sems));
	if (!sems)
		return (NULL);
	sems->forks = sem_open(SEM_FORKS, O_CREAT, 0644, count);
	sems->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	sems->meal = sem_open(SEM_MEAL, O_CREAT, 0644, 1);
	sems->stop = sem_open(SEM_STOP, O_CREAT, 0644, 1);
	return (sems);
}

t_data	*init_data(char **argv)
{
	int		i;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->count = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	return (data);
}
