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

t_camera	camera_c(vec pos, float eye_canv_dist, float fov)
{
	t_camera	res;


	res.canvas_width = 2 * eye_canv_dist * tanf(degree_to_radian(fov / 2));
	res.canvas_height = S_HEIGHT / (S_WIDTH / res.canvas_width);
	res.eye = pos;
	res.A = v3(-res.canvas_width / 2, res.canvas_height / 2, -eye_canv_dist);
	res.B = v3(res.canvas_width / 2, res.canvas_height / 2, -eye_canv_dist);
	res.C = v3(-res.canvas_width / 2, -res.canvas_height / 2, -eye_canv_dist);
	return (res);
}

vec	camera_get_AC(t_camera camera)
{
	return (v3_sub(camera.C, camera.A));
}

vec	camera_get_AB(t_camera camera)
{
	return (v3_sub(camera.B, camera.A));
}

t_plane	camera_get_canvas_plane(t_camera camera)
{
	return (plane_c(camera.A, camera.B, camera.C));
}

vec	camera_get_center(t_camera camera)
{
	return (v3_add(v3_add(camera.A, v3_scale(camera_get_AB(camera), 0.5)),
				   v3_scale(camera_get_AC(camera), 0.5)));
}