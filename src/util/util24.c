/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util24.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

/* https://stackoverflow.com/a/1024061 */
/* consistent x, y mapping on a plane with an arbitrary rotation applied to it */
/*
	point: point to map
	origin: origin of the plane
	normal: normal of the plane
*/
t_v	normalize_plane_point(t_v point, t_v origin, t_v normal)
{
	t_terms	ts;
	t_v		new_y_axis;
	t_v		new_x_axis;
	t_v		origin_to_point;

	if (equals_with_tolerance(fabs(normal.x), 1) && normal.y == 0 && normal.z == 0) {
		ts.z_axis = v3(0, 0, 1);
		new_y_axis = v3_norm(v3_cross(ts.z_axis, normal));
		new_x_axis = v3_norm(v3_cross(normal, new_y_axis));
		origin_to_point = v3_sub(point, origin);
		return (v3(v3_dot(origin_to_point, new_x_axis), v3_dot(origin_to_point, new_y_axis), 0));
	}
	ts.x_axis = v3(1, 0, 0);
	new_y_axis = v3_norm(v3_cross(ts.x_axis, normal));
	new_x_axis = v3_norm(v3_cross(normal, new_y_axis));
	origin_to_point = v3_sub(point, origin);
	return (v3(v3_dot(origin_to_point, new_x_axis), v3_dot(origin_to_point, new_y_axis), 0));
}

t_v	cartesian_to_sphere(t_v point, t_item sphere)
{
	t_terms	ts;
	t_plane	plane;

	ts.z_axis = item_get_axis(sphere);
	plane = plane_from_normal(sphere.pos, ts.z_axis);
	return (v3(v3_len(v3_sub(point, sphere.pos)), vect_angle(v3_sub(plane.p2, sphere.pos), v3_sub(project_point_onto_plane(point, plane), sphere.pos)), vect_angle(ts.z_axis, v3_sub(point, sphere.pos))));
}

t_v	checker_pixel_for_plane(t_v3_tuple pt_orig, t_v normal, float step, t_v3_tuple colors)
{
	t_v	new_pos;
	int	parity_x;
	int	parity_y;

	new_pos = normalize_plane_point(pt_orig.v1, pt_orig.v2, normal);
	if (new_pos.x < 0)
		new_pos.x -= step;
	if (new_pos.y < 0)
		new_pos.y -= step;
	parity_x = fmodf(floorf(fabs(new_pos.x) / step), 2);
	parity_y = fmodf(floorf(fabs(new_pos.y) / step), 2);
	if (parity_x == parity_y) {
		return (colors.v1);
	} else {
		return (colors.v2);
	}
}

static void	int_pl_py(t_plane *nearest_plane, t_intersection intr, t_terms *ts)
{
	t_v		tr[5][3];
	int		i;

	get_pyramid_triangles(*intr.item, tr);
	tr[4][0] = get_pyramid_base_square(*intr.item).p1;
	tr[4][1] = get_pyramid_base_square(*intr.item).p2;
	tr[4][2] = get_pyramid_base_square(*intr.item).p3;
	i = 0;
	while (i < 5)
	{
		ts->dist_ = point_plane_dist(intr.pos, plane_c(tr[i][0], tr[i][1], tr[i][2]));
		if (ts->a == 0 || ts->dist_ < ts->dist)
		{
			*nearest_plane = plane_c(tr[i][0], tr[i][1], tr[i][2]);
			ts->dist = ts->dist_;
			ts->a = 1;
		}
		i++;
	}
}

t_plane	get_intersection_plane(t_intersection intr)
{
	t_plane	nearest_plane;
	t_terms	ts;
	t_v		sq[6][4];
	int		i;

	ts.a = 0;
	ts.dist = 0;
	if (intr.item->type == Cube)
	{
		get_cube_squares(*intr.item, sq);
		i = 0;
		while (i < 6) {
			ts.dist_ = point_plane_dist(intr.pos, plane_c(sq[i][0], sq[i][1], sq[i][2]));
			if (ts.a == 0 || ts.dist_ < ts.dist) {
				nearest_plane = plane_c(sq[i][0], sq[i][1], sq[i][2]);
				ts.dist = ts.dist_;
				ts.a = 1;
			}
			i ++;
		}
	}
	else
		int_pl_py(&nearest_plane, intr,&ts);
	return (nearest_plane);
}
