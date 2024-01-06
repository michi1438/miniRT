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

	offset = y * scrn->line_len + x * scrn->bits_pp / 8;
	*(unsigned int *)(scrn->addr + (offset)) = color;
}

int	kb_mlx(int keycd, t_scData *scrn)
{
	if (keycd == 65307 || keycd == 53)
	{
		//ft_lstclear(scrn->e_list_displayed, free);
		mlx_destroy_window(scrn->mlx, scrn->win);
		exit(0);
	}
	return (0);
}
