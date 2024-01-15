/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

int	same_side_of_plane(t_plane plane, t_v A, t_v B)
{
	float	dot1;
	float	dot2;

	dot1 = v3_dot(plane_normal(plane), v3_sub(A, plane.p1));
	dot2 = v3_dot(plane_normal(plane), v3_sub(B, plane.p1));
	return (same_sign(dot1, dot2));
}

static t_matrix3d	get_rot_matrix(t_v v)
{
	t_matrix3d 	rot_matrix_x;
	t_matrix3d 	rot_matrix_y;
	t_matrix3d 	rot_matrix_z;

	rot_matrix_x = matrix3d_c(v3(1, 0, 0),v3(0, cos(v.x), sin(v.x)),v3(0, -sin(v.x), cos(v.x)));
	rot_matrix_y = matrix3d_c(v3(cos(v.y), 0, -sin(v.y)),v3(0, 1, 0),v3(sin(v.y), 0, cos(v.y)));
	rot_matrix_z = matrix3d_c(v3(cos(v.z), sin(v.z), 0),v3(-sin(v.z), cos(v.z), 0),v3(0, 0, 1));
	return (matrix_mult(rot_matrix_x, matrix_mult(rot_matrix_y, rot_matrix_z)));
}

/* rotate point p, by a vector v, around a point r */
t_v	rotate_point(t_v p, t_v v, t_v r)
{
	t_matrix3d	rot_matrix;
	t_v			p_translate;
	t_v			p_rotated1;

	rot_matrix = get_rot_matrix(v);
	p_translate = v3_sub(p, r);
	p_rotated1 = matrix_mult_vec(rot_matrix, p_translate);
	return (v3_add(p_rotated1, r));
}

float	vect_angle(t_v v1, t_v v2)
{
	return (acosf(fmin(1, v3_dot(v1, v2) / (v3_len(v1) * v3_len(v2)))));
}

float	degree_to_radian(float angle)
{
	return (angle * M_PI / 180);
}