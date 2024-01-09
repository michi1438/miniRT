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
	int	starting_id;

	starting_id ++;
	return (starting_id);
}

t_item	create_item(enum e_ObjectType type, vec pos, vec scale, vec color)
{
	t_item	res;

	res.type = type;
	res.pos = pos;
	res.scale = scale;
	res.color = color;
	res.specular = -1;
	res.z_ref_point = v3_add(v3(0, 1, 0), pos);
	res.id = get_id();
}

vec	item_get_axis(t_item item)
{
	return (v3_norm(v3_sub(item.z_ref_point, item.pos)));
}

void	item_draw_axes(t_item item)
{
	vec	z_axis;
	t_plane	plane;
	vec	y_axis;
	vec	x_axis;
	
	z_axis = v3_scale(item_get_axis(item), 0.5);
	plane = plane_from_normal(item.pos, z_axis);
	y_axis = v3_scale(v3_norm(v3_sub(plane.p2, item.pos)), 0.5);
	x_axis = v3_scale(v3_norm(v3_sub(plane.p3, item.pos)), 0.5);
	draw_segment(item.pos, v3_add(item.pos, z_axis), BLUE);
	draw_segment(item.pos, v3_add(item.pos, y_axis), GREEN);
	draw_segment(item.pos, v3_add(item.pos, x_axis), RED);
}

unsigned int	item_color_hex(t_item item)
{
	return (rgb_to_hex(item.color.x, item.color.y, item.color.z));
}
