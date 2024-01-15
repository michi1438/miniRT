/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util17.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

/* For plane ITEM */
t_intersection	intersect_ray_plane_item(t_line ray, t_item *plane)
{
	t_intersection	res;

	res = intersect_ray_plane(ray, plane_from_normal(plane->pos, plane->scale));
	res.item = plane;
	return (res);
}

t_intersection	intersect_ray_sphere(t_line ray, t_item *sphere)
{
	t_terms	terms;

	terms.D = v3_norm(v3_sub(ray.p2, ray.p1));
	terms.X = v3_sub(ray.p1, sphere->pos);
	terms.a = v3_dot(terms.D, terms.D);
	terms.b = 2 * v3_dot(terms.D, terms.X);
	terms.r = sphere->scale.x / 2;
	terms.c = v3_dot(terms.X, terms.X) - terms.r * terms.r;
	terms.discriminant = terms.b * terms.b - 4 * terms.a * terms.c;
	if (terms.discriminant < TOLERANCE)
		return (int_null());
	else
	{
		terms.t1 = (-terms.b + sqrt(terms.discriminant)) / (2 * terms.a);
		terms.t2 = (-terms.b - sqrt(terms.discriminant)) / (2 * terms.a);
		terms.point = v3_null();
		if (terms.t1 >= 0 && terms.t1 < terms.t2) {
			terms.point = v3_add(ray.p1, v3_scale(terms.D, terms.t1));
		} else if (terms.t2 >= 0) {
			terms.point = v3_add(ray.p1, v3_scale(terms.D, terms.t2));
		}
		if (!v3_is_null(terms.point)) {
			return (int_create(terms.point, v3_norm(v3_sub(terms.point, sphere->pos)),  ray, sphere));
		}
	}
	return (int_null());
}

int	point_inside_square(t_vecfour sqr, t_v point)
{
	t_plane	plane;
	t_v		norm;

	plane = plane_c(sqr.p1, sqr.p2, sqr.p3);
	norm = plane_normal(plane);
	if (fabs(v3_dot(v3_sub(point, sqr.p1), norm)) >= TOLERANCE) {
		return (0);
	}
	if (!same_side_of_line(line_c(sqr.p1, sqr.p2), sqr.p3, point)) {
		return (0);
	}
	if (!same_side_of_line(line_c(sqr.p2, sqr.p3), sqr.p1, point)) {
		return (0);
	}
	if (!same_side_of_line(line_c(sqr.p3, sqr.p4), sqr.p1, point)) {
		return (0);
	}
	if (!same_side_of_line(line_c(sqr.p4, sqr.p1), sqr.p3, point)) {
		return (0);
	}
	return (1);
}

void	get_cube_squares(const t_item cube, t_v square_buffer[6][4])
{
	square_buffer[0][0] = cube.vertices[0];
	square_buffer[0][1] = cube.vertices[1];
	square_buffer[0][2] = cube.vertices[2];
	square_buffer[0][3] = cube.vertices[3];
	square_buffer[1][0] = cube.vertices[1];
	square_buffer[1][1] = cube.vertices[2];
	square_buffer[1][2] = cube.vertices[6];
	square_buffer[1][3] = cube.vertices[5];
	square_buffer[2][0] = cube.vertices[2];
	square_buffer[2][1] = cube.vertices[3];
	square_buffer[2][2] = cube.vertices[7];
	square_buffer[2][3] = cube.vertices[6];
	square_buffer[3][0] = cube.vertices[0];
	square_buffer[3][1] = cube.vertices[3];
	square_buffer[3][2] = cube.vertices[7];
	square_buffer[3][3] = cube.vertices[4];
	square_buffer[4][0] = cube.vertices[0];
	square_buffer[4][1] = cube.vertices[1];
	square_buffer[4][2] = cube.vertices[5];
	square_buffer[4][3] = cube.vertices[4];
	square_buffer[5][0] = cube.vertices[7];
	square_buffer[5][1] = cube.vertices[6];
	square_buffer[5][2] = cube.vertices[5];
	square_buffer[5][3] = cube.vertices[4];
}

t_intersection	intersect_ray_cube(t_line ray, t_item *cube)
{
	t_terms	ts;
	t_v		cube_squares[6][4];
	int		i;
	t_plane	plane;

	ts.inter = int_null();
	ts.dist = 0;
	get_cube_squares(*cube, cube_squares);
	i = 0;
	while (i < 6)
	{
		plane = plane_c(cube_squares[i][0], cube_squares[i][1], cube_squares[i][2]);
		ts.inter2 = intersect_ray_plane(ray, plane);
		if (!int_is_null(ts.inter2))
		{
			if (point_inside_square(get_vecfour(cube_squares[i][0], cube_squares[i][1], cube_squares[i][2], cube_squares[i][3]), ts.inter2.pos))
			{
				ts.dist_ = v3_len(v3_sub(ts.inter2.pos, ray.p1));
				if (int_is_null(ts.inter) || ts.dist_ < ts.dist) {
					ts.inter = ts.inter2;
					ts.dist = ts.dist_;
				}
			}
		}
		i ++;
	}
	ts.inter.item = cube;
	return (ts.inter);
}
