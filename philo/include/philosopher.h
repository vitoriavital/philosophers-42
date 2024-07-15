/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:33:55 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/15 10:10:51 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define PINK "\x1b[38;5;213m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"

typedef enum e_condition	t_condition;
enum						e_condition
{
	FALSE = 0,
	TRUE = 1
};

typedef enum e_types		t_types;
enum						e_types
{
	LOCK = 10,
	UNLOCK,
	INIT,
	DESTROY,
};

typedef struct s_philo
{
	int						philo_id;
	int						n_philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						n_meals;
	int						is_eating;
	int						*is_alive;
	int						count_meals;
	long long				start;
	long long				last_meal;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*write_mutex;
	pthread_mutex_t			*dead_mutex;
	pthread_mutex_t			*meal_mutex;
	pthread_t				thread_id;
	int						*all_ready;
}							t_philo;

typedef struct s_monitor
{
	int						is_alive;
	t_philo					*philosophers;
	int						n_philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						n_meals;
	pthread_mutex_t			dead_mutex;
	pthread_mutex_t			meal_mutex;
	pthread_mutex_t			write_mutex;
	int						all_ready;
}							t_monitor;

// UTILS //
int							ft_atoi(const char *nptr, char *type,
								t_monitor *monitor);
void						print_message(char type, t_philo *philo);
long long					get_current_time_ms(void);

// MAIN //
void						clean_resources(t_monitor *monitor,
								pthread_mutex_t *forks);

// INITIALIZE //
void						check_params(int argc, char **argv,
								t_monitor *monitor);
void						initialize_data(t_monitor *monitor, t_philo *philos,
								pthread_mutex_t *forks);
void						init_forks(pthread_mutex_t *forks, int n_forks);

// DINNER CYCLE //
int							start_cycle(t_monitor *monitor,
								pthread_mutex_t *forks);

// PHILO ROUTINE //
void						*philo_routine(void *philosophers);

// MONITOR ROUTINE //
void						*monitor_routine(void *philosophers);

// THREAD UTILS //
int							action_mutex(t_types type, pthread_mutex_t *mutex);
int							get_value(pthread_mutex_t *mutex, int *value);
long long					get_time_value(pthread_mutex_t *mutex,
								long long *value);
void						set_value(pthread_mutex_t *mutex, int *value,
								int new_value, int increment);
void						set_time_value(pthread_mutex_t *mutex,
								long long *value, long long new_value);

#endif
