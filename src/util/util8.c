/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_v	v3_cross(t_v a, t_v b)
{
	return (v3(a.y * b.z - a.z * b.y,a.z * b.x - a.x * b.z,a.x * b.y - a.y * b.x));
}

float	v3_dot(t_v a, t_v b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/* https://stackoverflow.com/a/12499474 */
t_v	project_point_onto_line(t_line line, t_v point)
{
	t_v		v1;
	t_v		v2;
	t_v		v3_;
	t_v		p;
	float	u;

	v1 = v3(line.p1.x, line.p1.y, line.p1.z);
	v2 = v3(line.p2.x, line.p2.y, line.p2.z);
	v3_ = v3(point.x, point.y, point.z);
	p = v3(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	u = ((v3_.x - v1.x) * p.x + (v3_.y - v1.y) * p.y + (v3_.z - v1.z) * p.z) / (p.x * p.x + p.y * p.y + p.z * p.z);
	return (v3(v1.x + u * p.x, v1.y + u * p.y, v1.z + u * p.z));
}

/* https://stackoverflow.com/a/3863777 */
float	point_plane_dist(t_v point, t_plane plane)
{
	return (fabs(v3_dot(plane_normal(plane), (v3_sub(point, plane.p1)))));
}

float	signed_point_plane_dist(t_v point, t_plane plane)
{
	return (v3_dot(plane_normal(plane), (v3_sub(point, plane.p1))));
}
