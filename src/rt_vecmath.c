/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vecmath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/16 18:55:01 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	normalize(float *xyz)
{
	float vec_len;
	
	vec_len = sqrt(pow(xyz[0], 2) + pow(xyz[1], 2) + 1);
	xyz[0] = xyz[0] / vec_len;
	xyz[1] = xyz[1] / vec_len;
	xyz[2] = xyz[2] / vec_len;
}


float	dotprod(float *vec1, float *vec2)
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}
		
void	vec_substract(float *res_vec, float *vec1, float *vec2)
{
	res_vec[0] = vec1[0] - vec2[0];
	res_vec[1] = vec1[1] - vec2[1];
	res_vec[2] = vec1[2] - vec2[2];
}
