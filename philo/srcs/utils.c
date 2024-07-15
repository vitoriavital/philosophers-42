/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:17 by mavitori          #+#    #+#             */
/*   Updated: 2024/07/15 10:14:25 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

static void	check_signal(const char *nptr, int *i, char *type,
		t_monitor *monitor)
{
	if (nptr[*i] == '-')
	{
		printf("Invalid %s: %s\n", type, &nptr[*i]);
		free(monitor);
		exit(1);
	}
	else if (nptr[*i] == '+')
		(*i)++;
}

int	ft_atoi(const char *nptr, char *type, t_monitor *monitor)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (ft_is_space(nptr[i]))
		i++;
	check_signal(nptr, &i, type, monitor);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0' || num > 2147483647)
	{
		printf("Invalid %s: %s\n", type, &nptr[0]);
		free(monitor);
		exit(1);
	}
	return (num);
}

long long	get_current_time_ms(void)
{
	struct timeval	tv;
	long long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (time_ms);
}

void	print_message(char type, t_philo *philo)
{
	long long	time_ms;

	action_mutex(LOCK, philo->write_mutex);
	time_ms = get_current_time_ms();
	time_ms = time_ms - philo->start;
	if (get_value(philo->dead_mutex, philo->is_alive) == FALSE)
	{
		action_mutex(UNLOCK, philo->write_mutex);
		return ;
	}
	if (type == 'F')
		printf("%s%lld %d has a taken fork \n", PINK, time_ms, philo->philo_id);
	else if (type == 'E')
		printf("%s%lld %d is eating\n", YELLOW, time_ms, philo->philo_id);
	else if (type == 'S')
		printf("%s%lld %d is sleeping\n", BLUE, time_ms, philo->philo_id);
	else if (type == 'T')
		printf("%s%lld %d is thinking\n", GREEN, time_ms, philo->philo_id);
	else if (type == 'D')
		printf("%s%lld %d died \n", RED, time_ms, philo->philo_id);
	action_mutex(UNLOCK, philo->write_mutex);
}
