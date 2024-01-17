/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:14:39 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/04 09:19:20 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

int	put_to_screen(t_list **e_list)
{
	t_scData		scrn;

	scrn.e_list_displayed = e_list;
	scrn.mlx = mlx_init();
	scrn.win = mlx_new_window(scrn.mlx, S_WIDTH, S_HEIGHT, "MINIRT");
	scrn.img = mlx_new_image(scrn.mlx, S_WIDTH, S_HEIGHT);
	scrn.addr = mlx_get_data_addr(scrn.img, &scrn.bits_pp,
			&scrn.line_len, &scrn.endian);
	set_scene(&scrn, e_list);
	mlx_put_image_to_window(scrn.mlx, scrn.win, scrn.img, 0, 0);
	mlx_hook(scrn.win, 2, 1L << 0, kb_mlx, &scrn);
	mlx_loop(scrn.mlx);
	return (0);
}

void	mlx_pp(t_scData *scrn, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= S_WIDTH || y < 0 || y >= S_HEIGHT)
		return ;
	offset = y * scrn->line_len + x * scrn->bits_pp / 8;
	*(unsigned int *)(scrn->addr + (offset)) = color;
}

int	kb_mlx(int keycd, t_rtdata *data)
{
	if (keycd == K_ESC)
	{
		mlx_destroy_window(data->scrn->mlx, data->scrn->win);
		free_items(&data->items);
		exit(0);
	}
	if (keycd == K_ENTER)
		raytrace(*data);
	if (keycd == K_W)
	{
		camera_move(&data->camera, Forward, 0.1);
		draw(*data);
	}
	if (keycd == K_S)
	{
		camera_move(&data->camera, Backward, 0.1);
		draw(*data);
	}
	if (keycd == K_A)
	{
		camera_move(&data->camera, Left, 0.1);
		draw(*data);
	}
	if (keycd == K_D)
	{
		camera_move(&data->camera, Right, 0.1);
		draw(*data);
	}
	if (keycd == K_SPACE)
	{
		camera_move(&data->camera, Up, 0.1);
		draw(*data);
	}
	if (keycd == K_TAB)
	{
		camera_move(&data->camera, Down, 0.1);
		draw(*data);
	}
	if (keycd == K_RIGHT)
	{
		camera_rotate(&data->camera, Right, 0.1);
		draw(*data);
	}
	if (keycd == K_LEFT)
	{
		camera_rotate(&data->camera, Left, 0.1);
		draw(*data);
	}
	if (keycd == K_UP)
	{
		camera_rotate(&data->camera, Up, 0.1);
		draw(*data);
	}
	if (keycd == K_DOWN)
	{
		camera_rotate(&data->camera, Down, 0.1);
		draw(*data);
	}
	return (0);
}
