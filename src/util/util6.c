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

t_intsc	intersection(t_v pos, t_v normal, t_line ray, t_item *item)
{
	t_intsc	res;

	res.pos = pos;
	res.normal = normal;
	res.ray = ray;
	res.item = item;
	return (res);
}

t_v	mp_pto_phys(t_camra camera, t_v point,
				float ph_wdth, float ph_hght)
{
	float	x_ratio;
	float	y_ratio;
	t_v		rel;

	if (v3_is_null(point))
		return (v3_null());
	x_ratio = ph_wdth / camera.canvas_width;
	y_ratio = ph_hght / camera.canvas_height;
	rel = get_point_canvas_rel(camera, point);
	return (v3(rel.x * x_ratio, rel.y * y_ratio, 0));
}

t_v	mp_phys_cam(t_camra camera, t_v point,
				float ph_wdth, float ph_hght)
{
	float	x_ratio;
	float	y_ratio;
	float	new_x;
	float	new_y;

	if (v3_is_null(point))
		return (v3_null());
	x_ratio = camera.canvas_width / ph_wdth;
	y_ratio = camera.canvas_height / ph_hght;
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
