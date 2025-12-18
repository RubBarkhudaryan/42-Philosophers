/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:16:58 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/18 21:19:41 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

static bool	contains_symbols(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && !ft_inset(argv[i][j], " +-"))
				return (true);
			++j;
		}
		++i;
	}
	return (false);
}

bool	is_valid(char **argv)
{
	int	i;
	int	arg;
	int	philo_count;

	if (contains_symbols(argv))
		return (!ft_error(3, 0));
	philo_count = ft_atoi(argv[1]);
	if (philo_count < 1 || philo_count > 200)
		return (!ft_error(2, philo_count));
	i = 2;
	while (argv[i])
	{
		arg = ft_atoi(argv[i]);
		if (arg < 1 || arg > INT_MAX)
			return (!ft_error(4, 0));
		++i;
	}
	return (true);
}

int	ft_error(int error_status, int opt_arg)
{
	if (error_status == 1)
		printf("Error: Invalid arguments count.\n");
	else if (error_status == 2)
		printf("Error: Philos count out of range (1 - 200): %d\n", opt_arg);
	else if (error_status == 3)
		printf("Error: Invalid character found.\n");
	else if (error_status == 4)
		printf("Error: Argument out of range (1 - %d).\n", INT_MAX);
	else if (error_status == 5)
		printf("Error: Philos initialization failed.\n");
	else if (error_status == 6)
		printf("Error: Malloc failure.\n");
	return (1);
}
