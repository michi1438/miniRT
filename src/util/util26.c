/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util26.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_v	get_item_color_checkerboard(t_intsc intr)
{
	t_v		inverse_color;
	t_plane	nearest_plane;

	inverse_color = v3_sub(v3(255, 255, 255), intr.item->color);
	if (intr.item->type == Plane)
		return (chckr_pix_plan(tuple(intr.pos, intr.item->pos),
				intr.item->scale, 2, tuple(inverse_color, intr.item->color)));
	else if (intr.item->type == Sphere)
		return (uv_at_chekers(intr.item->color, inverse_color,
				v3(32, 8, 0), spherical_map(intr.pos, *intr.item)));
	else if (intr.item->type == Cylinder)
		return (uv_at_chekers(intr.item->color, inverse_color,
				v3(32, 8, 0), cylindrical_map(intr.pos, *intr.item)));
	else if (intr.item->type == Cube || intr.item->type == Pyramid)
	{
		nearest_plane = get_intsc_plane(intr);
		return (chckr_pix_plan(tuple(intr.pos, nearest_plane.p2),
				plane_normal(nearest_plane),
				intr.item->scale.x / 10, tuple(inverse_color,
					intr.item->color)));
	}
	else
		return (intr.item->color);
}

t_intsc	cast_ray(t_rtdata data, t_line ray, int do_draw)
{
	t_terms	ts;
	t_list	*list;

	ts.inter = int_null();
	ts.dist = 0;
	list = data.items;
	while (list != NULL)
	{
		ts.inter2 = ray_intersection(ray, (t_item *)list->content);
		if (!int_is_null(ts.inter2))
		{
			ts.dist_ = v3_len(v3_sub(ts.inter2.pos, ray.p1));
			if (int_is_null(ts.inter) || ts.dist_ < ts.dist)
			{
				ts.inter = ts.inter2;
				ts.dist = ts.dist_;
			}
		}
		list = list->next;
	}
	if (do_draw && !int_is_null(ts.inter))
		cast_ray2(ts, data);
	return (ts.inter);
}

static int	get_rays_size(t_camra camera, double resolution)
{
	double	i;
	double	j;
	int		k;

	i = 0;
	k = 0;
	while (i < camera.canvas_width)
	{
		j = 0;
		while (j < camera.canvas_height)
		{
			k ++;
			j += resolution;
		}
		i += resolution;
	}
	return (k);
}

void	raytrace(t_rtdata data)
{
	t_line	*rays;
	int		i;
	int		sz;
	double	resolution;

	resolution = get_resolution();
	sz = get_rays_size(data.camera, resolution);
	printf("got ray size: %d\n", sz);
	rays = gen_rays(data.camera, sz, resolution);
	printf("finished calculating rays\n");
	fill_screen(data.scrn, v3(0, 0, 0));
	if (!rays)
		return ;
	i = 0;
	while (i < sz)
	{
		cast_ray(data, rays[i], 1);
		i ++;
	}
	free(rays);
	mlx_put_image_to_window(data.scrn->mlx,
		data.scrn->win, data.scrn->img, 0, 0);
	printf("done!\n");
}

void	cast_ray_for_screen_coords(t_rtdata data, float x, float y)
{
	t_v	mapped;

	mapped = mp_phys_cam(data.camera,
			v3(x, y, 0), S_WIDTH, S_HEIGHT);
	cast_ray(data, line_c(data.camera.eye, mapped), 1);
}
