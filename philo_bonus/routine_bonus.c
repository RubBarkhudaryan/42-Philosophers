/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:06:00 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/21 19:32:44 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

static void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		check_death(philo);
		usleep(1000);
	}
	return (NULL);
}

int	check_fullness(t_philo *philo)
{
	sem_wait(philo->sems->meal);
	if (philo->data->must_eat != -1
		&& philo->eat_count >= philo->data->must_eat)
	{
		sem_post(philo->sems->meal);
		exit(EXIT_SATIATED);
	}
	sem_post(philo->sems->meal);
	return (0);
}

void	kill_all(pid_t *pids, int ind)
{
	int	i;

	i = 0;
	while (i < ind)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGKILL);
		++i;
	}
}

int	wait_all_or_death(t_data *data, pid_t *pids, long long start)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < data->count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			return (1);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_DEATH)
		{
			kill_all(pids, data->count);
			return (EXIT_DEATH);
		}
		++i;
	}
	print_action(NULL, 'q', start);
	return (EXIT_SATIATED);
}

void	routine(t_data *data, t_sems *sems, int index)
{
	t_philo	*philo;

	philo = init_philo(data, index, sems);
	if (!philo)
		exit(EXIT_FAILURE);
	if (pthread_create(&philo->monitor, NULL, death_monitor, philo) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(philo->monitor);
	if (index % 2 == 0)
		ft_usleep(philo, 1);
	while (true)
	{
		if (philo->data->must_eat != -1)
			check_fullness(philo);
		if (eat_handle(philo, data))
			break ;
		if (sleep_handle(philo, data))
			break ;
		if (think_handle(philo))
			break ;
	}
	free(philo);
	exit(EXIT_SATIATED);
}
