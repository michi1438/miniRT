/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util19.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

static void	int_ray_pyr_1(t_terms *ts, t_item pyramid, t_line ray)
{
	t_vecfour	base_square;
	t_plane		plane;

	base_square = get_pyramid_base_square(pyramid);
	plane = plane_c(base_square.p1, base_square.p2, base_square.p3);
	ts->inter2 = intersect_ray_plane(ray, plane);
	if (!int_is_null(ts->inter2))
	{
		if (point_inside_square(base_square, ts->inter2.pos))
		{
			ts->dist_ = v3_len(v3_sub(ts->inter2.pos, ray.p1));
			if (int_is_null(ts->inter) || ts->dist_ < ts->dist) {
				ts->inter = ts->inter2;
				ts->dist = ts->dist_;
			}
		}
	}
}

static void	int_ray_pyr_2(t_terms *ts, t_item pyramid, t_line ray)
{
	t_v		triangles[4][3];
	t_plane	plane;
	int		i;

	get_pyramid_triangles(pyramid, triangles);
	i = 0;
	while (i < 4)
	{
		plane = plane_c(triangles[i][0], triangles[i][1], triangles[i][2]);
		ts->inter2 = intersect_ray_plane(ray, plane);
		if (!int_is_null(ts->inter2))
		{
			if (point_inside_triangle(triangles[i][0], triangles[i][1], triangles[i][2], ts->inter2.pos))
			{
				ts->dist_ = v3_len(v3_sub(ts->inter2.pos, ray.p1));
				if (int_is_null(ts->inter) || ts->dist_ < ts->dist) {
					ts->inter = ts->inter2;
					ts->dist = ts->dist_;
				}
			}
		}
		i ++;
	}
}

t_intersection	intersect_ray_pyramid(t_line ray, t_item *pyramid)
{
	t_terms	ts;

	ts.inter = int_null();
	ts.dist = 0;
	int_ray_pyr_1(&ts, *pyramid, ray);
	int_ray_pyr_2(&ts, *pyramid, ray);
	ts.inter.item = pyramid;
	return (ts.inter);
}

t_intersection	ray_intersection(t_line ray, t_item *object)
{
	if (object->type == Plane)
		return (intersect_ray_plane_item(ray, object));
	else if (object->type == Sphere)
		return (intersect_ray_sphere(ray, object));
	else if (object->type == Cube)
		return (intersect_ray_cube(ray, object));
	else if (object->type == Pyramid)
		return (intersect_ray_pyramid(ray, object));
	else if (object->type == Cylinder)
		return (intersect_ray_cylinder(ray, object));
	return (int_null());
}

static void	cmpt_lt(t_rtdata data, t_light light, t_v *res, t_intersection intr)
{
	t_v	L;
	t_terms	ts;
	float	n_dot_l;

	ts.inter2 = cast_ray(data, line_c(light.pos, intr.pos), 0);
	if (!int_is_null(ts.inter2) && ts.inter2.item->id != intr.item->id)
	{
		if (v3_len(v3_sub(ts.inter2.pos, intr.pos)) < v3_len(v3_sub(intr.pos, light.pos))) {
			return ;
		}
	}
	L = v3_sub(light.pos, intr.pos);
	n_dot_l = v3_dot(intr.normal, L);
	if (n_dot_l > 0) {
		*res = add_colors(*res, modify_color_intensity(light.color, n_dot_l/(v3_len(intr.normal) * v3_len(L))));
	}
}

/* From book 'Computer Graphics from Scratch' by Gabriel Gambetta */
t_v	compute_lighting(t_rtdata data, t_intersection intr, t_list *lights)
{
	t_v	res;
	t_list	*list;

	res = v3(0, 0, 0);
	list = lights;
	while (list != NULL)
	{
		if (((t_light *)list->content)->type == Ambient)
		{
			res = add_colors(res, ((t_light *)list->content)->color);
		}
		else
		{
			cmpt_lt(data, *((t_light *)list->content), &res, intr);
		}
		list = list->next;
	}
	res.x = res.x / 255;
	res.y = res.y / 255;
	res.z = res.z / 255;
	return (res);
}