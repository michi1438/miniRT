/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util10.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_mtrx	get_identity_matrix(void)
{
	return (matrix3d_c(v3(1, 0, 0), v3(0, 1, 0), v3(0, 0, 1)));
}

t_v	get_cylinder_top(t_item cylinder)
{
	t_v	v;

	v = v3_norm(v3_sub(cylinder.vertices[0],
				cylinder.vertices[cylinder.vertices_len / 2]));
	return (v3_add(cylinder.pos, v3_scale(v, -cylinder.scale.y / 2)));
}

t_v	get_cylinder_bottom(t_item cylinder)
{
	t_v	v;

	v = v3_norm(v3_sub(cylinder.vertices[0],
				cylinder.vertices[cylinder.vertices_len / 2]));
	return (v3_add(cylinder.pos, v3_scale(v, cylinder.scale.y / 2)));
}

t_v	intersect(t_line line, t_plane plane)
{
	t_v		n;
	float	d;
	t_v		lv;
	float	divisor;
	float	dividend;

	n = v3_norm(v3_cross(v3_sub(plane.p3, plane.p1),
				v3_sub(plane.p2, plane.p1)));
	d = -(n.x * plane.p1.x + n.y * plane.p1.y + n.z * plane.p1.z);
	lv = v3_sub(line.p2, line.p1);
	divisor = n.x * lv.x + n.y * lv.y + n.z * lv.z;
	if (divisor == 0)
	{
		return (v3_null());
	}
	dividend = -(n.x * line.p1.x + n.y * line.p1.y + n.z * line.p1.z + d);
	if (dividend == 0)
		return (v3_null());
	return (v3_add(line.p1, v3_scale(lv, dividend / divisor)));
}

int	equals_with_tolerance(float val1, float val2)
{
	return (val1 <= val2 + TOLERANCE && val1 >= val2 - TOLERANCE);
}
