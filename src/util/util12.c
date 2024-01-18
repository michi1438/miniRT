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

void	fill_screen(t_scData *scrn, t_v color)
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

void	draw_segment(t_rtdata data, t_v p1, t_v p2, t_v color)
{
	p1 = mp_pto_phys(data.camera,
			project_point(p1, data.camera), S_WIDTH, S_HEIGHT);
	if (v3_is_null(p1))
		return ;
	p2 = mp_pto_phys(data.camera, project_point(p2, data.camera),
			S_WIDTH, S_HEIGHT);
	if (v3_is_null(p2))
		return ;
	draw_vect(data.scrn, p1, color);
	draw_vect(data.scrn, p2, color);
	draw_line(data.scrn, p1, p2, color);
}

int	add_item(t_list **lst, t_elem *elem)
{
	t_list	*new_lst_item;
	t_v		scale;
	t_item	*item;

	if (elem->type == 's')
		scale = v3(elem->radius, 0, 0);
	else if (elem->type == 'p')
		scale = v3(elem->norm_xyz[0], elem->norm_xyz[1], elem->norm_xyz[2]);
	else if (elem->type == 'b')
		scale = v3(elem->height, elem->height, elem->height);
	else
		scale = v3(elem->radius, elem->height, elem->radius);
	item = create_item(get_item_type(elem), tuple(v3(elem->xyz[0],
					elem->xyz[1], elem->xyz[2]), scale), tuple(
				v3(elem->norm_xyz[0], elem->norm_xyz[1], elem->norm_xyz[2]),
				v3(elem->rgb[0], elem->rgb[1], elem->rgb[2])),
			floatint(elem->specular, elem->is_checker));
	if (!item)
		return (0);
	new_lst_item = ft_lstnew(item);
	if (!new_lst_item)
		return (free(item), 0);
	ft_lstadd_back(lst, new_lst_item);
	return (1);
}

void	animate(t_rtdata data)
{
	t_list			*list;
	static double	iter;

	list = data.items;
	while (list != NULL)
	{
		rotate_item(list->content, v3_scale(v3(1, 2, 4), ROT_SPEED));
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
	mlx_put_image_to_window(data.scrn->mlx, data.scrn->win,
		data.scrn->img, 0, 0);
}
