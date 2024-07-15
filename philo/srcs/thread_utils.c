/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:07:34 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/04 13:37:57 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	action_mutex(t_types type, pthread_mutex_t *mutex)
{
	if (type == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (type == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (type == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (type == DESTROY)
		return (pthread_mutex_destroy(mutex));
	return (0);
}

int	get_value(pthread_mutex_t *mutex, int *value)
{
	int	current_value;

	action_mutex(LOCK, mutex);
	current_value = *value;
	action_mutex(UNLOCK, mutex);
	return (current_value);
}

void	set_value(pthread_mutex_t *mutex, int *value, int new_value,
		int increment)
{
	action_mutex(LOCK, mutex);
	if (increment == TRUE)
		(*value)++;
	else
		*value = new_value;
	action_mutex(UNLOCK, mutex);
}

long long	get_time_value(pthread_mutex_t *mutex, long long *value)
{
	long long	current_value;

	action_mutex(LOCK, mutex);
	current_value = *value;
	action_mutex(UNLOCK, mutex);
	return (current_value);
}

void	set_time_value(pthread_mutex_t *mutex, long long *value,
		long long new_value)
{
	action_mutex(LOCK, mutex);
	*value = new_value;
	action_mutex(UNLOCK, mutex);
}
