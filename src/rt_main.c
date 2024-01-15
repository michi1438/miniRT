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
	//set_scene(&scrn, &elst);
	t_elem *cam = findcam(&elst);
	t_camera	camera = camera_c(v3(cam->xyz[0], cam->xyz[1], cam->xyz[2]), 1, cam->fov);

	t_list *lights;
	lights = NULL;
	t_elem	*amb = findamb(&elst);
	t_light amb_ = light(Ambient, intensity_to_color(amb->light_ratio), v3(amb->xyz[0], amb->xyz[1], amb->xyz[2]));
	t_list	*amb__ = ft_lstnew(&amb_);
	ft_lstadd_back(&lights, amb__);

	t_elem	*l = findlight(&elst);
	t_light l_ = light(Point, intensity_to_color(l->light_ratio), v3(l->xyz[0], l->xyz[1], l->xyz[2]));
	t_list	*l__ = ft_lstnew(&l_);
	ft_lstadd_back(&lights, l__);

	t_list	*items;
	items = NULL;
	t_list	*iter;

	iter = elst;
	while (iter != NULL && iter->content != NULL)
	{
		t_elem *elem = (iter)->content;
		if (elem->type == 's')
		{
			t_item	*item = create_item(Sphere, tuple(v3(elem->xyz[0], elem->xyz[1], elem->xyz[2]), v3(elem->radius * 2, 0, 0)), tuple(v3(elem->norm_xyz[0], elem->norm_xyz[1], elem->norm_xyz[2]), v3(elem->rgb[0], elem->rgb[1], elem->rgb[2])));
			ft_lstadd_back(&items, ft_lstnew(item));
		}
		else if (elem->type == 'p')
		{
			t_item	*item = create_item(Plane, tuple(v3(elem->xyz[0], elem->xyz[1], elem->xyz[2]), v3(elem->norm_xyz[0], elem->norm_xyz[1], elem->norm_xyz[2])), tuple(v3(elem->norm_xyz[0], elem->norm_xyz[1], elem->norm_xyz[2]), v3(elem->rgb[0], elem->rgb[1], elem->rgb[2])));
			ft_lstadd_back(&items, ft_lstnew(item));
		}
		else if (elem->type == 'c')
		{
			t_item	*item = create_item(Cylinder, tuple(v3(elem->xyz[0], elem->xyz[1], elem->xyz[2]), v3(elem->radius * 2, elem->height, 0)), tuple(v3(elem->norm_xyz[0], elem->norm_xyz[1], elem->norm_xyz[2]), v3(elem->rgb[0], elem->rgb[1], elem->rgb[2])));
			ft_lstadd_back(&items, ft_lstnew(item));
		}
		iter = iter->next;
	}

	t_rtdata rtdata;
	rtdata.scrn = &scrn;
	rtdata.camera = camera;
	rtdata.lights = lights;
	rtdata.items = items;

	//cast_ray_for_screen_coords(rtdata, 470, 765);

	draw(rtdata);

	mlx_hook(scrn.win, 2, 1L << 0, kb_mlx, &rtdata);
	mlx_loop(scrn.mlx);

	return (0);
}
