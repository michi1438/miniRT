/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:29:13 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/02 10:16:43 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

int	main(int ac, char **av)
{
	t_list	*elst;

	elst = scene_parsing(ac, av);
	if (!elst)
		return (1);
	//put_to_screen(&elst);



	t_scData		scrn;

	scrn.e_list_displayed = &elst;
	scrn.mlx = mlx_init();
	scrn.win = mlx_new_window(scrn.mlx, S_WIDTH, S_HEIGHT, "MINIRT");
	scrn.img = mlx_new_image(scrn.mlx, S_WIDTH, S_HEIGHT);
	scrn.addr = mlx_get_data_addr(scrn.img, &scrn.bits_pp,
								  &scrn.line_len, &scrn.endian);
	set_scene(&scrn, &elst);
	mlx_put_image_to_window(scrn.mlx, scrn.win, scrn.img, 0, 0);
	mlx_hook(scrn.win, 2, 1L << 0, kb_mlx, &scrn);
	mlx_loop(scrn.mlx);



	return (0);
}
