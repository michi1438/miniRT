/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_matrices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:18:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/30 17:32:12 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	rt_matrix(float *ret, t_elem *cam_specs)
{
	float	t;
	float	abc[3];

	t = cam_specs->norm_xyz[2];
	abc[0] = ret[0] * cos(t) + ret[1] * -(sin(t));
	abc[1] = ret[0] * sin(t) + ret[1] * cos(t);
	abc[2] = ret[2];
	t = cam_specs->norm_xyz[1];
	ret[0] = abc[0] * cos(t) + abc[2] * sin(t);
	ret[1] = abc[1];
	ret[2] = abc[0] * -(sin(t)) + abc[2] * cos(t);
	t = cam_specs->norm_xyz[0];
	abc[0] = ret[0];
	abc[1] = ret[1] * cos(t) + ret[2] * -(sin(t));
	abc[2] = ret[1] * sin(t) + ret[2] * cos(t);
	ret[0] = abc[0];
	ret[1] = abc[1];
	ret[2] = abc[2];
	ret[0] += cam_specs->xyz[0];
	ret[1] += cam_specs->xyz[1];
	ret[2] += cam_specs->xyz[2];
}
