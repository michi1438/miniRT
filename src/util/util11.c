/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util11.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:53:56 by mguerga           #+#    #+#             */
/*   Updated: 2023/12/06 16:19:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

/*
 function rgbToHexV3(v) {
		return ("#" + (1 << 24 | v.x << 16 | v.y << 8 | v.z).toString(16).slice(1));
	}
 * */
int	vec_color_to_int(vec color)
{
	return (((int)color.x << 16) | ((int)color.y << 8) | (int)color.z);
}

void	draw_line(t_scData *scrn, vec p1, vec p2, vec color) {
	draw_line_dda(scrn, p1, p2, vec_color_to_int(color));
}