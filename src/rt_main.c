/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:29:13 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/17 12:10:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

t_list	*add_items(t_list **elst)
{
	t_list	*items;
	t_list	*iter;
	t_elem	*elem;

	items = NULL;
	iter = *elst;
	while (iter != NULL && iter->content != NULL)
	{
		elem = (iter)->content;
		if (elem->type != 'C' && elem->type != 'L'
			&& elem->type != 'A' && elem->type != '#')
		{
			if (!add_item(&items, elem))
			{
				free_items(&items);
				exit(1);
			}
		}
		iter = iter->next;
	}
	return (items);
}

void	add_lights(t_list **elst, t_rtdata *rtdata)
{
	t_list	*lights;
	t_elem	*amb;
	t_list	*amb__;
	t_list	*l__;
	t_elem	*l;

	lights = NULL;
	amb = findamb(elst);
	amb__ = ft_lstnew(light(Ambient, intensity_to_color(amb->light_ratio),
				v3(amb->xyz[0], amb->xyz[1], amb->xyz[2])));
	if (!amb__ || !amb__->content)
		exit(1);
	ft_lstadd_back(&lights, amb__);
	l = findlight(elst);
	l__ = ft_lstnew(light(Point, intensity_to_color(l->light_ratio),
				v3(l->xyz[0], l->xyz[1], l->xyz[2])));
	if (!l__ || !l__->content)
		exit(1);
	ft_lstadd_back(&lights, l__);
	rtdata->lights = lights;
}

int	main(int ac, char **av)
{
	t_list		*elst;
	t_scData	scrn;
	t_rtdata	rtdata;

	elst = scene_parsing(ac, av);
	if (!elst)
		return (1);
	scrn.e_list_displayed = &elst;
	scrn.mlx = mlx_init();
	scrn.win = mlx_new_window(scrn.mlx, S_WIDTH, S_HEIGHT, "MINIRT");
	scrn.img = mlx_new_image(scrn.mlx, S_WIDTH, S_HEIGHT);
	scrn.addr = mlx_get_data_addr(scrn.img, &scrn.bits_pp,
			&scrn.line_len, &scrn.endian);
	rtdata.scrn = &scrn;
	rtdata.camera = camera_c(v3(findcam(&elst)->xyz[0],
				findcam(&elst)->xyz[1], findcam(&elst)->xyz[2]),
			1, findcam(&elst)->fov, *findcam(&elst));
	add_lights(&elst, &rtdata);
	rtdata.items = add_items(&elst);
	draw(rtdata);
	mlx_hook(scrn.win, 2, 1L << 0, kb_mlx, &rtdata);
	mlx_hook(scrn.win, ON_DESTROY, 0, destroy, &rtdata);
	mlx_loop(scrn.mlx);
	return (0);
}
