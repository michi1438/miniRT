/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_v	project_point_onto_plane(t_v point, t_plane plane)
{
	float	dist;
	t_v		n;

	dist = signed_point_plane_dist(point, plane);
	n = v3_scale(plane_normal(plane), dist);
	if (dist > 0) {
		return (v3_sub(point, n));
	} else {
		return (v3_add(point, n));
	}
}

/* Multiplying a 3D matrix with a 3D vector (M x V) */
t_v	matrix_mult_vec(t_matrix3d matrix, t_v v)
{
	return (v3_add(v3_scale(matrix.v1, v.x), v3_add(v3_scale(matrix.v2, v.y), v3_scale(matrix.v3, v.z))));
}

/* Multiplying each term of a 3D matrix by a scalar */
t_matrix3d	matrix_scale(t_matrix3d matrix, float scalar)
{
	return (matrix3d_c(v3_scale(matrix.v1, scalar), v3_scale(matrix.v2, scalar), v3_scale(matrix.v3, scalar)));
}

/* Multiplying two 3D matrices */
t_matrix3d	matrix_mult(t_matrix3d m1, t_matrix3d m2)
{
	t_v	v1;
	t_v	v2;
	t_v	v3_;

	v1 = v3(
			m1.v1.x * m2.v1.x + m1.v2.x * m2.v1.y + m1.v3.x * m2.v1.z,
			m1.v1.y * m2.v1.x + m1.v2.y * m2.v1.y + m1.v3.y * m2.v1.z,
			m1.v1.z * m2.v1.x + m1.v2.z * m2.v1.y + m1.v3.z * m2.v1.z);
	v2 = v3(
			m1.v1.x * m2.v2.x + m1.v2.x * m2.v2.y + m1.v3.x * m2.v2.z,
			m1.v1.y * m2.v2.x + m1.v2.y * m2.v2.y + m1.v3.y * m2.v2.z,
			m1.v1.z * m2.v2.x + m1.v2.z * m2.v2.y + m1.v3.z * m2.v2.z);
	v3_ = v3(
			m1.v1.x * m2.v3.x + m1.v2.x * m2.v3.y + m1.v3.x * m2.v3.z,
			m1.v1.y * m2.v3.x + m1.v2.y * m2.v3.y + m1.v3.y * m2.v3.z,
			m1.v1.z * m2.v3.x + m1.v2.z * m2.v3.y + m1.v3.z * m2.v3.z);
	return (matrix3d_c(v1, v2, v3_));
}

t_matrix3d	matrix_sub(t_matrix3d m1, t_matrix3d m2)
{
	t_v	v1;
	t_v	v2;
	t_v	v3_;

	v1 = v3(m1.v1.x - m2.v1.x, m2.v1.y - m2.v1.y, m1.v1.z - m2.v1.z);
	v2 = v3(m1.v2.x - m2.v2.x, m2.v2.y - m2.v2.y, m1.v2.z - m2.v2.z);
	v3_ = v3(m1.v3.x - m2.v3.x, m2.v3.y - m2.v3.y, m1.v3.z - m2.v3.z);
	return (matrix3d_c(v1, v2, v3_));
}