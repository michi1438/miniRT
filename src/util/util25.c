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

// TODO: resize the image and return new alloced one
t_v	**get_pixels_from_image(t_image img, float target_width)
{
	(void) img;
	(void) target_width;
	return (NULL);
}

// TODO: free cache
void	free_pixel_cache(t_v **cache)
{
	(void) cache;
}

t_v3tpl	tuple(t_v v1, t_v v2)
{
	t_v3tpl	res;

	res.v1 = v1;
	res.v2 = v2;
	return (res);
}

t_line	line_c(t_v p1, t_v p2)
{
	t_line	line;

	line.p1 = p1;
	line.p2 = p2;
	return (line);
}
