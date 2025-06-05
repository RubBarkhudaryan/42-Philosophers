/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/05 21:20:57 by rbarkhud         ###   ########.fr       */
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
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

/*philo struct*/
struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	t_data			*data;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
};

struct s_data
{
	int				count;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
};

/*philo utils*/
int		is_valid(char **argv);
void	print_action(int philo, char action, long long timestamp);
void	ft_error(int error_status, int opt_arg);

/*init functions*/
pthread_mutex_t	*init_forks(int count);
pthread_t		*init_threads(int count);
t_data			*init_data(char **argv);

/*libft functions*/
int		ft_atoi(char *str);
int		ft_isdigit(char c);
int		ft_inset(char c, char *set);

#endif