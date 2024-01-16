/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_v	modify_color_intensity(t_v color, float scalar)
{
	t_v	res;

	res = v3_scale(color, scalar);
	res.x = clamp(res.x, 0, 255);
	res.y = clamp(res.y, 0, 255);
	res.z = clamp(res.z, 0, 255);
	return (res);
}

/* Takes an intensity from 0 to 1 and returns a
 * corresponding v3 white light color */
t_v	intensity_to_color(float intensity)
{
	float	mult;

	mult = clamp(intensity, 0, 1);
	return (v3(255 * mult, 255 * mult, 255 * mult));
}

int	same_sign(float a, float b)
{
	return ((a >= 0 && b >= 0) || (a <= 0 && b <= 0));
}

t_plane	plane_c(t_v p1, t_v p2, t_v p3)
{
	t_plane	res;

	res.p1 = p1;
	res.p2 = p2;
	res.p3 = p3;
	return (res);
}

t_v	plane_normal(t_plane plane)
{
	return (v3_norm(v3_cross(v3_sub(plane.p2, plane.p1),
				v3_sub(plane.p3, plane.p1))));
}
