/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util21.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

static void	cmpt_sp(t_light light, vec *res, t_intersection intr)
{
	vec	L;
	t_terms	ts;
	float	n_dot_l;
	vec		R;
	float	r_dot_v;

	ts.inter2 = cast_ray(line_c(light.pos, intr.pos), 0);
	if (!int_is_null(ts.inter2) && ts.inter2.item->id != intr.item->id)
	{
		if (v3_len(v3_sub(ts.inter2.pos, intr.pos)) < v3_len(v3_sub(intr.pos, light.pos))) {
			return ;
		}
	}
	L = v3_sub(light.pos, intr.pos);
	n_dot_l = v3_dot(intr.normal, L);

	R = v3_sub(v3_scale(intr.normal, 2 * v3_dot(intr.normal, L)), L);
	ts.V = v3_invert(v3_norm(v3_sub(intr.ray.p2, intr.ray.p1)));
	r_dot_v = v3_dot(R, ts.V);
	if (r_dot_v > 0) {
		*res = add_colors(*res, modify_color_intensity(light.color, powf(r_dot_v / (v3_len(R) * v3_len(ts.V)), intr.item->specular)));
	}
}

/* From book 'Computer Graphics from Scratch' by Gabriel Gambetta */
vec	compute_specular(t_intersection intr, t_list *lights)
{
	vec	res;
	t_list	*list;

	if (intr.item->specular == -1)
		return (v3(0, 0, 0));
	res = v3(0, 0, 0);
	list = lights;
	while (list != NULL)
	{
		if (((t_light *)list->content)->type == Point)
			cmpt_sp(*((t_light *)list->content), &res, intr);
		list = list->next;
	}
}

/* http://raytracerchallenge.com/bonus/texture-mapping.html */
/* archive: https://archive.md/c96z4 */
vec	uv_at_chekers(vec color1, vec color2, vec checkers_wh, vec u_v)
{
	float	u2;
	float	v2;

	u2 = floorf(u_v.x * checkers_wh.x);
	v2 = floorf(u_v.y * checkers_wh.y);
	if (fmodf((u2 + v2), 2) == 0) {
		return (color1);
	} else {
		return (color2);
	}
}

vec	uv_at_image(t_image *rt_image, float u, float v)
{
	float	target_height;
	int		x;
	int		y;

	target_height = floorf(new_image_height(rt_image, rt_image->target_width));
	v = fmodf((1 - v), 1);
	x = floor(u * (rt_image->target_width - 1));
	y = floor(v * (target_height - 1));
	return (rt_image->pixels[y][x]);
}

vec	spherical_map(vec point, t_item sphere)
{
	float	u;
	float	v;

	point = v3_add(point, v3_sub(v3(0, 0, 0), sphere.pos));
	u = 1 - (atan2f(point.x, point.z) / (2 * M_PI) + 0.5);
	v = 1 - (acosf(point.y / v3_len(point))) / M_PI;
	return (v3(u, v, 0));
}
