/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:35:49 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/01 18:46:57 by mguerga          ###   ########.fr       */
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
	float	res = 0;
	int		i;
	int		neg;
	int		len;

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
/*	XXX TEST for precision...
	printf("This is a test for the ft_atof()'s precision...\n");
	printf("printf(\"%%.30f\\n\", (float)res * neg);	--> ");
	printf("%.30f\n", (float)res * neg);
	printf("printf(\"%%.30f\\n\", 0.2);			--> ");
	printf("%.30f\n\n", 0.2);
*/
	return (res * neg);
}

int	mix_color(t_elem *objects, t_list **e_list, float pscreen[3], float dis)
{
	int	res;
	int nrgb[3];
	int i;
	float	n_ratio;
	t_elem *amb;
	t_elem	*light;
	t_list	*list;	

	amb = findamb(e_list);
	list = *e_list;
	while (list != NULL)
	{
		light = (list)->content;
		if (light->type == 'L')
		{
			n_ratio = amb->light_ratio * diffused(objects, light, pscreen, dis);
			break;
		}
		list = list->next;
	}
	i = -1;
	while (++i < 3)
		nrgb[i] = (int)(objects->rgb[i] * n_ratio);
	res = (nrgb[0] << 16 | nrgb[1] << 8 | nrgb[2]);
	return (res);
}

float diffused(t_elem *objects, t_elem *light, float pscreen[3], float dis)
{
	float p_hit[3];
	float hit_norm[3];
	float light_norm[3];
	float hit_deg;
	float light_deg;

	p_hit[0] = pscreen[0] * dis;
	p_hit[1] = pscreen[1] * dis;
	p_hit[2] = pscreen[2] * dis;
	vec_substract(hit_norm, p_hit, objects->xyz);
	normalize(hit_norm);
	hit_deg = (cos(hit_norm[0]) + cos(hit_norm[1]) + cos(hit_norm[2])) / 3;
	vec_substract(light_norm, p_hit, light->xyz);
	normalize(light_norm);
	light_deg = (cos(light_norm[0]) + cos(light_norm[1]) + cos(light_norm[2])) / 3;
	//printf("hit_deg - light_deg = %f\n", 1 - (light_deg - hit_deg)); 
	//if (light_deg - hit_deg > 1)
	///	return (1);
	return (1 - (light_deg - hit_deg)); // set up make diff light_norm and hit_norm for diffused.
}
