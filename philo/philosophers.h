/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/05/06 21:09:26 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_thread
{
	int	t;
}	t_thread;

/*philo utils*/
int		is_valid(char **argv);
void	ft_error(int error_status, int opt_arg);

/*libft functions*/
int		ft_atoi(char *str);
int		ft_isdigit(char c);
int		ft_inset(char c, char *set);

#endif