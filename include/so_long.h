/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:02:23 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/25 13:56:30 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

//Header files
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "mlx.h"
# include "../gnl/get_next_line.h"

//Structs
typedef struct s_vector
{
	int	x;
	int	y;	
}			t_vector;

typedef struct s_env
{	
	void	*bg;
	void	*wall;
	void	*daemon;
	void	*player;
	void	*exit;
	int		moves;

}			t_env;

typedef struct s_map
{
	int			ptr;
	int			**wall;
	t_vector	exit;
	t_vector	size;
}			t_map;

typedef struct s_window
{
	void	*ptr;
	int		width;
	int		height;
	char	*name;
}			t_window;

typedef struct s_status
{
	int	pcount;
	int	ccount;
	int	ecount;
}			t_status;

typedef struct s_program
{
	void		*mlx;
	t_window	window;
	t_map		map;
	t_env		env;
	t_vector	position;
	t_status	status;
}			t_program;

//Functions
void	b_init(void *load);
int		impact(void *load, char dir, int next);
void	kill(void *load);
int		keyp(int keycode, void *load);
void	plmove(void *load, int *mov, char dir);
int		getmap(void *load, char *map);
void	msize(void *load, char *map);
int		countln(void *load, char *line, int lnum, int fd);
void	draw(void *load);
void	spr_type(void *load, char type, int x, int y);
void	set_cols(void *load);
void	std_exit(void);
int		safe_exit(void *load);
void	d_wall(void *load, int x, int y);
void	d_space(void *load, int x, int y);
void	d_player(void *load, int x, int y);
void	d_coin(void *load, int x, int y);
void	d_exit(void *load, int x, int y);
void	parseargs(int argc, char **file);
void	argsfail(char c, int pos);
void	mapfail(int raw, int col, int fd);
void	status(void *load);
void	countfail(void *load, char type);
void	resolution_fix(void *load);

#endif
