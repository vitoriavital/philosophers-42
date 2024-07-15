/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:07:34 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/14 16:42:44 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	join_all(t_monitor *monitor, pthread_t supervisor,
		pthread_mutex_t *forks)
{
	int	i;

	set_value(&monitor->write_mutex, &monitor->all_ready, TRUE, FALSE);
	if (pthread_join(supervisor, NULL) != 0)
	{
		printf("Error joining monitor thread\n");
		clean_resources(monitor, forks);
		return (1);
	}
	i = 0;
	while (i < monitor->n_philos)
	{
		if (pthread_join(monitor->philosophers[i].thread_id, NULL) != 0)
		{
			printf("Error joining philosopher thread\n");
			clean_resources(monitor, forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_cycle(t_monitor *monitor, pthread_mutex_t *forks)
{
	pthread_t	supervisor;
	int			i;

	i = 0;
	if (monitor->n_meals == 0)
		return (0);
	if (pthread_create(&supervisor, NULL, &monitor_routine,
			monitor->philosophers) != 0)
	{
		printf("Error creating monitor thread\n");
		clean_resources(monitor, forks);
		return (1);
	}
	while (i < monitor->n_philos)
	{
		if (pthread_create(&monitor->philosophers[i].thread_id, NULL,
				&philo_routine, &monitor->philosophers[i]) != 0)
		{
			printf("Error creating philosopher thread\n");
			clean_resources(monitor, forks);
			return (1);
		}
		i++;
	}
	return (join_all(monitor, supervisor, forks));
}
