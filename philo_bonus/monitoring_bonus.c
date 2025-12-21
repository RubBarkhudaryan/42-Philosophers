/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:11:31 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/21 19:21:38 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

int	check_death(t_philo *philo)
{
	long long	last;
	long long	now;

	now = get_time_in_ms();
	sem_wait(philo->sems->meal);
	last = philo->last_meal;
	sem_post(philo->sems->meal);
	if (now - last >= philo->data->die_time)
	{
		sem_wait(philo->sems->print);
		print_action(philo, 'd', philo->start_time);
		exit(EXIT_DEATH);
	}
	return (0);
}
