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

void	fill_screen(t_scData *scrn, vec color)
{
	int	clr;
	int	i;
	int	j;

	clr = vec_color_to_int(color);
	i = 0;
	while (i < S_WIDTH)
	{
		j = 0;
		while (j < S_HEIGHT)
		{
			mlx_pp(scrn, i, j, clr);
			j ++;
		}
		i ++;
	}
}

void	draw_segment(t_rtdata data, vec p1, vec p2, vec color)
{
	p1 = map_point_to_physical(data.camera, project_point(p1, data.camera), S_WIDTH, S_HEIGHT);
	if (v3_is_null(p1)) {
		return ;
	}
	p2 = map_point_to_physical(data.camera, project_point(p2, data.camera), S_WIDTH, S_HEIGHT);
	if (v3_is_null(p2)) {
		return ;
	}
	draw_vect(data.scrn, p1, color);
	draw_vect(data.scrn, p2, color);
	draw_line(data.scrn, p1, p2, color);
}

void	add_item(t_item item)
{
	//items.push(item); TODO
}

void	animate(t_rtdata data)
{
	t_list	*list;
	static double	iter;

	list = data.items;
	while (list != NULL)
	{
		rotate_item(list, v3_scale(v3(1, 2, 4), ROT_SPEED));
		iter += 0.05f;
		iter = fmod(iter, M_PI);
		list = list->next;
	}
	draw(data);
	list = data.items;
	while (list != NULL)
	{
		item_draw_axes(data, *((t_item *)(list->content)));
	}
}

void	draw(t_rtdata data)
{
	t_list	*list;

	fill_screen(data.scrn, v3(0, 0, 0));
	list = data.items;
	while (list != NULL)
	{
		outline_item(data, *((t_item *)(list->content)));
		list = list->next;
	}
}
