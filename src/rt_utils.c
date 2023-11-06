/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:35:49 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/06 12:04:48 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"
#include <float.h>

size_t mantislen(char *str, int neg)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '.')
		i++;
	printf("i = %d \n", i);
	if (neg == -1)
		i += neg;
	return (i);
}

float	ft_atof(char *str)
{
	float res = 0;
	int i;
	int neg;
	int len;

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
//	XXX TEST for precision...
	printf("This is a test for the ft_atof()'s precision...\n");
	printf("printf(\"%%.30f\\n\", (float)res * neg);  --> ");
	printf("%.30f\n", (float)res * neg);
	printf("printf(\"%%.30f\\n\", 0.255255255);       --> ");
	printf("%.30f\n", 0.255255255);
	return (res * neg);
}
