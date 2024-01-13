/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util26.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

vec	get_item_color_checkerboard(t_intersection intr)
{
	vec	inverse_color;
	t_plane	nearest_plane;
	vec		u_v;

	inverse_color = v3_sub(color_from_int(WHITE), intr.item->color);
	if (intr.item->type == Plane) {
		return (checker_pixel_for_plane(tuple(intr.pos, intr.item->pos), intr.item->scale, 2, tuple(inverse_color, intr.item->color)));
	} else if (intr.item->type == Sphere) {
		u_v = spherical_map(intr.pos, *intr.item);
		return(uv_at_chekers(intr.item->color, inverse_color, v3(32, 8, 0), u_v));
	} else if (intr.item->type == Cylinder) {
		u_v = cylindrical_map(intr.pos, *intr.item);
		return(uv_at_chekers(intr.item->color, inverse_color, v3(32, 8, 0), u_v));
	} else if (intr.item->type == Cube) {
		nearest_plane = get_intersection_plane(intr);
		return (checker_pixel_for_plane(tuple(intr.pos, nearest_plane.p2), plane_normal(nearest_plane), intr.item->scale.x / 10, tuple(inverse_color, intr.item->color)));
	} else if (intr.item->type == Pyramid) {
		nearest_plane = get_intersection_plane(intr);
		return (checker_pixel_for_plane(tuple(intr.pos, nearest_plane.p2), plane_normal(nearest_plane), intr.item->scale.x / 10, tuple(inverse_color, intr.item->color)));
	} else {

		return (intr.item->color);
	}
}

function cast_ray(ray, do_draw = true) {
	let intersection = null;
	let dist = 0;
	for (var j = 0; j < items.length; j++) {
		let int_ = ray_intersection(ray, items[j]);
		if (int_ != null) {
			let dist_ = v3_len(v3_sub(int_.pos, ray.p1));
			if (intersection == null || dist_ < dist) {
				intersection = int_;
				dist = dist_;
			}
		}
	}
	if (do_draw && intersection != null) {
		let mapped_point = map_point_to_physical(camera, intersection.ray.p2, htmlcanvas.width, htmlcanvas.height);
		let light_color = compute_lighting(intersection);
		let specular_coefficient = 0.7;
		let specular_color = modify_color_intensity(compute_specular(intersection), specular_coefficient);
		let color;
		if (1) {
			let diffuse_color = mult_colors(get_item_color(intersection), light_color);
			color = rgbToHexV3(add_colors(diffuse_color, specular_color)); //rgbToHexV3(mult_colors(get_item_color(intersection), light_color));
		} else {
			color = rgbToHexV3(get_item_color(intersection));
		}
		draw_circle(mapped_pointr.x, mapped_pointr.y, 1, color, 2);
	}
	return (intersection);
}

function raytrace() {
	if (parseFloat(document.getElementById('rt_precision').value < TOLERANCE)) {
		return ;
	}

	console.log("raytracing...");
	let rays = gen_rays(camera, parseFloat(document.getElementById('rt_precision').value));

	console.log(rays.length)
	console.log(rays);
	for (var i = 0; i < rays.length; i++) {
		cast_ray(rays[i]);
	}
	console.log("done!");
	draw_lights();
}

function cast_ray_for_screen_coords(x, y) {
	console.log(`casting for ${x}, ${y}`);
	let mapped = map_physical_to_camera(camera, v3(x, y), htmlcanvas.width, htmlcanvas.height);
	cast_ray(new Line(camera.eye, mapped), true);
}