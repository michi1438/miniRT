/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_camra	camera_c(t_v pos, float eye_canv_dist, float fov, t_elem el)
{
	t_camra		res;
	t_v			move_vec;

	res.canvas_width = 2 * eye_canv_dist * tanf(degree_to_radian(fov / 2));
	res.canvas_height = S_HEIGHT / (S_WIDTH / res.canvas_width);
	res.eye = pos;
	move_vec = v3_sub(pos, v3(0, 0, 0));
	res.a = v3_add(move_vec, v3(-res.canvas_width
				/ 2, res.canvas_height / 2, -eye_canv_dist));
	res.b = v3_add(move_vec, v3(res.canvas_width
				/ 2, res.canvas_height / 2, -eye_canv_dist));
	res.c = v3_add(move_vec, v3(-res.canvas_width
				/ 2, -res.canvas_height / 2, -eye_canv_dist));
	camera_rotate(&res, Up, el.norm_xyz[0]);
	camera_rotate(&res, Right, el.norm_xyz[1]);
	return (res);
}

t_v	camera_get_ac(t_camra camera)
{
	return (v3_sub(camera.c, camera.a));
}

t_v	camera_get_ab(t_camra camera)
{
	return (v3_sub(camera.b, camera.a));
}

t_plane	camera_get_canvas_plane(t_camra camera)
{
	return (plane_c(camera.a, camera.b, camera.c));
}

t_v	camera_get_center(t_camra camera)
{
	return (v3_add(v3_add(camera.a, v3_scale(camera_get_ab(camera), 0.5)),
			v3_scale(camera_get_ac(camera), 0.5)));
}
