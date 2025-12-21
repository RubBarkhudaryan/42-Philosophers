/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/21 19:16:05 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

int	main(int argc, char **argv)
{
	pid_t		*pids;
	t_sems		*sems;
	t_data		*data;
	int			i;

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
		wait_all_or_death(data, pids, data->start_time);
		return (cleanup_parent(data, sems, pids), 0);
	}
	return (ft_error(1, 0));
}
