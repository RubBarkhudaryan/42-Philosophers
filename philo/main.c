/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/06/05 21:28:14 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*routine(void *arg)
{}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc == 5 || argc == 6) && is_valid(argv))
	{
		
	}
	else if (argc < 5)
		ft_error(1, 0);
	return (0);
}
