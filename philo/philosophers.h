/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/05/14 18:41:57 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>

/*philo struct*/
typedef struct s_philo
{
	int			id;
	int			die;
	int			eat;
	int			sleep;
	int			must_eat;
	pthread_t	philo;
}	t_philo;

/*philo utils*/
int		is_valid(char **argv);
void	print_action(int philo, char action, long long timestamp);
void	ft_error(int error_status, int opt_arg);

/*libft functions*/
int		ft_atoi(char *str);
int		ft_isdigit(char c);
int		ft_inset(char c, char *set);

#endif