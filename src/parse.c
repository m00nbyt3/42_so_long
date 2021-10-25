/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:24:44 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/20 17:29:16 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	parseargs(int argc, char **file);
void	argsfail(char c, int pos);
void	mapfail(int raw, int col, int fd);
void	status(void *load);
void	countfail(void *load, char type);

void	parseargs(int argc, char **file)
{
	int	len;
	int	i;

	if (argc < 2)
	{
		printf("\nERROR: '.ber' map not specified\n");
		std_exit();
	}
	else if (argc > 2)
	{
		printf("\nERROR: Too many args\n");
		std_exit();
	}
	len = 0;
	while (file[1][len])
		len++;
	i = 0;
	while (++i <= 4)
		argsfail(file[1][--len], i);
}

void	argsfail(char c, int pos)
{
	int	err;

	err = 0;
	if (pos == 1)
	{
		if (c != 'r')
			err++;
	}
	else if (pos == 2)
	{
		if (c != 'e')
			err++;
	}
	else if (pos == 3)
	{
		if (c != 'b')
			err++;
	}
	else if (c != '.')
		err++;
	if (err)
	{
		printf("\nERROR: Incorrect map extension (not '.ber')\n");
		std_exit();
	}
}

void	mapfail(int raw, int col, int fd)
{
	if (fd < 0)
		printf("\nERROR: Unable to open the map \n");
	else if (col == -1)
		printf("\nERROR: Map is empty\n");
	else if (col == -2)
		printf("\nERROR: Wrong map format in line %d\n", raw);
	else if (col == -3)
	{
		if (raw == 1)
			printf("\nERROR: Wall missing in first raw (1st)\n");
		else
			printf("\nERROR: Wall missing in last raw (%dth)\n", raw);
	}
	if (raw < 0)
		printf("\nERROR: Wall missing (raw %d, column %d)\n", -raw, col);
	close (fd);
	std_exit();
}

void	status(void *load)
{
	t_program	*program;
	int			exit;

	program = (t_program *)load;
	exit = 0;
	if (program->status.pcount != 1)
	{
		countfail(load, 'p');
		exit++;
	}
	if (!program->status.ccount)
	{
		countfail(load, 'c');
		exit++;
	}
	if (program->status.ecount != 1)
	{
		countfail(load, 'e');
		exit++;
	}
	if (exit)
		safe_exit(load);
}

void	countfail(void *load, char type)
{
	t_program	*program;

	program = (t_program *)load;
	if (type == 'p')
	{
		if (!program->status.pcount)
			printf("\nERROR: Player not found! Add it on the '.ber' map. (P)\n");
		else
			printf("\nERROR: More than one player on the map! (P)\n");
	}
	else if (type == 'c')
		printf("\nERROR: Collectible not found! Add it on the '.ber' map. (C)\n");
	else if (type == 'e')
	{
		if (!program->status.ecount)
			printf("\nERROR: Exit not found! Add it on the '.ber' map. (E)\n");
		else
			printf("\nERROR: More than one exit on the map! (E)\n");
	}
}
