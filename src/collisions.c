/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:16:18 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/19 13:14:27 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		impact(void *load, char dir, int next);
void	set_cols(void *load);

int	impact(void *load, char dir, int next)
{
	t_program	*program;
	t_vector	cpos;

	program = (t_program *)load;
	cpos.x = program->position.x / 100;
	cpos.y = program->position.y / 100;
	if (dir == 'r' || dir == 'l')
	{
		if (program->map.wall[cpos.y][cpos.x + next] == 1)
			return (1);
	}
	if (dir == 'd' || dir == 'u')
	{
		if (program->map.wall[cpos.y + next][cpos.x] == 1)
			return (1);
	}
	return (0);
}

void	set_cols(void *load)
{
	t_program	*program;
	int			tmp;

	program = (t_program *)load;
	program->map.wall = malloc(program->map.size.y * sizeof(int *));
	tmp = program->map.size.y - 1;
	while (tmp >= 0)
	{
		program->map.wall[tmp] = malloc(program->map.size.x * sizeof(int));
		tmp--;
	}
}
