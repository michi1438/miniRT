/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

/* https://math.stackexchange.com/a/64528 */
t_plane	plane_from_normal(t_v point, t_v normal)
{
	t_v	w;
	t_v	u;
	t_v	v;

	if (fabs(normal.x) <= fabs(normal.y) && fabs(normal.x) <= fabs(normal.z))
		w = v3(1, 0, 0);
	else if (fabs(normal.y) <= fabs(normal.x)
		&& fabs(normal.y) <= fabs(normal.z))
		w = v3(0, 1, 0);
	else
		w = v3(0, 0, 1);
	u = v3_cross(w, normal);
	v = v3_cross(normal, u);
	return (plane_c(point, v3_add(point, u), v3_add(point, v)));
}

t_line	line(t_v p1, t_v p2)
{
	t_line	res;

	res.p1 = p1;
	res.p2 = p2;
	return (res);
}

t_mtrx	matrix3d_c(t_v v1, t_v v2, t_v v3)
{
	t_mtrx	res;

	res.v1 = v1;
	res.v2 = v2;
	res.v3 = v3;
	return (res);
}

int	same_side_of_line(t_line line, t_v A, t_v B)
{
	t_v	cross1;
	t_v	cross2;

	cross1 = v3_cross(v3_sub(line.p2, line.p1), v3_sub(A, line.p1));
	cross2 = v3_cross(v3_sub(line.p2, line.p1), v3_sub(B, line.p1));
	return (v3_dot(cross1, cross2) >= 0);
}
