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

void	rotate_to_normal(t_item *item)
{
	t_v		ang;
	t_v		rot;
	t_v		p;
	t_v		bak;

	bak = item->pos;
	rot = item_get_axis(*item);
	move_item_to(item, v3(0, 0, 0));
	item->z_ref_point = v3_add(item->pos, v3(0, 1, 0));
	p = v3_add(item->pos, rot);
	ang.x = vect_angle(v3(item->z_ref_point.x, item->z_ref_point.y, 0),
			v3(p.x, p.y, 0));
	ang.y = vect_angle(v3(item->z_ref_point.x, 0, item->z_ref_point.z),
			v3(p.x, 0, p.z));
	ang.z = vect_angle(v3(0, item->z_ref_point.y, item->z_ref_point.z),
			v3(0, p.y, p.z));
	rotate_item(item, v3(ang.z, ang.y, ang.x));
	move_item_to(item, bak);
}
