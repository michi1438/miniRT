/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_testin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:25:25 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/16 15:44:05 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	print_elem(t_elem *elem)
{
	ft_printf("#####	elem->type = %c	##### \n\n", elem->type);
	printf("elem->light_ratio = %.2f\n", elem->light_ratio);
	printf("elem->fov = %f\n", elem->fov);
	printf("elem->height = %.2f\n", elem->height);
	printf("elem->radius = %.2f\n\n", elem->radius);
	printf("elem->xyz = %.2f\n", elem->xyz[0]);
	printf("elem->xyz = %.2f\n", elem->xyz[1]);
	printf("elem->xyz = %.2f\n\n", elem->xyz[2]);
	printf("elem->norm_xyz = %.2f\n", elem->norm_xyz[0]);
	printf("elem->norm_xyz = %.2f\n", elem->norm_xyz[1]);
	printf("elem->norm_xyz = %.2f\n\n", elem->norm_xyz[2]);
	printf("elem->rgb = %d\n", elem->rgb[0]);
	printf("elem->rgb = %d\n", elem->rgb[1]);
	printf("elem->rgb = %d\n\n", elem->rgb[2]);
}
