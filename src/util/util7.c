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

t_v	v3_invert(t_v a)
{
	return (v3_scale(a, -1));
}

t_v	v3_abs(t_v a)
{
	return (v3(fabs(a.x), fabs(a.y), fabs(a.z)));
}

float	v3_len(t_v a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_v	v3_norm(t_v v)
{
	return (v3_scale(v, 1/v3_len(v)));
}

float	v3_norm_squared(t_v v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
