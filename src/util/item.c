/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/18 11:37:06 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

static int	get_id(void)
{
	static int	starting_id;

	starting_id ++;
	return (starting_id);
}

static void	set_vertices(t_item *item)
{
	if (item->type == Sphere)
		sphere_vertices(item->pos, item->scale, item);
	if (item->type == Cylinder)
		cylinder_vertices(item->pos, item->scale, item);
	if (item->type == Cube)
		cube_vertices(item->pos, item->scale, item);
	if (item->type == Pyramid)
		pyramid_vertices(item->pos, item->scale, item);
	if (item->type == Plane)
		return ;
	rotate_to_normal(item);
}

t_item	*create_item(enum e_ObjectType type, t_v3tpl pos_scale,
		t_v3tpl axe_color, t_fitpl sp_ch)
{
	t_item	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->type = type;
	res->pos = pos_scale.v1;
	res->scale = pos_scale.v2;
	res->color = axe_color.v2;
	res->specular = sp_ch.f;
	if (type == Sphere)
		axe_color.v1 = v3(0, 1, 0);
	res->z_ref_point = v3_add(axe_color.v1, pos_scale.v1);
	res->id = get_id();
	res->image = NULL;
	res->is_checker = sp_ch.i;
	set_vertices(res);
	return (res);
}

t_v	item_get_axis(t_item item)
{
	return (v3_norm(v3_sub(item.z_ref_point, item.pos)));
}

void	item_draw_axes(t_rtdata data, t_item item)
{
	t_v		z_axis;
	t_plane	plane;
	t_v		y_axis;
	t_v		x_axis;

	z_axis = v3_scale(item_get_axis(item), 0.5);
	plane = plane_from_normal(item.pos, z_axis);
	y_axis = v3_scale(v3_norm(v3_sub(plane.p2, item.pos)), 0.5);
	x_axis = v3_scale(v3_norm(v3_sub(plane.p3, item.pos)), 0.5);
	draw_segment(data, item.pos, v3_add(item.pos, z_axis),
		color_from_int(BLUE));
	draw_segment(data, item.pos, v3_add(item.pos, y_axis),
		color_from_int(GREEN));
	draw_segment(data, item.pos, v3_add(item.pos, x_axis), color_from_int(RED));
}
