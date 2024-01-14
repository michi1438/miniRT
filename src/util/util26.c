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

vec	get_item_color_checkerboard(t_intersection intr)
{
	vec	inverse_color;
	t_plane	nearest_plane;
	vec		u_v;

	inverse_color = v3_sub(color_from_int(WHITE), intr.item->color);
	if (intr.item->type == Plane) {
		return (checker_pixel_for_plane(tuple(intr.pos, intr.item->pos), intr.item->scale, 2, tuple(inverse_color, intr.item->color)));
	} else if (intr.item->type == Sphere) {
		u_v = spherical_map(intr.pos, *intr.item);
		return(uv_at_chekers(intr.item->color, inverse_color, v3(32, 8, 0), u_v));
	} else if (intr.item->type == Cylinder) {
		u_v = cylindrical_map(intr.pos, *intr.item);
		return(uv_at_chekers(intr.item->color, inverse_color, v3(32, 8, 0), u_v));
	} else if (intr.item->type == Cube) {
		nearest_plane = get_intersection_plane(intr);
		return (checker_pixel_for_plane(tuple(intr.pos, nearest_plane.p2), plane_normal(nearest_plane), intr.item->scale.x / 10, tuple(inverse_color, intr.item->color)));
	} else if (intr.item->type == Pyramid) {
		nearest_plane = get_intersection_plane(intr);
		return (checker_pixel_for_plane(tuple(intr.pos, nearest_plane.p2), plane_normal(nearest_plane), intr.item->scale.x / 10, tuple(inverse_color, intr.item->color)));
	} else {

		return (intr.item->color);
	}
}

int count = 0;
t_intersection	cast_ray(t_rtdata data, t_line ray, int do_draw)
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
			ts.dist_ =  v3_len(v3_sub(ts.inter2.pos, ray.p1));
			if (int_is_null(ts.inter) || ts.dist_ < ts.dist)
			{
				ts.inter = ts.inter2;
				ts.dist = ts.dist_;
			}
		}
		list = list->next;
	}
	if (do_draw && !int_is_null(ts.inter)) {
		count ++;
		ts.point = map_point_to_physical(data.camera, ts.inter.ray.p2, S_WIDTH, S_HEIGHT);
		ts.light_color = compute_lighting(data, ts.inter, data.lights);
		ts.specular_color = modify_color_intensity(compute_specular(data, ts.inter, data.lights), SPECULAR);
		ts.diffuse_color = mult_colors(get_item_color(ts.inter), ts.light_color);
		ts.color = add_colors(ts.diffuse_color, ts.specular_color);

		mlx_pp(data.scrn, ts.point.x, ts.point.y, vec_color_to_int(ts.color));
	}
	return (ts.inter);
}

static int	get_rays_size(t_camera camera, double resolution)
{
	double	i;
	double	j;
	int	k;

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

	double resolution = RESOLUTION;
	if (getenv("RESOLUTION"))
	{
		resolution = atof(getenv("RESOLUTION"));
		printf("picked up resolution from env: %f\n", resolution);
	} else {
		printf("using hardcoded resolution: %f\n", resolution);
	}
	sz = get_rays_size(data.camera, resolution);
	printf("got ray size: %d\n", sz);
	rays = gen_rays(data.camera, sz, resolution);
	printf("finished calculating rays\n");
	if (!rays)
		return ;
	i = 0;
	count = 0;
	while (i < sz)
	{
		cast_ray(data, rays[i], 1);
		i ++;
	}
	free(rays);
	mlx_put_image_to_window(data.scrn->mlx, data.scrn->win, data.scrn->img, 0, 0);
	printf("painted %d pixels\n", count);
}

void	cast_ray_for_screen_coords(t_rtdata data, float x, float y)
{
	vec	mapped;

	mapped = map_physical_to_camera(data.camera, v3(x, y, 0), S_WIDTH, S_HEIGHT);
	cast_ray(data, line_c(data.camera.eye, mapped), 1);
}
