/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt_head.h"

/* Source: https://www.geeksforgeeks.org/dda-line
 * -generation-algorithm-computer-graphics/ */
void	draw_line_dda(t_scData *scrn, vec p1, vec p2, int color)
{
	int		steps;
	float	pos[2];
	float	incs[2];
	int		i;

	if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y))
		steps = fabs(p2.x - p1.x);
	else
		steps = fabs(p2.y - p1.y);
	incs[0] = (p2.x - p1.x) / (float)steps;
	incs[1] = (p2.y - p1.y) / (float)steps;
	pos[0] = p1.x;
	pos[1] = p1.y;
	i = 0;
	while (i <= steps)
	{
		mlx_pp(scrn, pos[0], pos[1], color);
		pos[0] += incs[0];
		pos[1] += incs[1];
		i ++;
	}
}
