/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

t_v3	v3(float x, float y, float z)
{
	t_v3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_v	v3_add(t_v a, t_v b)
{
	return (v3(a.x + b.x, a.y + b.y, a.z + b.z));
}

float	clamp(float val, float min, float max)
{
	return (fmin(fmax(val, min), max));
}

t_v	add_colors(t_v c1, t_v c2)
{
	t_v	res;

	res = v3_add(c1, c2);
	res.x = clamp(res.x, 0, 255);
	res.y = clamp(res.y, 0, 255);
	res.z = clamp(res.z, 0, 255);
	return (res);
}

t_v	mult_colors(t_v c1, t_v c2)
{
	t_v	res;

	res = v3(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z);
	return (res);
}
