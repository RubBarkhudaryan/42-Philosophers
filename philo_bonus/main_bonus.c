/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:14:03 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/05/06 21:08:18 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

int	main(int argc, char **argv)
{
	// t_thread	thread;

	if (argc == 5 || argc == 6)
	{
		if (is_valid(argv))
		{
			printf("valid\n");
		}
	}
	else
		ft_error(1, 0);
	return (0);
}
