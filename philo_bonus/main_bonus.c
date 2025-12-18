/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/18 22:15:44 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

static void	cleanup_parent(t_data *data, t_sems *sems, pid_t *pids)
{
	if (data)
		free(data);
	if (pids)
		free(pids);
	if (sems)
	{
		sem_close_all(sems);
		sem_unlink_all();
		free(sems);
	}
}

static int	wait_all_or_death(t_data *data, pid_t *pids)
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
	return (EXIT_SATIATED);
}

static void	routine(t_data *data, t_sems *sems, int index)
{
	t_philo	*philo;

	philo = init_philo(data, index, sems);
	if (!philo)
		exit(EXIT_FAILURE);
	if (index % 2 == 0)
		ft_usleep(philo, 1);
	while (true)
	{
		if (fork_handle(philo, data))
			return ;
		if (eat_handle(philo, data))
			return ;
		if (sleep_handle(philo, data))
			return ;
		if (think_handle(philo, data))
			return ;
		if (philo->data->must_eat != -1 && philo->eat_count >= data->must_eat)
			exit(EXIT_SATIATED);
	}
	free(philo);
	exit(EXIT_SATIATED);
}

static void	kill_all(pid_t *pids, int ind)
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

int	main(int argc, char **argv)
{
	pid_t	*pids;
	t_sems	*sems;
	t_data	*data;
	int		i;

	if ((argc == 5 || argc == 6) && is_valid(argv))
	{
		data = init_data(argv);
		sems = init_semaphores(ft_atoi(argv[1]));
		pids = (pid_t *)malloc(sizeof(pid_t) * ft_atoi(argv[1]));
		if (!data || !sems || !pids)
			return (cleanup_parent(data, sems, pids), ft_error(6, 0));
		i = -1;
		while (++i < data->count)
		{
			pids[i] = fork();
			if (pids[i] < 0)
				return (kill_all(pids, i), 1);
			if (pids[i] == 0)
				routine(data, sems, i + 1);
		}
		wait_all_or_death(data, pids);
		cleanup_parent(data, sems, pids);
	}
	else
		return (ft_error(1, 0));
	return (0);
}
