/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util11.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

vec	color_from_int(int color)
{
	vec	res;

	res.x = (color << 8) / 16777216;
	res.y = (color << 16) / 16777216;
	res.z = (color << 24) / 16777216;
	return (res);
}

/* scale.x: radius ; scale.y: amount of vertices around axis y ; scale.z: amount of vertices around axis z */
/* scale.y and scale.z are hardcoded to 8 and 4 */
void	sphere_vertices(vec pos, vec scale, t_item *item)
{
	t_item	it;
	vec		top_point;
	int		i;
	int		j;

	it = *item;
	top_point = v3_add(pos, v3(0, scale.x / 2, 0));
	i = 1;
	while (i <= (int)scale.y)
	{
		j = 1;
		while (j <= (int)scale.x)
		{
			it.vertices[(i - 1) + (j - 1)] = rotate_point(rotate_point(top_point, v3(0, 0, j * M_PI / (4 + 1)), pos), v3(0, i * M_PI / (8 / 2), 0), pos);
			j ++;
		}
		i ++;
	}
	it.vertices[32] = top_point;
	it.vertices[33] = v3_add(pos, v3(0, -scale.x / 2, 0));
	it.vertices_len = 34;
}

void	pyramid_vertices(vec pos, vec scale, t_item *item)
{
	t_item	it;

	it = *item;
	it.vertices[0] = v3_add(pos, v3(0, scale.y / 2, 0));
	it.vertices[1] = v3_add(pos,v3_add(v3(-scale.x / 2, 0, 0),v3_add(v3(0, -scale.y / 2, 0),v3(0, 0, -scale.z / 2))));
	it.vertices[2] = v3_add(pos,v3_add(v3(scale.x / 2, 0 ,0),v3_add(v3(0, -scale.y / 2, 0),v3(0, 0, -scale.z / 2))));
	it.vertices[3] = v3_add(pos,v3_add(v3(scale.x / 2, 0, 0),v3_add(v3(0, -scale.y / 2, 0),v3(0, 0, scale.z / 2))));
	it.vertices[4] = v3_add(pos,v3_add(v3(-scale.x / 2, 0, 0),v3_add(v3(0, -scale.y / 2, 0),v3(0, 0, scale.z / 2))));
	it.vertices_len = 5;
}

void	cube_vertices(vec pos, vec scale, t_item *item)
{
	t_item	it;

	it = *item;
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, scale.z / 2),v3_add(v3(0, scale.y / 2, 0),v3(-scale.x / 2, 0, 0))));
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, -scale.z / 2),v3_add(v3(0, scale.y / 2, 0),v3(-scale.x / 2, 0, 0))));
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, -scale.z / 2),v3_add(v3(0, scale.y / 2, 0),v3(scale.x / 2, 0, 0))));
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, scale.z / 2),v3_add(v3(0, scale.y / 2, 0),v3(scale.x / 2, 0, 0))));
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, scale.z / 2),v3_add(v3(0, -scale.y / 2, 0),v3(-scale.x / 2, 0, 0))));
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, -scale.z / 2),v3_add(v3(0, -scale.y / 2, 0),v3(-scale.x / 2, 0, 0))));
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, -scale.z / 2),v3_add(v3(0, -scale.y / 2, 0),v3(scale.x / 2, 0, 0))));
	it.vertices[0] = v3_add(pos,v3_add(v3(0, 0, scale.z / 2),v3_add(v3(0, -scale.y / 2, 0),v3(scale.x / 2, 0, 0))));
	it.vertices_len = 8;
}

/* returns list of cube vertices */
void	cylinder_vertices(vec pos, vec scale, t_item *item)
{
	t_item	it;
	vec		first;
	vec		second;
	int		i;

	it = *item;
	first = v3_add(v3_add(pos, v3(0, -scale.y / 2, 0)), v3(scale.x / 2, 0, 0));
	i = 0;
	while (i < 10)
	{
		it.vertices[i] = rotate_point(first,v3(0, i * M_PI / (10 / 2), 0),pos);
		i ++;
	}
	second = v3_add(v3_add(pos, v3(0, scale.y / 2, 0)), v3(scale.x / 2, 0, 0));
	i = 0;
	while (i < 10)
	{
		it.vertices[i - 10] = rotate_point(second,v3(0, i * M_PI / (10 /2), 0),pos);
		i ++;
	}
	it.vertices_len = 20;
}
