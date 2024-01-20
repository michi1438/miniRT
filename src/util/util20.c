/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util19.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

static void	test_cap1(t_terms *ts, t_item cylinder, t_line ray)
{
	t_plane	plane;
	t_intsc	pint;

	plane = plane_c(cylinder.vertices[cylinder.vertices_len - 1],
			cylinder.vertices[cylinder.vertices_len - 2],
			cylinder.vertices[cylinder.vertices_len - 3]);
	pint = intersect_ray_plane(ray, plane);
	if (!int_is_null(pint))
	{
		if (v3_len(v3_sub(ts->c_, pint.pos)) <= cylinder.scale.x / 2)
		{
			ts->dist_ = v3_len(v3_sub(pint.pos, ray.p1));
			if (int_is_null(ts->inter) || ts->dist_ < ts->dist)
			{
				ts->inter = pint;
				ts->dist = ts->dist_;
			}
		}
	}
}

static void	test_cap2(t_terms *ts, t_item cylinder, t_line ray)
{
	t_plane	plane;
	t_intsc	pint;

	plane = plane_c(cylinder.vertices[0],
			cylinder.vertices[1], cylinder.vertices[2]);
	pint = intersect_ray_plane(ray, plane);
	if (!int_is_null(pint))
	{
		if (v3_len(v3_sub(get_cylinder_bottom(cylinder),
					pint.pos)) <= cylinder.scale.x / 2)
		{
			ts->dist_ = v3_len(v3_sub(pint.pos, ray.p1));
			if (int_is_null(ts->inter) || ts->dist_ < ts->dist)
			{
				ts->inter = pint;
				ts->dist = ts->dist_;
			}
		}
	}
}

static int	cyl1(t_terms *ts, t_item cylinder)
{
	ts->t = FLT_MAX;
	ts->a = v3_dot(ts->d, ts->d) - powf(v3_dot(ts->d, ts->v), 2);
	ts->b = 2 * (v3_dot(ts->d, ts->x_) - v3_dot(ts->d, ts->v)
			* v3_dot(ts->x_, ts->v));
	ts->c = v3_dot(ts->x_, ts->x_) - powf(v3_dot(ts->x_, ts->v), 2)
		- cylinder.scale.x / 2 * cylinder.scale.x / 2;
	ts->discriminant = ts->b * ts->b - 4 * ts->a * ts->c;
	if (ts->discriminant < 0)
	{
		return (0);
	}
	ts->d1 = (-ts->b + sqrt(ts->discriminant)) / (2 * ts->a);
	ts->d2 = (-ts->b - sqrt(ts->discriminant)) / (2 * ts->a);
	ts->m1 = v3_dot(ts->d, ts->v) * ts->d1 + v3_dot(ts->x_, ts->v);
	ts->m2 = v3_dot(ts->d, ts->v) * ts->d2 + v3_dot(ts->x_, ts->v);
	return (1);
}

static int	cyl2(t_terms *ts, t_item cylinder)
{
	if (ts->d2 > ts->d1)
	{
		ts->tmp = ts->d1;
		ts->d1 = ts->d2;
		ts->d2 = ts->tmp;
		ts->tmp = ts->m1;
		ts->m1 = ts->m2;
		ts->m2 = ts->tmp;
	}
	if (ts->m2 < cylinder.scale.y && ts->m2 > 0)
	{
		if (ts->d2 < 0)
		{
			return (0);
		}
		ts->t = ts->d2;
	}
	return (1);
}

t_intsc	intersect_ray_cylinder(t_line ray, t_item *cylinder)
{
	t_terms	ts;

	ts.inter = int_null();
	ts.dist = 0;
	ts.d = v3_norm(v3_sub(ray.p2, ray.p1));
	ts.v = (v3_norm(v3_sub(cylinder->vertices[0],
					cylinder->vertices[cylinder->vertices_len / 2])));
	ts.c_ = get_cylinder_top(*cylinder);
	ts.x_ = v3_sub(ray.p1, ts.c_);
	test_cap1(&ts, *cylinder, ray);
	test_cap2(&ts, *cylinder, ray);
	if (!cyl1(&ts, *cylinder))
		return (ts.inter);
	if (!cyl2(&ts, *cylinder))
		return (ts.inter);
	if (ts.t != FLT_MAX && ts.t >= 0 && (int_is_null(ts.inter)
			|| v3_len(v3_scale(ts.d, ts.t)) < ts.dist))
	{
		ts.point = v3_add(ray.p1, v3_scale(ts.d, ts.t));
		ts.normal = v3_norm(v3_sub(v3_sub(ts.point, ts.c_),
					v3_scale(ts.v, ts.m2)));
		return (int_create(ts.point, ts.normal, ray, cylinder));
	}
	ts.inter.item = cylinder;
	return (ts.inter);
}
