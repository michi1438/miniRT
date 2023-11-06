/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:14:39 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/02 12:18:45 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

int	put_to_screen(t_list **e_list)
{
	t_scData		scrn;
	int				x = 0;

	(void)e_list;
	scrn.mlx = mlx_init();
	scrn.win = mlx_new_window(scrn.mlx, 1920/2, 1080/2, "MINIRT");
	scrn.img = mlx_new_image(scrn.mlx, 1920/2, 1080/2);
	scrn.addr = mlx_get_data_addr(scrn.img, &scrn.bits_pp, &scrn.line_len, &scrn.endian);
	while (x < 100)
		mlx_pp(&scrn, x++, 5, 0x00FF0000);
	mlx_put_image_to_window(scrn.mlx, scrn.win, scrn.img, 0, 0);
	mlx_hook(scrn.win, 2, 1L << 0, kb_mlx, &scrn);
	mlx_loop(scrn.mlx);
	return (0);
}

void	mlx_pp(t_scData *scrn, int x, int y, int color)
{
	*(unsigned int*)(scrn->addr + (y * scrn->line_len + x * scrn->bits_pp / 8)) = color;
}

int	kb_mlx(int keycd, t_scData *scrn)
{
	if (keycd == 65307 || keycd == 53)
	{
		mlx_destroy_window(scrn->mlx, scrn->win);
		exit(0);
	}
	return (0);
}
