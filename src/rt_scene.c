/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:15:14 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/16 14:01:42 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	set_scene(t_scData *scrn, t_list **e_list)
{
	first_rays(scrn, e_list);
}

void	first_rays(t_scData *scrn, t_list **e_list)
{
	float	pscreen[3];
	int		y;
	int		x;
	float	radian_fov;	
	float	sratio;
	float	thc;
	t_elem	*cam_specs;

	
	cam_specs = findcam(e_list);
	radian_fov = tan((M_PI * cam_specs->fov / 180) / 2);
	sratio = (float)S_WIDTH / S_HEIGHT;
	y = -1;
	while (++y < S_HEIGHT)
	{
		x = -1;
		while (++x < S_WIDTH)
		{
			pscreen[0] = ((2 * ((x + 0.5) / S_WIDTH)) - 1) * sratio * radian_fov;
			pscreen[1] = (1 - (2 * ((y + 0.5) / S_HEIGHT))) * radian_fov;
			pscreen[2] = -1;
			//emplement c2w matrix rotation and translation...
			normalize(pscreen);
			//printf("(%.5f,%.5f,%.5f) ", pscreen[0], pscreen[1], pscreen[2]);
			//add the position of the camera and its orientation...
			thc = intersect(pscreen, cam_specs);
			if (thc > 0)
				mlx_pp(scrn, x, y, 0x000000FF * thc / 10); // XXX this is not the right way to apply color...
		}
	}
}

void	normalize(float *xyz)
{
	float vec_len;
	
	vec_len = sqrt(pow(xyz[0], 2) + pow(xyz[1], 2) + 1);
	xyz[0] = xyz[0] / vec_len;
	xyz[1] = xyz[1] / vec_len;
	xyz[2] = xyz[2] / vec_len;
}

t_elem	*findcam(t_list **e_list)
{
	t_elem	*cam;
	t_list	*list;	

	list = *e_list;
	while (list != NULL)
	{
		cam = (list)->content;
		if (cam->type == 'C')
			return (cam);
		list = list->next;
	}
	return (NULL);
}

int	intersect(float *normal_dir, t_elem *cam_specs)
{
	//|O+tD|^2-R^2=0	
	// XXX not using actual elements just a hardcoded sphere...
	float	to_obj[3];	
	float	quad_abc[3];
	float	tca;
	float	d2;
	float	thc;	
	//float	intersec_dist[2];	
	
	thc = 0;
	to_obj[0] = 50 - cam_specs->xyz[0] ;
	to_obj[1] = 50 - cam_specs->xyz[1] ;
	to_obj[2] = -100 - cam_specs->xyz[2] ; 
	tca = dotprod(to_obj, normal_dir);
	d2 = dotprod(to_obj, to_obj) - tca * tca;
	if (d2 > 15 * 15)
		return (-1);
	thc = sqrt(15 * 15 - d2);
	//intersec_dist[0] = tca - thc;	
	//intersec_dist[1] = tca + thc;	
	// XXX somehow if the intersection is before the camera don't print pixel...
	quad_abc[0] = dotprod(normal_dir, normal_dir);
	quad_abc[1] = 2 * dotprod(normal_dir, to_obj);
	quad_abc[2] = dotprod(to_obj, to_obj) - 15 * 15;

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

float	dotprod(float *vec1, float *vec2)
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}
		
void	vec_substract(float *res_vec, float *vec1, float *vec2)
{
	res_vec[0] = vec1[0] - vec2[0];
	res_vec[1] = vec1[1] - vec2[1];
	res_vec[2] = vec1[2] - vec2[2];
}
