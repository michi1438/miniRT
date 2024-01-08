/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

vec	modify_color_intensity(vec color, float scalar)
{
	vec	res;

	res = v3_scale(color, scalar);
	res.x = clamp(res.x, 0, 255);
	res.y = clamp(res.y, 0, 255);
	res.z = clamp(res.z, 0, 255);
	return (res);
}

/* Takes an intensity from 0 to 1 and returns a corresponding v3 white light color */
vec	intensity_to_color(float intensity)
{
	float	mult;

	mult = clamp(intensity, 0, 1);
	return (v3(255 * mult, 255 * mult, 255 * mult));
}

int	same_sign(float a, float b)
{
	return ((a >= 0 && b >= 0) || (a <= 0 && b <= 0));
}

t_plane	plane(vec p1, vec p2, vec p3)
{
	t_plane	res;

	res.p1 = p1;
	res.p2 = p2;
	res.p3 = p3;
}

vec	plane_normal(t_plane plane)
{
	return(v3_norm(v3_cross(v3_sub(plane.p2, plane.p1), v3_sub(plane.p3, plane.p1))));
}
