/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:01:19 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/26 11:39:25 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_program	program;

	parseargs(argc, argv);
	program.env.moves = 0;
	program.map.ptr = getmap(&program, argv[1]);
	b_init(&program);
	draw(&program);
	status(&program);
	mlx_hook(program.window.ptr, 02, 0, keyp, &program);
	mlx_hook(program.window.ptr, 17, 0, safe_exit, &program);
	mlx_loop(program.mlx);
}
