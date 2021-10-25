/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preload.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:12:01 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/25 10:34:49 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	b_init(void *load);
int		keyp(int keycode, void *load);
void	resolution_fix(void *load);

void	b_init(void *load)
{
	t_program	*program;

	program = (t_program *)load;
	program->mlx = mlx_init();
	program->window.width *= 100;
	program->window.height *= 100;
	if (program->window.height > 1400 || program->window.width > 2600)
	{
		printf("\nERROR: The map is so big for this screen (Max 27x14)\n");
		std_exit();
	}
	program->position.x = 0;
	program->position.y = 0;
	program->window.ptr = mlx_new_window(program->mlx, program->window.width, \
		program->window.height, "42 Dungeons");
	program->env.bg = mlx_xpm_file_to_image(program->mlx, \
		"img/bg.xpm", &(program->window.width), &(program->window.height));
	program->env.player = mlx_xpm_file_to_image(program->mlx, \
		"img/knight.xpm", &(program->window.width), &(program->window.height));
	program->env.daemon = mlx_xpm_file_to_image(program->mlx, \
		"img/daemon.xpm", &(program->window.width), &(program->window.height));
	program->env.wall = mlx_xpm_file_to_image(program->mlx, \
		"img/wall.xpm", &(program->window.width), &(program->window.height));
	program->env.exit = mlx_xpm_file_to_image(program->mlx, \
		"img/exit.xpm", &(program->window.width), &(program->window.height));
}

int	keyp(int keycode, void *load)
{
	t_program	*program;
	t_vector	subs;

	program = (t_program *)load;
	subs.x = 0;
	subs.y = 0;
	if (keycode == 53)
		safe_exit(program);
	else if (keycode == 2 && !impact(load, 'r', 1))
		plmove(&subs, &(program->position.x), 'r');
	else if (keycode == 0 && !impact(load, 'l', -1))
		plmove(&subs, &(program->position.x), 'l');
	else if (keycode == 1 && !impact(load, 'd', 1))
		plmove(&subs, &(program->position.y), 'd');
	else if (keycode == 13 && !impact(load, 'u', -1))
		plmove(&subs, &(program->position.y), 'u');
	else
		return (0);
	kill(load);
	printf("MOVES: %d\n", ++program->env.moves);
	mlx_put_image_to_window(program->mlx, program->window.ptr, program->env.bg, \
		program->position.x + subs.x, program->position.y + subs.y);
	mlx_put_image_to_window(program->mlx, program->window.ptr, \
		program->env.player, program->position.x, program->position.y);
	return (0);
}
