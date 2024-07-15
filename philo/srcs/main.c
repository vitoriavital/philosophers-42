/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:10:49 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/15 10:10:32 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	clean_resources(t_monitor *monitor, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < monitor->n_philos)
	{
		action_mutex(DESTROY, &forks[i]);
		i++;
	}
	action_mutex(DESTROY, &monitor->dead_mutex);
	action_mutex(DESTROY, &monitor->write_mutex);
	action_mutex(DESTROY, &monitor->meal_mutex);
	free (forks);
	free (monitor->philosophers);
	free (monitor);
}

int	main(int argc, char **argv)
{
	t_monitor		*monitor;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	monitor = (t_monitor *)malloc(sizeof(t_monitor));
	check_params(argc, argv, monitor);
	philos = (t_philo *)malloc(sizeof(t_philo) * monitor->n_philos);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* monitor->n_philos);
	init_forks(forks, monitor->n_philos);
	initialize_data(monitor, philos, forks);
	monitor->philosophers = philos;
	start_cycle(monitor, forks);
	clean_resources(monitor, forks);
}
