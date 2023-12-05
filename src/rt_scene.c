/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:15:14 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/04 17:44:09 by mguerga          ###   ########.fr       */
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
	t_elem	*cam_specs;
	t_elem	*objects;
	t_list	*list;	

	cam_specs = findcam(e_list);
	xy[1] = -1;
	while (++xy[1] < S_HEIGHT)
	{
		xy[0] = -1;
		while (++xy[0] < S_WIDTH)
		{
			pscreen[0] = ((2 * (xy[0] + 0.5) / S_WIDTH) - 1) * cam_specs->fov * cam_specs->sratio;
			pscreen[1] = (1 - (2 * ((xy[1] + 0.5) / S_HEIGHT))) * cam_specs->fov;
			pscreen[2] = -1;
			normalize(pscreen); //normalize before rotation why ???
			rt_matrix(pscreen, cam_specs);
			//printf("(%.5f,%.5f,%.5f) ", pscreen[0], pscreen[1], pscreen[2]);
			list = *e_list;
			while (list->content != NULL)
			{
				objects = list->content;
				if (objects->type == 's')
				{
					thc = intersect(pscreen, cam_specs, objects);
					if (thc > 0)
						mlx_pp(scrn, xy[0], xy[1], 0x000000FF * thc / objects->radius);
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
