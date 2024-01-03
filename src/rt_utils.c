/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:35:49 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/04 00:11:17 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"
#include <float.h>

size_t	mantislen(char *str, int neg)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '.')
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
	while (str[i] != '\0' && str[i] != '.')
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
	n_ratio = (amb->light_ratio / 2 + diffused(objects, light, pscr, e_list));
	objects->status = 0;
	if (n_ratio > 1)
		n_ratio = 1;
	i = -1;
	while (++i < 3)
		nrgb[i] = (int)(objects->rgb[i] * n_ratio);
	res = (nrgb[0] << 16 | nrgb[1] << 8 | nrgb[2]);
	return (res);
}

float	diffused(t_elem *objects, t_elem *light, float pscreen[3], t_list **e_list)
{
	float	p_hit[3];
	float	hit_norm[3];
	float	light_norm[3];
	float	ddiff[3];
	float	n_len;
	float	lentolight;

	(void)lentolight;
	(void)e_list;
	p_hit[0] = pscreen[0];
	p_hit[1] = pscreen[1];
	p_hit[2] = pscreen[2];
	vec_substract(hit_norm, p_hit, objects->xyz);
	normalize(hit_norm);
	vec_substract(light_norm, p_hit, light->xyz);
	lentolight = sqrt(pow(light_norm[0], 2) + pow(light_norm[1], 2) + pow(light_norm[2], 2));
	normalize(light_norm);
	vec_substract(ddiff, hit_norm, light_norm);
	vec_substract(light_norm, light->xyz, p_hit);
	normalize(light_norm);
	n_len = log(sqrt(pow(ddiff[0], 2) + pow(ddiff[1], 2) + pow(ddiff[2], 2)));
	if (n_len < 0 || cycle_shadow(light_norm, p_hit, e_list, lentolight) == 0)
		return (0);
	return (n_len * light->light_ratio);
}
