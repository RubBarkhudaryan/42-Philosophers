/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/04 19:24:12 by rbarkhud         ###   ########.fr       */
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
	int				id;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	pthread_t		philo;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
}	t_philo;

/*philo utils*/
int		is_valid(char **argv);

void	print_action(int philo, char action, long long timestamp);
void	ft_error(int error_status, int opt_arg);
void	init_forks(t_philo **philos, int count);
void	*routine(void *arg);

t_philo	*init_philos(char **argv);

/*philo actions*/
int		ft_think(t_philo *philo);
int		ft_forks(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);


/*libft functions*/
int		ft_atoi(char *str);
int		ft_isdigit(char c);
int		ft_inset(char c, char *set);

#endif