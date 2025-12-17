/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/17 20:29:09 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>

# include <semaphore.h>
# include <fcntl.h>

# include <limits.h>
# include <sys/time.h>

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define SEM_FORKS		"/forks"
# define SEM_PRINT		"/print"
# define SEM_MEAL		"/meal"
# define SEM_STOP		"/stop"

# define EXIT_DEATH		1
# define EXIT_SATIATED	0

typedef struct s_sems
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*meal;
	sem_t	*stop;
}	t_sems;

/*philo struct*/
typedef struct s_data
{
	int			count;
	int			must_eat;
	long long	die_time;
	long long	eat_time;
	long long	sleep_time;
}	t_data;

/*shared data struct*/
typedef struct s_philo
{
	int			id;
	pid_t		pid;
	int			eat_count;
	long long	start_time;
	long long	last_meal;

	t_data		*data;
	t_sems		*sems;

	pthread_t	death_thread;
}	t_philo;

/*philo utils*/
bool		is_valid(char **argv);
void		print_action(t_philo *philo, char action, long long timestamp);
void		ft_error(int error_status, int opt_arg);
void		free_data(t_data **data);
void		ft_usleep(long long ms);

/*monitoring*/
// void			*monitoring_death(void *data);
// void			*eat_monitoring(void *arg);
// int			check_death(t_data *data);
// int			check_fullness(t_data *data);

/*init utils*/
// void		cast_str_data(t_data **data, char **argv);

/*init functions*/
t_data		*init_data(char **argv);
t_philo		*init_philo(t_data *data, int index, t_sems *sems);

/*timer function*/
long long	get_time_in_ms(void);
long		get_last_meal(t_philo *philo);

/*helper functions*/
int			ft_atoi(char *str);
int			ft_isdigit(char c);
int			ft_inset(char c, char *set);

/*philo's actions*/
int			think_handle(t_philo *philo, t_data *data);
int			forks_handle(t_philo *philo, t_data *data);
int			eat_handle(t_philo *philo, t_data *data);
int			sleep_handle(t_philo *philo, t_data *data);

/*philo actions utils*/
void		drop_forks(t_philo *philo);
int			try_pick_forks_evens(t_philo *philo, t_data *data);
int			try_pick_forks_odds(t_philo *philo, t_data *data);

#endif