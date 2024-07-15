/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:48:19 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/15 10:06:41 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	check_philo_life(t_philo *philo)
{
	long long	last_meal;
	int			is_eating;

	last_meal = get_time_value(philo->meal_mutex, &philo->last_meal);
	is_eating = get_value(philo->meal_mutex, &philo->is_eating);
	if ((get_current_time_ms() - last_meal) > (philo->time_to_die)
		&& is_eating == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	all_alive(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].n_philos)
	{
		if (check_philo_life(&philos[i]) == FALSE)
		{
			print_message('D', &philos[i]);
			set_value(philos[i].dead_mutex, philos[i].is_alive, FALSE, FALSE);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int	all_full(t_philo *philos)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	if (philos[i].n_meals == -1)
		return (FALSE);
	while (i < philos[0].n_philos)
	{
		if (get_value(philos[i].meal_mutex,
				&philos[i].count_meals) >= philos[i].n_meals)
			done++;
		i++;
	}
	if (done == philos[0].n_philos && philos[0].n_philos > 0)
	{
		set_value(philos[0].dead_mutex, philos[0].is_alive, FALSE, FALSE);
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor_routine(void *philosophers)
{
	t_philo	*philos;

	philos = (t_philo *)philosophers;
	while (1)
	{
		if (get_value(philos[0].write_mutex, philos[0].all_ready) == TRUE)
			break ;
	}
	while (1)
	{
		if (all_alive(philos) == FALSE || all_full(philos) == TRUE)
			break ;
	}
	return (philosophers);
}
