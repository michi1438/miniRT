/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:15:14 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/29 15:40:44 by mguerga          ###   ########.fr       */
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
	int		xy[2];
	float	thc;
	float	viewport_xy[2][3];
	float	delta_xy[2][3];
	float	viewport_upperleft[3];
	float	pixel00_loc[3];
	t_elem	*cam_specs;
	t_elem	*objects;
	t_list	*list;	

	cam_specs = findcam(e_list);
	viewport_xy[0][0] = 2 * cam_specs->sratio;
	viewport_xy[0][1] = 0;
	viewport_xy[0][2] = 0;
	viewport_xy[1][0] = 0;
	viewport_xy[1][1] = -2;
	viewport_xy[1][2] = 0;

	delta_xy[0][0] = viewport_xy[0][0] / S_WIDTH;
	delta_xy[0][1] = viewport_xy[0][1] / S_WIDTH;
	delta_xy[0][2] = viewport_xy[0][2] / S_WIDTH;
	delta_xy[1][0] = viewport_xy[1][0] / S_HEIGHT;
	delta_xy[1][1] = viewport_xy[1][1] / S_HEIGHT;
	delta_xy[1][2] = viewport_xy[1][2] / S_HEIGHT;

	viewport_upperleft[0] = cam_specs->xyz[0] - viewport_xy[0][0] / 2 - viewport_xy[1][0] / 2;
	viewport_upperleft[1] = cam_specs->xyz[1] - viewport_xy[0][1] / 2 - viewport_xy[1][1] / 2;
	viewport_upperleft[2] = cam_specs->xyz[2] - viewport_xy[0][2] / 2 - viewport_xy[1][2] / 2 - 1;//focal_length along z axis;
	
	pixel00_loc[0] = viewport_upperleft[0] + 0.5 * (delta_xy[0][0] + delta_xy[1][0]);
	pixel00_loc[1] = viewport_upperleft[1] + 0.5 * (delta_xy[0][1] + delta_xy[1][1]);
	pixel00_loc[2] = viewport_upperleft[2] + 0.5 * (delta_xy[0][2] + delta_xy[1][2]);
	xy[1] = -1;
	while (++xy[1] < S_HEIGHT)
	{
		xy[0] = -1;
		while (++xy[0] < S_WIDTH)
		{
			//pscreen[0] = ((2 * (xy[0] + 0.5) / S_WIDTH) - 1) * cam_specs->fov * cam_specs->sratio;
			pscreen[0] = pixel00_loc[0] + (xy[0] * delta_xy[0][0]) + (xy[1] * delta_xy[1][0]) * cam_specs->fov * cam_specs->sratio;
			pscreen[1] = pixel00_loc[1] + (xy[0] * delta_xy[0][1]) + (xy[1] * delta_xy[1][1]) * cam_specs->fov;
			pscreen[2] = pixel00_loc[2] + (xy[0] * delta_xy[0][2]) + (xy[1] * delta_xy[1][2]);
			//rt_matrix(pscreen, cam_specs);
			normalize(pscreen);
			//rt_matrix(origin, cam_specs);
			//emplement c2w matrix rotation and translation...
			//printf("(%.5f,%.5f,%.5f) ", pscreen[0], pscreen[1], pscreen[2]);
			//add the position of the camera and its orientation...
			list = *e_list;
			while (list->content != NULL)
			{
				objects = list->content;
				if (objects->type == 's')
				{
					thc = intersect(pscreen, cam_specs, objects);
					if (thc > 0)
						mlx_pp(scrn, xy[0], xy[1], 0x000000FF * thc / 40); // XXX this is not the right way to apply color...
				}
				list = list->next;
			}
		}
	}
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
