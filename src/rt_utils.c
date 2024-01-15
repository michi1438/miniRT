/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:35:49 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/15 16:42:19 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"
#include <float.h>

size_t	mantislen(char *str, int neg)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '.' && str[i] != '\n')
		i++;
	if (neg == -1)
		i += neg;
	return (i);
}

float	ft_atof(char *str)
{
	float	res;
	int		i;
	int		neg;
	int		len;

	res = 0;
	neg = 1;
	i = 0;
	if (str[i] == '-')
	{
		i++;
		neg = -1;
	}
	len = mantislen(str, neg);
	while (str[i] != '\0' && str[i] != '.' && str[i] != '\n')
		res += (str[i++] - '0') * pow(10, --len);
	if (str[i++] == '\0')
		return (res * neg);
	len = 0;
	while (str[i] != '\0' && str[i] != '.')
		res += (str[i++] - '0') * pow(10, --len);
	return (res * neg);
}

int	mix_color(t_elem *objects, t_list **e_list, float pscr[3])
{
	int		res;
	int		nrgb[3];
	int		i;
	float	n_ratio;
	t_elem	*amb;
	t_elem	*light;

	amb = findamb(e_list);
	light = findlight(e_list);
	objects->status = 1;
	n_ratio = (amb->light_ratio * 2.0f / 3.0f + diffused(objects, light, pscr, e_list));
	// FIXME is there a way to specify 2 / 3 as a less intensive way for the computer ?
	objects->status = 0;
	if (n_ratio > 1)
		n_ratio = 1;
	i = -1;
	while (++i < 3)
		nrgb[i] = (int)(objects->rgb[i] * n_ratio);
	res = (nrgb[0] << 16 | nrgb[1] << 8 | nrgb[2]);
	return (res);
}

float	diffused(t_elem *objects, t_elem *light, float pscr[3], t_list **e_list)
{
	float	p_hit[3];
	float	hit_norm[3];
	float	lnrm[3];
	float	diff[3];
	float	n_len;
	float	l_light;

	p_hit[0] = pscr[0];
	p_hit[1] = pscr[1];
	p_hit[2] = pscr[2];
	vec_substract(hit_norm, p_hit, objects->xyz);
	normalize(hit_norm);
	vec_substract(lnrm, p_hit, light->xyz);
	l_light = sqrt(lnrm[0] * lnrm[0] + lnrm[1] * lnrm[1] + lnrm[2] * lnrm[2]);
	// FIXME what is best pow(var, 2) or (var * var) ?
	normalize(lnrm);
	vec_substract(diff, hit_norm, lnrm);
	vec_substract(lnrm, light->xyz, p_hit);
	normalize(lnrm);
	n_len = sqrt(diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2]);
	if (n_len < M_SQRT2) // XXX shadows starts at the equator... try to comment this out and tell me what you think...
		return (0);
	n_len = log(n_len / M_SQRT2);
	if (n_len < 0 || cycle_shadow(lnrm, p_hit, e_list, l_light) == 0)
		return (0);
	return (n_len * light->light_ratio);
}
