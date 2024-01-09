/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

vec	v3_sub(vec a, vec b)
{
	return (v3(a.x - b.x, a.y - b.y, a.z - b.z));
}

vec	v3_clone(vec v)
{
	return v3(v.x, v.y, v.z);
}

vec	v3_null()
{
	return (v3(FLT_MAX, FLT_MAX, FLT_MAX));
}

int	v3_is_null(vec v)
{
	return (v.x == FLT_MAX && v.y == FLT_MAX && v.z == FLT_MAX);
}

/* projects a point on the camera plane */
/* returns v3(FT_MAX) if the line between eye and point doesn't intersect plane or is behind screen */
vec	project_point(vec point, t_camera camera)
{
	t_line	line_;
	t_plane	canvas;
	vec	intersection_;

	if (!same_side_of_plane(plane_c(camera.eye, camera.A, camera.C), camera.B, point)) {
		return (v3_null());
	}
	if (!same_side_of_plane(plane_c(camera.eye, camera.B, camera_get_D(camera)), camera.A, point)) {
		return (v3_null());
	}
	if (!same_side_of_plane(plane_c(camera.eye, camera.C, camera_get_D(camera)), camera.A, point)) {
		return (v3_null());
	}
	if (!same_side_of_plane(plane_c(camera.eye, camera.A, camera.B), camera.C, point)) {
		return (v3_null());
	}
	line_ = line_c(camera.eye, point);
	canvas = camera_get_canvas_plane(camera);
	intersection_ = intersect(line_, canvas);
	if (v3_is_null(intersection_)) {
		return (v3_null());
	}
	return (intersection_);
}