/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/16 18:06:11 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
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
	long long		last_meal;
	t_data			*data;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	eat_mutex;
};

/*shared data struct*/
struct s_data
{
	int				count;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	int				dead;
	int				full;
	long long		start_time;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_t		monitoring;
	pthread_t		eat_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
};

/*philo utils*/
bool			is_valid(char **argv);
void			print_action(t_philo *philo, char action, long long timestamp);
void			ft_error(int error_status, int opt_arg);
void			free_data(t_data **data);
void			ft_usleep(long long ms);

/*init utils*/
void			cast_str_data(t_data **data, char **argv);

/*init functions*/
pthread_mutex_t	*init_forks(int count);
pthread_t		*init_threads(int count);
t_data			*init_data(char **argv);
void			init_philo(t_philo *philo, t_data *data, int index);

/*monitoring*/
void			*monitoring_death(void *data);
void			*eat_monitoring(void *arg);
int				check_death(t_data *data);
int				check_fullness(t_data *data);

/*timer function*/
long long		get_time_in_ms(void);
long			get_last_meal(t_philo *philo);

/*helper functions*/
int				ft_atoi(char *str);
int				ft_isdigit(char c);
int				ft_inset(char c, char *set);

/*philo's actions*/
int				think_handle(t_philo *philo, t_data *data);
int				forks_handle(t_philo *philo, t_data *data);
int				eat_handle(t_philo *philo, t_data *data);
int				sleep_handle(t_philo *philo, t_data *data);

/*philo actions utils*/
void			drop_forks(t_philo *philo);
int				try_pick_forks_evens(t_philo *philo, t_data *data);
int				try_pick_forks_odds(t_philo *philo, t_data *data);

#endif