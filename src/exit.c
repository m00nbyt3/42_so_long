/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:20:55 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/20 15:34:28 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	int			tmp;

	program = (t_program *)load;
	tmp = program->map.size.y - 1;
	while (tmp >= 0)
	{
		free(program->map.wall[tmp]);
		tmp--;
	}
	free(program->map.wall);
	mlx_destroy_window(program->mlx, program->window.ptr);
	printf("\n(SAFE) EXIT\n\n");
	exit(0);
	return (0);
}
