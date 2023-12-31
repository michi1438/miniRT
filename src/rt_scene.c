/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:15:14 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/04 16:41:25 by mguerga          ###   ########.fr       */
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
	t_elem	*cam;

	cam = findcam(e_list);
	xy[1] = -1;
	while (++xy[1] < S_HEIGHT)
	{
		xy[0] = -1;
		while (++xy[0] < S_WIDTH)
		{
			pscreen[0] = ((2 * (xy[0] + 0.5) / S_WIDTH) - 1) * cam->fov * cam->sratio;
			pscreen[1] = (1 - (2 * ((xy[1] + 0.5) / S_HEIGHT))) * cam->fov;
			pscreen[2] = -1;
			normalize(pscreen);
			rt_matrix(pscreen, cam);
			cycle_objects(xy, pscreen, cam, scrn, e_list);
		}
	}
}

void	cycle_objects(int xy[2], float pscreen[3], t_elem *cam_specs, t_scData *scrn, t_list **e_list)
{
	float	inter_dist[2];
	t_list	*list;	
	t_elem	*objects;
	float	p_hit[3];

	list = *e_list;
	inter_dist[1] = FLT_MAX;
	while (list->content != NULL)
	{
		objects = list->content;
		// XXX where new elements intersection type should go... the shapes should be properly parsed before hand
		if (objects->type == 's')
		{
			inter_dist[0] = intersect_sp(pscreen, cam_specs->xyz, objects);
			if (inter_dist[0] > 0 && inter_dist[0] < inter_dist[1])
			{
				p_hit[0] = pscreen[0] * inter_dist[0] + cam_specs->xyz[0];
				p_hit[1] = pscreen[1] * inter_dist[0] + cam_specs->xyz[1];
				p_hit[2] = pscreen[2] * inter_dist[0] + cam_specs->xyz[2];
				mlx_pp(scrn, xy[0], xy[1], mix_color(objects, e_list, p_hit));
				inter_dist[1] = inter_dist[0];
			}
		}
		list = list->next;
	}
}

int	cycle_shadow(float n_vec[3], float orig_xyz[3], t_list **e_list, float lentolight)
{
	float	inter_dist[2];
	t_list	*list;	
	t_elem	*objects;

	list = *e_list;
	inter_dist[0] = FLT_MAX;
	while (list->content != NULL)
	{
		objects = list->content;
		inter_dist[1] = intersect_sp(n_vec, orig_xyz, objects);
		// XXX where new elements intersection type should go also for the second ray shadow...
		if (objects->type == 's' && objects->status == 0 && inter_dist[1] > 0)
			inter_dist[0] = inter_dist[1];
		list = list->next;
	}
	if (inter_dist[0] < lentolight)
		return (0);
	else
		return (1);
}
