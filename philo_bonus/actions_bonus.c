/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:22:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/21 19:26:07 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

int	think_handle(t_philo *philo)
{
	if (check_death(philo) || check_fullness(philo))
		return (1);
	sem_wait(philo->sems->print);
	print_action(philo, 't', philo->start_time);
	sem_post(philo->sems->print);
	ft_usleep(philo, 1);
	return (0);
}

int	eat_handle(t_philo *philo, t_data *data)
{
	if (check_death(philo) || check_fullness(philo))
		return (1);
	sem_wait(philo->sems->take);
	sem_wait(philo->sems->forks);
	sem_wait(philo->sems->forks);
	sem_post(philo->sems->take);
	sem_wait(philo->sems->print);
	print_action(philo, 'f', philo->start_time);
	print_action(philo, 'f', philo->start_time);
	sem_post(philo->sems->print);
	sem_wait(philo->sems->print);
	print_action(philo, 'e', philo->start_time);
	sem_post(philo->sems->print);
	sem_wait(philo->sems->meal);
	philo->eat_count++;
	philo->last_meal = get_time_in_ms();
	sem_post(philo->sems->meal);
	ft_usleep(philo, data->eat_time);
	sem_post(philo->sems->forks);
	sem_post(philo->sems->forks);
	return (0);
}

int	sleep_handle(t_philo *philo, t_data *data)
{
	if (check_death(philo) || check_fullness(philo))
		return (1);
	sem_wait(philo->sems->print);
	print_action(philo, 's', philo->start_time);
	sem_post(philo->sems->print);
	ft_usleep(philo, data->sleep_time);
	return (0);
}
