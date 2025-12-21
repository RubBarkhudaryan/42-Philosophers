/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/21 19:26:20 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H

# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
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
# define SEM_TAKE		"/take"

# define EXIT_DEATH		1
# define EXIT_SATIATED	0

typedef struct s_sems
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*meal;
	sem_t	*stop;
	sem_t	*take;
}	t_sems;

/*philo struct*/
typedef struct s_data
{
	int			count;
	int			must_eat;
	long long	die_time;
	long long	eat_time;
	long long	sleep_time;
	long long	start_time;
}	t_data;

/*shared data struct*/
typedef struct s_philo
{
	int			id;
	int			eat_count;
	long long	start_time;
	long long	last_meal;

	t_data		*data;
	t_sems		*sems;
	pthread_t	monitor;
}	t_philo;

/*philo utils*/
bool		is_valid(char **argv);
void		print_action(t_philo *philo, char action, long long timestamp);
int			ft_error(int error_status, int opt_arg);
void		ft_usleep(t_philo *philo, long long ms);

/*semaphores*/
void		sem_unlink_all(void);
void		sem_close_all(t_sems *sems);

/*init functions*/
t_data		*init_data(char **argv);
t_sems		*init_semaphores(int count);
t_philo		*init_philo(t_data *data, int index, t_sems *sems);

/*checkers*/
int			check_death(t_philo *philo);
int			check_fullness(t_philo *philo);

/*timer function*/
long long	get_time_in_ms(void);

/*helper functions*/
int			ft_atoi(char *str);
int			ft_isdigit(char c);
int			ft_inset(char c, char *set);

/*philo's actions*/
int			think_handle(t_philo *philo);
int			eat_handle(t_philo *philo, t_data *data);
int			sleep_handle(t_philo *philo, t_data *data);

/*main utils*/
void		cleanup_parent(t_data *data, t_sems *sems, pid_t *pids);
int			wait_all_or_death(t_data *data, pid_t *pids, long long start);
void		routine(t_data *data, t_sems *sems, int index);
void		kill_all(pid_t *pids, int ind);

#endif