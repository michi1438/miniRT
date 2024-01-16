/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util22.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

void	cyl_m1(t_terms *ts, t_v point, t_item cylinder)
{
	t_plane	xy_plane;
	t_v		xy_proj;
	t_v		x_proj;
	t_v		y_proj;

	xy_plane = plane_c(cylinder.pos, ts->x, ts->y);
	xy_proj = project_point_onto_plane(point, xy_plane);
	x_proj = project_point_onto_line(line_c(cylinder.pos, ts->x), xy_proj);
	ts->x_dist = v3_len(v3_sub(cylinder.pos, x_proj));
	if (v3_dot(ts->x_axis, v3_sub(x_proj, cylinder.pos)) < 0)
		ts->x_dist *= -1;
	y_proj = project_point_onto_line(line_c(cylinder.pos, ts->y), xy_proj);
	ts->y_dist = v3_len(v3_sub(cylinder.pos, y_proj));
	if (v3_dot(ts->y_axis, v3_sub(y_proj, cylinder.pos)) < 0)
		ts->y_dist *= -1;
}

void	cyl_m2(t_terms *ts, t_v point, t_item cylinder)
{
	t_plane	zy_plane;
	t_v		zy_proj;
	t_v		z_proj;

	zy_plane = plane_c(cylinder.pos, ts->z, ts->y);
	zy_proj = project_point_onto_plane(point, zy_plane);
	z_proj = project_point_onto_line(line_c(cylinder.pos, ts->z), zy_proj);
	ts->z_dist = v3_len(v3_sub(cylinder.pos, z_proj));
	if (v3_dot(ts->z_axis, v3_sub(z_proj, cylinder.pos)) < 0)
		ts->z_dist *= -1;
}

t_v	cylindrical_map(t_v point, t_item cylinder)
{
	float	u;
	float	v;
	t_terms	ts;

	ts.y_axis = item_get_axis(cylinder);
	ts.z = plane_from_normal(cylinder.pos, ts.y_axis).p2;
	ts.x = plane_from_normal(cylinder.pos, ts.y_axis).p3;
	ts.y = v3_add(cylinder.pos, ts.y_axis);
	ts.z_axis = v3_norm(v3_sub(ts.z, cylinder.pos));
	ts.x_axis = v3_norm(v3_sub(ts.x, cylinder.pos));
	cyl_m1(&ts, point, cylinder);
	cyl_m2(&ts, point, cylinder);
	ts.point = v3(ts.x_dist, ts.y_dist, ts.z_dist);
	u = fmodf((1 - ((atan2f(point.x, point.z)) / (2 * M_PI) + 0.5)), 1);
	v = fmodf(point.y, 1);
	return (v3(u, v, 0));
}
