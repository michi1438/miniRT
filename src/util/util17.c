/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util16.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

/* For plane ITEM */
t_intersection	intersect_ray_plane_item(t_line ray, t_item *plane)
{
	t_intersection	res;

	res = intersect_ray_plane(ray, plane_from_normal(plane->pos, plane->scale));
	res.item = plane;
	return (res);
}

t_intersection	intersect_ray_sphere(t_line ray, t_item *sphere)
{
	t_terms	terms;
	t_intersection	res;

	terms.D = v3_norm(v3_sub(ray.p2, ray.p1));
	terms.X = v3_sub(ray.p1, sphere->pos);
	terms.a = v3_dot(terms.D, terms.D);
	terms.b = 2 * v3_dot(terms.D, terms.X);
	terms.r = sphere->scale.x / 2;
	terms.c = v3_dot(terms.X, terms.X) - terms.r * terms.r;
	terms.discriminant = terms.b * terms.b - 4 * terms.a * terms.c;
	if (terms.discriminant < TOLERANCE)
		return (int_null());
	else
	{
		terms.t1 = (-terms.b + sqrt(terms.discriminant)) / (2 * terms.a);
		terms.t2 = (-terms.b - sqrt(terms.discriminant)) / (2 * terms.a);
		terms.point = v3_null();
		if (terms.t1 >= 0 && terms.t1 < terms.t2) {
			terms.point = v3_add(ray.p1, v3_scale(terms.D, terms.t1));
		} else if (terms.t2 >= 0) {
			terms.point = v3_add(ray.p1, v3_scale(terms.D, terms.t2));
		}
		if (!v3_is_null(terms.point)) {
			return (new RtIntersection(point, v3_norm(v3_sub(point, sphere.pos)), ray, sphere));
		}
	}
	return (int_null());
}

function point_inside_square(s1, s2, s3, s4, point) {
	let plane = new Plane(s1, s2, s3);
	let norm = plane.getNormal();
	let altitudeComponent = Math.abs(v3_dot(v3_sub(point, s1), norm));
	if (altitudeComponent >= TOLERANCE) {
		return (false);
	}
	if (!same_side_of_line(new Line(s1, s2), s3, point)) {
		return (false);
	}
	if (!same_side_of_line(new Line(s2, s3), s1, point)) {
		return (false);
	}
	if (!same_side_of_line(new Line(s3, s4), s1, point)) {
		return (false);
	}
	if (!same_side_of_line(new Line(s4, s1), s3, point)) {
		return (false);
	}
	return (true);
}
function get_cube_squares(cube) {
	return ([
	[cube.vertices[0], cube.vertices[1], cube.vertices[2], cube.vertices[3]],
	[cube.vertices[1], cube.vertices[2], cube.vertices[6], cube.vertices[5]],
	[cube.vertices[2], cube.vertices[3], cube.vertices[7], cube.vertices[6]],
	[cube.vertices[0], cube.vertices[3], cube.vertices[7], cube.vertices[4]],
	[cube.vertices[0], cube.vertices[1], cube.vertices[5], cube.vertices[4]],
	[cube.vertices[7], cube.vertices[6], cube.vertices[5], cube.vertices[4]]
	]);
}
function intersect_ray_cube(ray, cube) {
	let res = null;
	let dist = 0;

	let cube_squares = get_cube_squares(cube);
	for (var i = 0; i < cube_squares.length; i++) {
		let plane = new Plane(cube_squares[i][0], cube_squares[i][1], cube_squares[i][2]);
		let int = intersect_ray_plane(ray, plane);
		if (int != null) {
			if (point_inside_square(cube_squares[i][0], cube_squares[i][1], cube_squares[i][2], cube_squares[i][3], int.pos)) {
				let dist_ = v3_len(v3_sub(int.pos, ray.p1));
				if (res == null || dist_ < dist) {
					res = int;
					dist = dist_;
				}
			}
		}
	}
	if (res != null) {
		res.item = cube;
	}
	return (res);
}
