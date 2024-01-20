/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kb_and_pp_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:15:26 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/18 12:15:30 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

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
	more_keys1(keycd, data);
	return (0);
}

static void	more_keys3(int keycd, t_rtdata *data)
{
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
}

static void	more_keys2(int keycd, t_rtdata *data)
{
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
	more_keys3(keycd, data);
}

void	more_keys1(int keycd, t_rtdata *data)
{
	if (keycd == K_ESC)
	{
		mlx_destroy_window(data->scrn->mlx, data->scrn->win);
		free_items(&data->items);
		exit(0);
	}
	if (keycd == K_ENTER && get_resolution() > 0)
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
	more_keys2(keycd, data);
}
