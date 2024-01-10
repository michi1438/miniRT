/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util11.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

void	move_item(t_item *item, vec pos)
{
	t_item	it;
	int		i;

	it = *item;
	it.pos = v3_add(it.pos, pos);
	i = 0;
	while (i < it.vertices_len)
	{
		it.vertices[i] = v3_add(it.vertices[i], pos);
		i ++;
	}
}

void	move_item_to(t_item *item, vec pos)
{
	move_item(item, v3_sub(pos, item->pos));
}

void	rotate_item(t_item *item, vec rot)
{
	int	i;
	t_item	it;

	it = *item;
	if (item->type == Plane) {
		return ;
	}
	i = 0;
	while (i < item->vertices_len)
	{
		it.vertices[i] = rotate_point(it.vertices[i], rot, it.pos);
		i ++;
	}
	it.z_ref_point = rotate_point(it.z_ref_point, rot, it.pos);
}

static void	scale_item(t_item *item, vec scale)
{
	/*vec	rot_backup;
	t_item	it;

	it = *item;
	rot_backup = v3(it.rot.x, item.rot.y, item.rot.z);
	rotate_item(item, v3_invert(item.rot));
	item.scale = v3(scale.x, scale.y, scale.z);
	item.vertices = item.vertex_func(item.pos, item.scale);
	rotate_item(item, rot_backup);*/
	// optional TODO
}

void	outline_item(t_rtdata data, t_item item)
{
	vec	mappings[34];
	int	i;

	if (item.type == Plane)
	{
		return ;
	}
	i = 0;
	while (i < item.vertices_len)
	{
		mappings[i] = map_point_to_physical(data.camera, project_point(item.vertices[i], data.camera), S_WIDTH, S_HEIGHT);
		i ++;
	}
	draw_mappings(data, item, mappings);
}