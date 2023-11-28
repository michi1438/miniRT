/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:28:03 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/28 20:36:26 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

int	intersect(float *normal_dir, t_elem *cam_specs, t_elem *obj)
{
	//|O+tD|^2-R^2=0	
	// XXX not using actual elements just a hardcoded sphere...
	float	to_obj[3];	
	float	quad_abc[3];
	float	tca;
	float	d2;
	float	thc;	
	float	intersec_dist[2];
	
	thc = 0;
	vec_substract(to_obj, cam_specs->xyz, obj->xyz);
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
		if (intersec_dist[0] < 0)
			intersec_dist[0] = intersec_dist[1];	
		if (intersec_dist[0] >= 0)
			return (thc);	
	}
	return (-1);
}

int	solve_discriminent(float a, float b, float c, float *intersect_dist)
{
	float discrim;
	float q;
	float temp;
   
	discrim = b * b - 4 * a * c;
	if (discrim < 0)
		return (-1);
	else if (discrim == 0)
	{
		intersect_dist[0] = - 0.5 * b / a;
		intersect_dist[1] = - 0.5 * b / a;
	}
	else
	{
		if (b > 0)
			q = -0.5 * (b + sqrt(discrim));
		else
			q = -0.5 * (b - sqrt(discrim));
		intersect_dist[0] = q / a;
		intersect_dist[1] = b / q;
	}
	if (intersect_dist[0] > intersect_dist[1])
	{
		temp = intersect_dist[1];
		intersect_dist[1] = intersect_dist[0];
		intersect_dist[0] = temp;	
	}	
	return (1);
		

}
