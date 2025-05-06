/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:16:58 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/05/06 21:08:41 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

static int	contains_symbols(char **argv)
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
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

void	ft_error(int error_status, int opt_arg)
{
	if (error_status == 1)
		printf("Error: Invalid arguments count\n");
	else if (error_status == 2)
		printf("Error: Philos count out of range (1 - 1000): %d\n", opt_arg);
	else if (error_status == 3)
		printf("Error: Invalid character found\n");
	else if (error_status == 4)
		printf("Error: Argument out of range (1 - %d)\n", INT_MAX);
}

int	is_valid(char **argv)
{
	int	i;
	int	arg;
	int	philo_count;

	philo_count = ft_atoi(argv[1]);
	if (philo_count <= 0 || philo_count > 1000)
		return (ft_error(2, philo_count), 0);
	if (contains_symbols(argv))
		return (ft_error(3, 0), 0);
	i = 2;
	while (argv[i])
	{
		arg = ft_atoi(argv[i]);
		if (arg < 1 || arg > INT_MAX)
			return (ft_error(4, 0), 0);
		++i;
	}
	return (1);
}
