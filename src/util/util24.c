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
vec	normalize_plane_point(vec point, vec origin, vec normal)
{
	t_terms	ts;
	vec		new_y_axis;
	vec		new_x_axis;
	vec		origin_to_point;

	if (equals_with_tolerance(fabs(normal.x), 1) && normal.y == 0 && normal.z == 0) {
		ts.z_axis = v3(0, 0, 1);
		new_y_axis = v3_norm(v3_cross(ts.z_axis, normal));
		new_x_axis = v3_norm(v3_cross(normal, new_y_axis));
		origin_to_point = v3_sub(point, origin);
		return (v3(v3_dot(origin_to_point, new_x_axis), v3_dot(origin_to_point, new_y_axis)));
	}
	ts.x_axis = v3(1, 0, 0);
	new_y_axis = v3_norm(v3_cross(ts.x_axis, normal));
	new_x_axis = v3_norm(v3_cross(normal, new_y_axis));
	origin_to_point = v3_sub(point, origin);
	return (v3(v3_dot(origin_to_point, new_x_axis), v3_dot(origin_to_point, new_y_axis)));
}

vec	cartesian_to_sphere(vec point, t_item sphere)
{
	t_terms	ts;
	t_plane	plane;

	ts.z_axis = item_get_axis(sphere);
	plane = plane_from_normal(sphere.pos, ts.z_axis);
	return (v3(v3_len(v3_sub(point, sphere.pos)), vect_angle(v3_sub(plane.p2, sphere.pos), v3_sub(project_point_onto_plane(point, plane), sphere.pos)), vect_angle(ts.z_axis, v3_sub(point, sphere.pos))));
}

vec	checker_pixel_for_plane(point, origin, normal, step, color1, color2) {
	let new_pos = normalize_plane_point(point, origin, normal);
	if (new_pos.x < 0) {
		new_pos.x -= step;
	}
	if (new_pos.y < 0) {
		new_pos.y -= step;
	}
	const checkerX = Math.floor(Math.abs(new_pos.x) / step);
	const checkerY = Math.floor(Math.abs(new_pos.y) / step);
	const parityX = checkerX % 2;
	const parityY = checkerY % 2;
	if (parityX === parityY) {
		return (color1);
	} else {
		return (color2);
	}
}

static void	int_pl_cb(t_plane *nearest_plane, float *nearest_plane_dist, t_intersection intr)
{
	let squares = get_cube_squares(int.item);
	for (var i = 0; i < squares.length; i++) {
		let plane = new Plane(squares[i][0], squares[i][1], squares[i][2]);
		let dist_ = point_plane_dist(int.pos, plane);
		if (!nearest_plane || dist_ < nearest_plane_dist) {
			nearest_plane = plane;
			nearest_plane_dist = dist_;
		}
	}
}

t_plane	get_intersection_plane(t_intersection intr)
{
	t_plane	nearest_plane;
	float	nearest_plane_dist;

	if (intr.item->type == Cube)
		int_pl_cb(&nearest_plane, &nearest_plane_dist, intr);
	else
	{
		let triangles = get_pyramid_triangles(int.item);
		triangles.push(get_pyramid_base_square(int.item));
		for (var i = 0; i < triangles.length; i++) {
			let plane = new Plane(triangles[i][0], triangles[i][1], triangles[i][2]);
			let dist_ = point_plane_dist(int.pos, plane);
			if (!nearest_plane || dist_ < nearest_plane_dist) {
				nearest_plane = plane;
				nearest_plane_dist = dist_;
			}
		}
	}
	return (nearest_plane);
}
