/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:47:27 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/20 13:36:37 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	d_wall(void *load, int x, int y);
void	d_space(void *load, int x, int y);
void	d_player(void *load, int x, int y);
void	d_coin(void *load, int x, int y);
void	d_exit(void *load, int x, int y);

void	d_wall(void *load, int x, int y)
{
	t_program	*program;

	program = (t_program *)load;
	program->map.wall[y / 100][x / 100] = 1;
	mlx_put_image_to_window(program->mlx, program->window.ptr, \
		program->env.wall, x, y);
}

void	d_space(void *load, int x, int y)
{
	t_program	*program;

	program = (t_program *)load;
	program->map.wall[y / 100][x / 100] = 0;
}

void	d_player(void *load, int x, int y)
{
	t_program	*program;

	program = (t_program *)load;
	program->status.pcount++;
	program->map.wall[y / 100][x / 100] = 0;
	mlx_put_image_to_window(program->mlx, program->window.ptr, \
		program->env.player, x, y);
	program->position.x = x;
	program->position.y = y;
}

void	d_coin(void *load, int x, int y)
{
	t_program	*program;

	program = (t_program *)load;
	program->status.ccount++;
	program->map.wall[y / 100][x / 100] = 2;
	mlx_put_image_to_window(program->mlx, program->window.ptr, \
		program->env.daemon, x, y);
}

void	d_exit(void *load, int x, int y)
{
	t_program	*program;

	program = (t_program *)load;
	program->status.ecount++;
	program->map.wall[y / 100][x / 100] = 1;
	mlx_put_image_to_window(program->mlx, program->window.ptr, \
		program->env.exit, x, y);
	program->map.exit.x = x / 100;
	program->map.exit.y = y / 100;
}
