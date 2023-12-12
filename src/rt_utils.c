/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:35:49 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/12 09:39:26 by mguerga          ###   ########.fr       */
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

int	mix_color(int *rgb, float p_norm[3], t_elem *amb)
{
	int	res;

	rgb[0] = (rgb[0] + amb->rgb[0]);
	rgb[0] /= 2;
	rgb[1] = (rgb[1] + amb->rgb[1]);
	rgb[1] /= 2;
	rgb[2] = (rgb[2] + amb->rgb[2]);
	rgb[2] /= 2;
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	res = ((int)(rgb[0] * p_norm[2] * amb->light_ratio) << 16 | (int)(rgb[1] * p_norm[2] * amb->light_ratio) << 8 | (int)(rgb[2] * p_norm[2] * amb->light_ratio));
	return (res);
}
