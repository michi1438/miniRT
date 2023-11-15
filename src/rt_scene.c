/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:15:14 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/15 12:13:02 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	set_scene(t_scData *scrn, t_list **e_list)
{
	(void)e_list;
	first_rays(scrn);
}

void	first_rays(t_scData *scrn)
{
	float	pscreen[3];
	int		y;
	int		x;
	float	radian_fov;	
	float	sratio;
	int		color;

	
	radian_fov = tan((M_PI * 110 / 180)/2);
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
			normalize(pscreen);
	//		printf("(%.5f,%.5f,%.5f) ", pscreen[0], pscreen[1], pscreen[2]);
			//add the position of the camera and its orientation...
			color = fabs(pscreen[0]) * 0x00FF0000;	
			color += fabs(pscreen[1]) * 0x0000FF00;	
			color += pow(pscreen[2], 2) * 0x000000FF;	
			mlx_pp(scrn, x, y, color);
		}
	//	printf("\n\n");
}
}

void	normalize(float *xyz)
{
	float vec_len;
	
	vec_len = sqrt(pow(xyz[0], 2) + pow(xyz[1], 2) + pow(xyz[2], 2));
	xyz[0] = xyz[0] / vec_len;
	xyz[1] = xyz[1] / vec_len;
	xyz[2] = xyz[2] / vec_len;
}

