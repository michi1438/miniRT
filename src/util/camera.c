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

t_camera	camera_create(float eye_canv_dist, float screen_width, float screen_height)
{
	t_camera	res;

	res.canvas_width = screen_width;
	res.canvas_height = screen_height;
	res.eye = v3(0, 0, 0);
	res.A = v3(-screen_width / 2, screen_height / 2, -eye_canv_dist);
	res.B = v3(screen_width / 2, screen_height / 2, -eye_canv_dist);
	res.C = v3(-screen_width / 2, -screen_height / 2, -eye_canv_dist);
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
	return (plane_(camera.A, camera.B, camera.C));
}

vec	camera_get_center(t_camera camera)
{
	return (v3_add(v3_add(camera.A, v3_scale(camera_get_AB(camera), 0.5)),
				   v3_scale(camera_get_AC(camera), 0.5)));
}