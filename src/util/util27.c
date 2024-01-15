/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util19.c                                            :+:      :+:    :+:   */
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
	t_v rot = item_get_axis(*item);
	item->z_ref_point = v3_add(item->pos, v3(0, 1, 0));
	t_v p = v3_add(item->pos, rot);

	float angle1 = vect_angle(v3(item->z_ref_point.x, item->z_ref_point.y, 0), v3(p.x, p.y, 0));
	float angle2 = vect_angle(v3(item->z_ref_point.x, 0, item->z_ref_point.z), v3(p.x, 0, p.z));
	float angle3 = vect_angle(v3(0, item->z_ref_point.y, item->z_ref_point.z), v3(0, p.y, p.z));

	printf("angles: %f, %f, %f", angle1, angle2, angle3);
	rotate_item(item, v3(angle1 * 5.899659289, angle2 * 5.899659289, angle3 * 5.899659289));
}
