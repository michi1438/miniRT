/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util11.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

void	draw_cube_mappings(t_scData *scrn, t_v mappings[34], t_item item)
{
	connect_points(scrn, mappings[0], mappings[1], item);
	connect_points(scrn, mappings[1], mappings[2], item);
	connect_points(scrn, mappings[2], mappings[3], item);
	connect_points(scrn, mappings[3], mappings[0], item);
	connect_points(scrn, mappings[0], mappings[4], item);
	connect_points(scrn, mappings[1], mappings[5], item);
	connect_points(scrn, mappings[2], mappings[6], item);
	connect_points(scrn, mappings[3], mappings[7], item);
	connect_points(scrn, mappings[4], mappings[5], item);
	connect_points(scrn, mappings[5], mappings[6], item);
	connect_points(scrn, mappings[6], mappings[7], item);
	connect_points(scrn, mappings[7], mappings[4], item);
}

void	draw_pyramid_mappings(t_scData *scrn, t_v mappings[34], t_item item)
{
	connect_points(scrn, mappings[0], mappings[1], item);
	connect_points(scrn, mappings[0], mappings[2], item);
	connect_points(scrn, mappings[0], mappings[3], item);
	connect_points(scrn, mappings[0], mappings[4], item);
	connect_points(scrn, mappings[1], mappings[2], item);
	connect_points(scrn, mappings[2], mappings[3], item);
	connect_points(scrn, mappings[3], mappings[4], item);
	connect_points(scrn, mappings[4], mappings[1], item);
}

/* scale.y and scale.z are hardcoded to 8 and 4 */
void	draw_sphere_mappings(t_scData *scrn, t_v mappings[34], t_item item)
{
	int	i;
	int	j;
	t_v	top_point;
	t_v	bottom_point;

	top_point = mappings[item.vertices_len - 2];
	bottom_point = mappings[item.vertices_len - 1];
	i = 0;
	while (i < 8)
	{
		connect_points(scrn, top_point, mappings[i * 4], item);
		connect_points(scrn, bottom_point, mappings[i * 4 + 4 - 1], item);
		j = 0;
		while (j < 4)
		{
			connect_points(scrn, mappings[i * 4 + j],
				mappings[i * 4 + j + 1], item);
			j ++;
		}
		i ++;
	}
}

void	draw_cylinder_mappings(t_scData *scrn, t_v mappings[34], t_item item)
{
	int	i;

	i = 0;
	while (i < item.vertices_len / 2 - 1)
	{
		connect_points(scrn, mappings[i], mappings[i + 1], item);
		i ++;
	}
	connect_points(scrn, mappings[item.vertices_len / 2 - 1],
		mappings[0], item);
	i = item.vertices_len / 2;
	while (i < item.vertices_len - 1)
	{
		connect_points(scrn, mappings[i], mappings[i + 1], item);
		i ++;
	}
	connect_points(scrn, mappings[item.vertices_len - 1],
		mappings[item.vertices_len / 2], item);
	i = 0;
	while (i < item.vertices_len / 2)
	{
		connect_points(scrn, mappings[i],
			mappings[i + item.vertices_len / 2], item);
		i ++;
	}
}
