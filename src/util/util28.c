/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util28.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/17 11:08:31 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_intsc	ray_intersection(t_line ray, t_item *object)
{
	if (object->type == Plane)
		return (intersect_ray_plane_item(ray, object));
	else if (object->type == Sphere)
		return (intersect_ray_sphere(ray, object));
	else if (object->type == Cube)
		return (intersect_ray_cube(ray, object));
	else if (object->type == Pyramid)
		return (intersect_ray_pyramid(ray, object));
	else if (object->type == Cylinder)
		return (intersect_ray_cylinder(ray, object));
	return (int_null());
}

t_line	gen_single_ray(t_camra camera, t_terms ts, double i, double j)
{
	return (line_c(camera.eye, v3_add(v3_add(camera.a,
					v3_scale(ts.x_axis, (float)i)),
				v3_scale(ts.y_axis, (float)j))));
}

void	intsct_cube2(t_terms *ts, t_line ray,
				t_v cube_squares[6][4], int i)
{
	if (point_inside_square(get_vec4(cube_squares[i][0], cube_squares[i][1],
		cube_squares[i][2], cube_squares[i][3]), ts->inter2.pos))
	{
		ts->dist_ = v3_len(v3_sub(ts->inter2.pos, ray.p1));
		if (int_is_null(ts->inter) || ts->dist_ < ts->dist)
		{
			ts->inter = ts->inter2;
			ts->dist = ts->dist_;
		}
	}
}

void	g_intsc_pln2(t_plane *nearest_plane,
				t_v sq[6][4], int i, t_terms *ts)
{
	*nearest_plane = plane_c(sq[i][0], sq[i][1], sq[i][2]);
	ts->dist = ts->dist_;
	ts->a = 1;
}

void	cast_ray2(t_terms ts, t_rtdata data)
{
	ts.point = mp_pto_phys(data.camera,
			ts.inter.ray.p2, S_WIDTH, S_HEIGHT);
	ts.light_color = compute_lighting(data, ts.inter, data.lights);
	ts.specular_color = modify_color_intensity(compute_specular(data,
				ts.inter, data.lights), SPECULAR);
	ts.diffuse_color = mult_colors(get_item_color(ts.inter), ts.light_color);
	ts.color = add_colors(ts.diffuse_color, ts.specular_color);
	mlx_pp(data.scrn, ts.point.x, ts.point.y, vec_color_to_int(ts.color));
}
