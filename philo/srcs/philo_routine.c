/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:47:41 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/15 10:07:06 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	is_philo_alive(t_philo *philo)
{
	int	is_alive;

	is_alive = get_value(philo->dead_mutex, philo->is_alive);
	if (is_alive == FALSE)
		return (FALSE);
	return (TRUE);
}

static void	ft_sleep(t_philo *philo)
{
	if (get_value(philo->dead_mutex, philo->is_alive) == FALSE)
		return ;
	print_message('S', philo);
	usleep(philo->time_to_sleep * 1000);
}

static void	ft_eat(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *last)
{
	action_mutex(LOCK, first);
	print_message('F', philo);
	if (philo->n_philos > 1)
	{
		action_mutex(LOCK, last);
		print_message('F', philo);
		set_value(philo->meal_mutex, &philo->is_eating, TRUE, FALSE);
		print_message('E', philo);
		set_time_value(philo->meal_mutex, &philo->last_meal,
			get_current_time_ms());
		set_value(philo->meal_mutex, &philo->count_meals, TRUE, TRUE);
		usleep(philo->time_to_eat * 1000);
		set_value(philo->meal_mutex, &philo->is_eating, FALSE, FALSE);
		pthread_mutex_unlock(last);
	}
	if (philo->n_philos == 1)
		usleep(philo->time_to_die * 1000);
	pthread_mutex_unlock(first);
}

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (1)
	{
		if (get_value(philo->write_mutex, philo->all_ready) == TRUE)
			break ;
	}
	while (is_philo_alive(philo) == TRUE)
	{
		usleep(1000);
		if (philo->philo_id % 2 == 1)
			ft_eat(philo, philo->left_fork, philo->right_fork);
		else
			ft_eat(philo, philo->right_fork, philo->left_fork);
		ft_sleep(philo);
		if (get_value(philo->dead_mutex, philo->is_alive) == TRUE)
			print_message('T', philo);
	}
	return (philosopher);
}
