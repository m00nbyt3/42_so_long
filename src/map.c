/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:19:31 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/26 11:38:17 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		getmap(void *load, char *map);
void	msize(void *load, char *map);
int		countln(void *load, char *line, int lnum, int fd);
void	draw(void *load);
void	spr_type(void *load, char type, int x, int y);

int	getmap(void *load, char *map)
{
	int	file;

	msize(load, map);
	file = open(map, O_RDONLY);
	return (file);
}

void	msize(void *load, char *map)
{
	t_program	*program;
	int			file;
	char		*line;
	int			err;

	program = (t_program *)load;
	file = open(map, O_RDONLY);
	line = get_next_line(file);
	if (!line)
		mapfail(0, -1, file);
	program->window.width = 0;
	program->window.height = 0;
	while (line)
	{
		program->window.height++;
		err = countln (load, line, program->window.height, file);
		free(line);
		line = NULL;
		line = get_next_line(file);
	}
	if (err)
		mapfail(program->window.height, -3, file);
	close (file);
	program->map.size.x = program->window.width;
	program->map.size.y = program->window.height;
}

int	countln(void *load, char *line, int lnum, int fd)
{
	t_program	*program;
	int			size;
	int			err;

	program = (t_program *)load;
	size = 0;
	err = 0;
	while (*line && *line != '\n')
	{
		if (*line != '1' && err == 0)
			err = 1;
		size++;
		line++;
	}
	if (program->window.width == 0 && size)
		program->window.width = size;
	else if (program->window.width != size || !size)
		mapfail(lnum, -2, fd);
	if (*(line - 1) != '1')
		mapfail(-lnum, size, fd);
	if (*(line - size) != '1')
		mapfail(-lnum, 1, fd);
	if (lnum == 1 && err == 1)
		mapfail(lnum, -3, fd);
	return (err);
}

void	draw(void *load)
{
	t_program	*program;
	t_vector	pos;
	char		*line;

	program = (t_program *)load;
	program->status.ccount = 0;
	pos.y = 0;
	line = get_next_line(program->map.ptr);
	set_cols(load);
	while (line)
	{
		pos.x = 0;
		while (*line)
		{
			spr_type(load, *line, pos.x, pos.y);
			line++;
			pos.x += 100;
		}
		pos.y += 100;
		line -= (pos.x / 100);
		free(line);
		line = NULL;
		line = get_next_line(program->map.ptr);
	}
	close (program->map.ptr);
}

void	spr_type(void *load, char type, int x, int y)
{
	t_program	*program;

	program = (t_program *)load;
	if (type == '1')
		d_wall(load, x, y);
	else if (type == '0')
		d_space(load, x, y);
	else if (type == 'P')
		d_player(load, x, y);
	else if (type == 'C')
		d_coin(load, x, y);
	else if (type == 'E')
		d_exit(load, x, y);
	else if (type != '\n' && type != '\0')
	{
		printf("\nERROR: Incorrect entity in map-> %c", type);
		printf(" (raw %d, column %d)\n", (y / 100) + 1, (x / 100) + 1);
		close (program->map.ptr);
		safe_exit(load);
	}
}
