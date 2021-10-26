/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:20:55 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/26 11:44:15 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	std_exit(void);
int		safe_exit(void *ptr);

void	std_exit(void)
{
	printf("\nEXIT\n\n");
	exit(0);
}

int	safe_exit(void *load)
{
	t_program	*program;

	program = (t_program *)load;
	mlx_destroy_window(program->mlx, program->window.ptr);
	printf("\n(SAFE) EXIT\n\n");
	exit(0);
	return (0);
}
