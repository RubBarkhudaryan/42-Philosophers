/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:16:58 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/11 17:56:39 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

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

	philo_count = ft_atoi(argv[1]);
	if (philo_count < 1 || philo_count > 200)
		return (ft_error(2, philo_count), false);
	if (contains_symbols(argv))
		return (ft_error(3, 0), false);
	i = 2;
	while (argv[i])
	{
		arg = ft_atoi(argv[i]);
		if (arg < 1 || arg > INT_MAX)
			return (ft_error(4, 0), false);
		++i;
	}
	return (true);
}

void	ft_error(int error_status, int opt_arg)
{
	if (error_status == 1)
		printf("Error: Invalid arguments count\n");
	else if (error_status == 2)
		printf("Error: Philos count out of range (1 - 200): %d\n", opt_arg);
	else if (error_status == 3)
		printf("Error: Invalid character found\n");
	else if (error_status == 4)
		printf("Error: Argument out of range (1 - %d)\n", INT_MAX);
	else if (error_status == 5)
		printf("Error: Philos initialization failed\n");
}

void	print_action(t_philo *philo, char action, long long timestamp)
{
	long long	curr_time;
	t_data		*data;

	data = philo->data;
	curr_time = get_time_in_ms();
	pthread_mutex_lock(&data->print_mutex);
	if (action == 'f')
		printf("%lld %d has taken a fork\n", curr_time - timestamp, philo->id);
	else if (action == 'e')
		printf("%lld %d is eating\n", curr_time - timestamp, philo->id);
	else if (action == 's')
		printf("%lld %d is sleeping\n", curr_time - timestamp, philo->id);
	else if (action == 't')
		printf("%lld %d is thinking\n", curr_time - timestamp, philo->id);
	else if (action == 'd')
		printf("%lld %d died\n", curr_time - timestamp, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}
