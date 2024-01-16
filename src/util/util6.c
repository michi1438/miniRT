/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_light	light(enum e_LightType type, t_v color, t_v pos)
{
	t_light	res;

	res.type = type;
	res.color = color;
	res.pos = pos;
	return (res);
}

t_intersection	intersection(t_v pos, t_v normal, t_line ray, t_item *item)
{
	t_intersection	res;

	res.pos = pos;
	res.normal = normal;
	res.ray = ray;
	res.item = item;
	return (res);
}

t_v	map_point_to_physical(t_camera camera, t_v point,
				float physical_width, float physical_height)
{
	float	x_ratio;
	float	y_ratio;
	t_v		rel;

	if (v3_is_null(point))
		return (v3_null());
	x_ratio = physical_width / camera.canvas_width;
	y_ratio = physical_height / camera.canvas_height;
	rel = get_point_canvas_rel(camera, point);
	return (v3(rel.x * x_ratio, rel.y * y_ratio, 0));
}

t_v	map_physical_to_camera(t_camera camera, t_v point,
				float physical_width, float physical_height)
{
	float	x_ratio;
	float	y_ratio;
	float	new_x;
	float	new_y;

	if (v3_is_null(point))
		return (v3_null());
	x_ratio = camera.canvas_width / physical_width;
	y_ratio = camera.canvas_height / physical_height;
	point.x *= x_ratio;
	point.y *= y_ratio;
	new_x = v3_add(camera.A,
			v3_scale(v3_norm(camera_get_ab(camera)), point.x)).x;
	new_y = v3_add(camera.A,
			v3_scale(v3_norm(camera_get_ac(camera)), point.y)).y;
	return (v3(new_x, new_y, camera.A.z));
}

t_v	v3_scale(t_v a, float scale)
{
	return (v3(a.x * scale, a.y * scale, a.z * scale));
}