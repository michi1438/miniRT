/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util24.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

float	new_image_height(t_image *img, float new_width)
{
	return (img->height / (img->width / new_width));
}

vec	**getPixelsFromImage(t_image img, float target_width)
{
	// TODO: resize the image and return new alloced one
}

void	free_pixel_cache(vec **cache)
{
	// TODO: free cache
}

t_v3_tuple	tuple(vec v1,vec v2)
{
	t_v3_tuple	res;

	res.v1 = v1;
	res.v2 = v2;
	return (res);
}

