/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:55:23 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/12/17 17:20:14 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

int ft_atoi(char *str)
{
	int i;
	int res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (sign == 1 && res > (INT_MAX - (str[i] - '0')) / 10)
			return (0);
		if (sign == -1 && res > (-(INT_MIN + (str[i] - '0'))) / 10)
			return (0);
		res = res * 10 + (str[i] - '0');
		++i;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (0);
	return (res * sign);
}

int ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int ft_inset(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}
