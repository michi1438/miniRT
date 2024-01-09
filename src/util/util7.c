/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

vec	v3_invert(vec a)
{
	return (v3_scale(a, -1))
}

vec	v3_abs(vec a)
{
	return (v3(fabs(a.x), fabs(a.y), fabs(a.z)));
}

float	v3_len(vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

vec	v3_norm(vec v)
{
	return (v3_scale(v, 1/v3_len(v)));
}

float	v3_norm_squared(vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
