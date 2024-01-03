/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:28:03 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/03 16:09:49 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

float	intersect_sp(float *normal_dir, float orig_xyz[3], t_elem *obj)
{
	float	to_obj[3];	
	float	quad_abc[3];
	float	tca;
	float	d2;
	float	thc;	
	float	intersec_dist[2];

	thc = 0;
	vec_substract(to_obj, orig_xyz, obj->xyz);
	tca = dotprod(to_obj, normal_dir);
	d2 = dotprod(to_obj, to_obj) - tca * tca;
	if (d2 > obj->radius * obj->radius)
		return (-1);
	thc = sqrt(obj->radius * obj->radius - d2);
	intersec_dist[0] = tca - thc;
	intersec_dist[1] = tca + thc;
	if (intersec_dist[0] > intersec_dist[1])
	{
		intersec_dist[1] = tca - thc;
		intersec_dist[0] = tca + thc;
	}	
	quad_abc[0] = dotprod(normal_dir, normal_dir);
	quad_abc[1] = 2 * dotprod(normal_dir, to_obj);
	quad_abc[2] = dotprod(to_obj, to_obj) - obj->radius * obj->radius;
	if (solve_discriminent(quad_abc[0], quad_abc[1], quad_abc[2], intersec_dist) == 1)
	{
		if (intersec_dist[1] > 0)
			return (intersec_dist[1]);
		else if (intersec_dist[0] > 0)
			return (intersec_dist[0]);
	}
	return (-1);
}

int	solve_discriminent(float a, float b, float c, float *intersect_dist)
{
	float	discrim;
	float	q;

	discrim = b * b - 4 * a * c;
	if (discrim < 0)
		return (-1);
	else if (discrim == 0)
	{
		intersect_dist[0] = -0.5 * b / a;
		intersect_dist[1] = -0.5 * b / a;
	}
	else
	{
		if (b > 0)
			q = -0.5 * (b + sqrt(discrim));
		else
			q = -0.5 * (b - sqrt(discrim));
		intersect_dist[0] = q / a;
		intersect_dist[1] = c / q;
	}
	return (1);
}
