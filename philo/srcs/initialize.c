/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:14:20 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/14 17:23:37 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	check_params(int argc, char **argv, t_monitor *monitor)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		printf("Ex: ./philo P D E S [M]\n");
		printf("P: Number of philosophers\n");
		printf("D: Time to die\n");
		printf("E: Time to eat\n");
		printf("S: Time to sleep\n");
		printf("M: Number of meals\n");
		free (monitor);
		exit(1);
	}
	monitor->n_philos = ft_atoi(argv[1], "number of philosophers", monitor);
	monitor->time_to_die = ft_atoi(argv[2], "time to die", monitor);
	monitor->time_to_eat = ft_atoi(argv[3], "time to eat", monitor);
	monitor->time_to_sleep = ft_atoi(argv[4], "time to sleep", monitor);
	monitor->all_ready = FALSE;
	if (argc == 6)
		monitor->n_meals = ft_atoi(argv[5], "number of meals", monitor);
	else
		monitor->n_meals = -1;
	monitor->is_alive = TRUE;
	action_mutex(INIT, &monitor->dead_mutex);
	action_mutex(INIT, &monitor->meal_mutex);
	action_mutex(INIT, &monitor->write_mutex);
}

void	init_forks(pthread_mutex_t *forks, int n_forks)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		action_mutex(INIT, &forks[i]);
		i++;
	}
}

static void	init_philo(t_philo *philos, t_monitor *monitor, int i)
{
	philos[i].philo_id = i + 1;
	philos[i].n_philos = monitor->n_philos;
	philos[i].time_to_die = monitor->time_to_die;
	philos[i].time_to_eat = monitor->time_to_eat;
	philos[i].time_to_sleep = monitor->time_to_sleep;
	philos[i].n_meals = monitor->n_meals;
	philos[i].is_eating = FALSE;
	philos[i].is_alive = &monitor->is_alive;
	philos[i].all_ready = &monitor->all_ready;
	philos[i].count_meals = 0;
	philos[i].start = get_current_time_ms();
	philos[i].last_meal = philos[i].start;
	philos[i].write_mutex = &monitor->write_mutex;
	philos[i].dead_mutex = &monitor->dead_mutex;
	philos[i].meal_mutex = &monitor->meal_mutex;
}

void	initialize_data(t_monitor *monitor, t_philo *philos,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < monitor->n_philos)
	{
		init_philo(philos, monitor, i);
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].n_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}
