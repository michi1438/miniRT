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

/*
 function rgbToHexV3(v) {
		return ("#" + (1 << 24 | v.x << 16 | v.y << 8 | v.z).toString(16).slice(1));
	}
 * */
int	vec_color_to_int(vec color)
{
	return (((int)color.x << 16) | ((int)color.y << 8) | (int)color.z);
}

void	draw_line(t_scData *scrn, vec p1, vec p2, vec color)
{
	draw_line_dda(scrn, p1, p2, vec_color_to_int(color));
}

void	draw_square(t_scData *scrn, vec pos, float size, vec color)
{
	int	clr;
	int	i;
	int	j;

	clr = vec_color_to_int(color);
	i = (int)pos.y;
	while (i < (int)size)
	{
		j = (int)pos.x;
		while (j < (int)size)
		{
			mlx_pp(scrn, j, i, clr);
			j ++;
		}
		i ++;
	}
}

void	draw_vect(t_scData *scrn, vec v, vec color)
{
	float	radius;

	radius = 5;
	if (v3_is_null(v)) {
		return ;
	}
	v.x -= radius / 2;
	v.y -= radius / 2;
	draw_square(scrn, v, radius, color);
}

void	connect_points(t_scData *scrn, vec p1, vec p2, t_item item)
{
	if (v3_is_null(p1) || v3_is_null(p2))
	{
		return ;
	}
	draw_vect(scrn, p1, item.color);
	draw_vect(scrn, p2, item.color);
	draw_line(scrn, p1, p2, item.color);
}