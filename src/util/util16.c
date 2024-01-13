/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util16.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

void	draw_mappings(t_rtdata data, t_item  item, vec mappings[34])
{
	if (item.type == Cube)
		draw_cube_mappings(data.scrn, mappings, item);
	else if (item.type == Pyramid)
		draw_pyramid_mappings(data.scrn, mappings, item);
	else if (item.type == Sphere)
		draw_sphere_mappings(data.scrn, mappings, item);
	else if (item.type == Cylinder)
		draw_cylinder_mappings(data.scrn, mappings, item);
}

t_line	*gen_rays(t_camera camera, double resolution)
{
	vec	x_axis;
	vec	y_axis;
	int	i;
	int	j;
	int	k;
	t_line	*res;

	res = malloc(sizeof(*res) * S_WIDTH * S_HEIGHT);
	if (!res)
		return (NULL);
	x_axis = v3_norm(camera_get_AB(camera));
	y_axis = v3_norm(camera_get_AC(camera));
	i = 0;
	k = 0;
	while (i < S_WIDTH)
	{
		j = 0;
		while (j < S_HEIGHT)
		{
			res[k] = line_c(camera.eye, v3_add(v3_add(camera.A, v3_scale(x_axis, (float)i)), v3_scale(y_axis, (float)j)));
			k ++;
			j ++;
		}
		i += (int)resolution;
	}
	return (res);
}

t_intersection	int_null()
{
	t_intersection t;

	t.pos = v3_null();
	return (t);
}

int	int_is_null(t_intersection intersection)
{
	return (v3_is_null(intersection.pos));
}

t_intersection	intersect_ray_plane(t_line ray, t_plane plane)
{
	t_terms	terms;

	terms.D = v3_norm(v3_sub(ray.p2, ray.p1));
	terms.X = v3_sub(ray.p1, plane.p1);
	terms.N = plane_normal(plane);
	terms.d_v = v3_dot(terms.D, terms.N);
	terms.x_v = v3_dot(terms.X, terms.N);
	if (terms.d_v == (float)TOLERANCE || ((terms.x_v < TOLERANCE) == (terms.d_v < TOLERANCE)))
	{
		return (int_null());
	}
	terms.t = - terms.x_v / terms.d_v;
	terms.intr = v3_add(ray.p1, v3_scale(terms.D, terms.t));
	if (terms.d_v <= TOLERANCE) {
		terms.normal = terms.N;
	} else {
		terms.normal = v3_invert(terms.N);
	}
	return (int_create(terms.intr, terms.normal, ray, NULL));
}
