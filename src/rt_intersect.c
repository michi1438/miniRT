/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:28:03 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/16 19:56:08 by mguerga          ###   ########.fr       */
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
	//float	intersec_dist[2
	
	thc = 0;
	vec_substract(to_obj, cam_specs->xyz, obj->xyz);
	tca = dotprod(to_obj, normal_dir);
	d2 = dotprod(to_obj, to_obj) - tca * tca;
	if (d2 > obj->radius * obj->radius)
		return (-1);
	thc = sqrt(obj->radius * obj->radius - d2);
	//intersec_dist[0] = tca - thc;	
	//intersec_dist[1] = tca + thc;	
	// XXX somehow if the intersection is before the camera don't print pixel...
	quad_abc[0] = dotprod(normal_dir, normal_dir);
	quad_abc[1] = 2 * dotprod(normal_dir, to_obj);
	quad_abc[2] = dotprod(to_obj, to_obj) - obj->radius * obj->radius;

	if (solve_discriminent(quad_abc[0], quad_abc[1], quad_abc[2]) == 1)
		return (thc);	
	return (-1);
}

int	solve_discriminent(float a, float b, float c)
{
	float discrim;
   
	discrim = b * b - 4 * a * c;
	if (discrim >= 0)
		return (1);
	return (-1);
}
