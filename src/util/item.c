/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

static int	get_id()
{
	static int	starting_id;

	starting_id ++;
	return (starting_id);
}

t_item	*create_item(enum e_ObjectType type, vec pos, vec scale, vec color)
{
	t_item	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->type = type;
	res->pos = pos;
	res->scale = scale;
	res->color = color;
	res->specular = -1;
	res->z_ref_point = v3_add(v3(0, 1, 0), pos);
	res->id = get_id();
	res->image = NULL;
	res->is_checker = 0;
	return (res);
}

vec	item_get_axis(t_item item)
{
	return (v3_norm(v3_sub(item.z_ref_point, item.pos)));
}

void	item_draw_axes(t_rtdata data, t_item item)
{
	vec	z_axis;
	t_plane	plane;
	vec	y_axis;
	vec	x_axis;
	
	z_axis = v3_scale(item_get_axis(item), 0.5);
	plane = plane_from_normal(item.pos, z_axis);
	y_axis = v3_scale(v3_norm(v3_sub(plane.p2, item.pos)), 0.5);
	x_axis = v3_scale(v3_norm(v3_sub(plane.p3, item.pos)), 0.5);
	draw_segment(data, item.pos, v3_add(item.pos, z_axis), color_from_int(BLUE));
	draw_segment(data, item.pos, v3_add(item.pos, y_axis), color_from_int(GREEN));
	draw_segment(data, item.pos, v3_add(item.pos, x_axis), color_from_int(RED));
}
