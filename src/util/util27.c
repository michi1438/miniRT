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
	float	angle1;
	float	angle2;
	float	angle3;
	t_v		rot;
	t_v		p;

	rot = item_get_axis(*item);
	item->z_ref_point = v3_add(item->pos, v3(0, 1, 0));
	p = v3_add(item->pos, rot);
	angle1 = vect_angle(v3(item->z_ref_point.x, item->z_ref_point.y, 0),
			v3(p.x, p.y, 0));
	angle2 = vect_angle(v3(item->z_ref_point.x, 0, item->z_ref_point.z),
			v3(p.x, 0, p.z));
	angle3 = vect_angle(v3(0, item->z_ref_point.y, item->z_ref_point.z),
			v3(0, p.y, p.z));
	rotate_item(item, v3(angle1 * 5.899659289, angle2
			* 5.899659289, angle3 * 5.899659289));
}