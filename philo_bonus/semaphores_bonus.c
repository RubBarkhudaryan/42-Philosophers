/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:14:11 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/18 22:17:47 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

void	sem_unlink_all(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_STOP);
}

void	sem_close_all(t_sems *sems)
{
	if (!sems)
		return ;
	if (sems->forks && sems->forks != SEM_FAILED)
		sem_close(sems->forks);
	if (sems->meal && sems->meal != SEM_FAILED)
		sem_close(sems->meal);
	if (sems->print && sems->print != SEM_FAILED)
		sem_close(sems->print);
	if (sems->stop && sems->stop != SEM_FAILED)
		sem_close(sems->stop);
}
