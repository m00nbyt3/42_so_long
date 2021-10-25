/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:18:00 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/20 15:21:42 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	plmove(void *load, int *mov, char dir);
void	kill(void *load);

void	plmove(void *load, int *mov, char dir)
{
	t_vector	*subs;

	subs = (t_vector *)load;
	if (dir == 'r' || dir == 'd')
	{
		if (dir == 'r')
			subs->x -= 100;
		else
			subs->y -= 100;
		*mov = *mov + 100;
	}
	else if (dir == 'l' || dir == 'u')
	{
		if (dir == 'l')
			subs->x += 100;
		else
			subs->y += 100;
		*mov = *mov - 100;
	}
}

void	kill(void *load)
{
	t_program	*program;
	t_vector	cpos;
	t_vector	exit;

	program = (t_program *)load;
	cpos.x = program->position.x / 100;
	cpos.y = program->position.y / 100;
	exit.x = program->map.exit.x;
	exit.y = program->map.exit.y;
	if (program->map.wall[cpos.y][cpos.x] == 2)
	{
		program->status.ccount--;
		program->map.wall[cpos.y][cpos.x] = 0;
	}
	if (!program->status.ccount)
		program->map.wall[exit.y][exit.x] = 0;
	if (program->map.wall[exit.y][exit.x] == 0)
	{
		if (cpos.x == exit.x && cpos.y == exit.y)
		{
			printf("MOVES: %d\n", ++program->env.moves);
			safe_exit(load);
		}
	}
}
