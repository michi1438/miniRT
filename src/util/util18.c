/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util18.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

//make a function that takes some params and returns an intersection struct based on them

t_intersection	int_create(t_v pos, t_v norm, t_line ray, t_item *item)
{
	t_intersection	res;

	res.pos = pos;
	res.normal = norm;
	res.ray = ray;
	res.item = item;
	return (res);
}

t_vecfour	get_vecfour(t_v p1, t_v p2, t_v p3, t_v p4)
{
	t_vecfour	res;

	res.p1 = p1;
	res.p2 = p2;
	res.p3 = p3;
	res.p4 = p4;
	return (res);
}

int	point_inside_triangle(t_v s1, t_v s2, t_v s3, t_v point)
{
	t_plane	plane;
	t_v		norm;

	plane = plane_c(s1, s2, s3);
	norm = plane_normal(plane);
	if (fabs(v3_dot(v3_sub(point, s1), norm)) >= TOLERANCE) {
		return (0);
	}
	if (!same_side_of_line(line_c(s1, s2), s3, point)) {
		return (0);
	}
	if (!same_side_of_line(line_c(s1, s3), s2, point)) {
		return (0);
	}
	if (!same_side_of_line(line_c(s2, s3), s1, point)) {
		return (0);
	}
	return (1);
}

t_vecfour	get_pyramid_base_square(t_item pyramid)
{
	return (get_vecfour(pyramid.vertices[1], pyramid.vertices[2], pyramid.vertices[3], pyramid.vertices[4]));
}

void	get_pyramid_triangles(const t_item pyramid, t_v tri_buffer[4][3])
{
	tri_buffer[0][0] = pyramid.vertices[0];
	tri_buffer[0][1] = pyramid.vertices[1];
	tri_buffer[0][2] = pyramid.vertices[4];
	tri_buffer[1][0] = pyramid.vertices[0];
	tri_buffer[1][1] = pyramid.vertices[1];
	tri_buffer[1][2] = pyramid.vertices[2];
	tri_buffer[2][0] = pyramid.vertices[0];
	tri_buffer[2][1] = pyramid.vertices[2];
	tri_buffer[2][2] = pyramid.vertices[3];
	tri_buffer[3][0] = pyramid.vertices[0];
	tri_buffer[3][1] = pyramid.vertices[3];
	tri_buffer[3][2] = pyramid.vertices[4];
}