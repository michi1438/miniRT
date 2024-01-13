/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util23.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

static vec	img_clr_plane(t_intersection intr)
{
	vec		new_pos;
	float	angle;
	vec		n_;
	vec		pixel;

	n_ = v3(0, 0, 1);
	angle = vect_angle(intr.normal, n_);
	new_pos = v3_add(v3_scale(intr.pos, cos(angle)), v3_add(v3_scale(v3_cross(intr.normal, intr.pos), sin(angle)), v3_scale(intr.normal, v3_dot(intr.normal, intr.pos) * (1 - cos(angle)))));
	if (equals_with_tolerance(intr.normal.x, 0) && equals_with_tolerance(intr.normal.y, 1) && equals_with_tolerance(intr.normal.z, 0))
	{
		new_pos = v3(intr.pos.x, intr.pos.z, 0);
	}
	new_pos.x = trunc(fmodf(new_pos.x, intr.item->image->target_width));
	if (new_pos.x < 0) {
		new_pos.x = intr.item->image->target_width + new_pos.x;
	}
	new_pos.y = trunc(fmodf(new_pos.y, new_image_height(intr.item->image, intr.item->image->target_width)));
	if (new_pos.y > 0) {
		new_pos.y = new_image_height(intr.item->image, intr.item->image->target_width) - new_pos.y;
	}
	pixel = intr.item->image->pixels[abs(floorf(new_pos.y))][abs(floorf(new_pos.x))];
	return (v3(pixel.x, pixel.y, pixel.z));
}

static vec	img_clr_sphere(t_intersection intr)
{
	vec	coords;
	vec	**new_pixels;
	t_terms	ts;
	int		x;
	int		y;

	if (intr.item->cache_width == intr.item->image->width) {
		new_pixels = intr.item->pixel_cache;
	} else {
		intr.item->cache_width = intr.item->image->width;
		new_pixels = getPixelsFromImage(*intr.item->image, intr.item->image->width);
		free_pixel_cache(intr.item->pixel_cache);
		intr.item->pixel_cache = new_pixels;
	}
	coords = cartesian_to_sphere(intr.pos, *intr.item);
	x = floorf((coords.y / (2 * M_PI)) * (intr.item->image->width - 1));
	y = floorf((coords.z / M_PI) * (new_image_height(intr.item->image, intr.item->image->width) - 1));
	return (v3(new_pixels[y][x].x, new_pixels[y][x].y, new_pixels[y][x].z));
}

static vec	img_clr_cb_pyr(t_intersection intr)
{
	t_plane	plane;
	t_terms	ts;
	vec		pixel;
	vec		x_proj;
	vec		y_proj;

	plane = get_intersection_plane(intr);
	ts.x_axis = v3_norm(v3_sub(plane.p2, plane.p1));
	ts.y_axis = v3_norm(v3_sub(plane.p3, plane.p1));
	x_proj = project_point_onto_line(line_c(plane.p1, plane.p2), intr.pos);
	ts.x_dist = v3_len(v3_sub(plane.p1, x_proj));
	y_proj = project_point_onto_line(line_c(plane.p1, plane.p3), intr.pos);
	ts.y_dist = v3_len(v3_sub(plane.p1, y_proj));
	ts.x_dist = fmodf(ts.x_dist, intr.item->image->target_width - 1);
	ts.y_dist = fmodf(ts.y_dist, new_image_height(intr.item->image, intr.item->image->target_width) - 1);
	pixel = intr.item->image->pixels[(int)floor(ts.y_dist * 1000)][(int)floor(ts.x_dist * 1000)];
	return (v3(pixel.x, pixel.y, pixel.z));
}

vec	get_item_color_image(t_intersection intr)
{
	vec	u_v;
	vec	img_color;

	if (intr.item->type == Plane) {
		return (img_clr_plane(intr));
	} else if (intr.item->type == Sphere) {
		return (img_clr_sphere(intr));
	} else if (intr.item->type == Cylinder) {
		u_v = cylindrical_map(intr.pos, *intr.item);
		img_color = uv_at_image(intr.item->image, u_v.x, u_v.y);
		return(v3(img_color.x, img_color.y, img_color.z));
	} else if (intr.item->type == Cube || intr.item->type == Pyramid) {
		return (img_clr_cb_pyr(intr));
	}
	return (v3(0, 0, 0));
}

vec	get_item_color(t_intersection intr)
{
	if (intr.item->image != NULL)
	{
		return get_item_color_image(intr);
	}
	else if (intr.item->is_checker)
	{
		return(get_item_color_checkerboard(intr));
	}
	else
	{
		return (intr.item->color);
	}
}