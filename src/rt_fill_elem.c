/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:25:07 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/07 15:19:47 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	fill_err(char type)
{
	ft_printf("ERR: \"%c\" line can't be parsed, check your .rt file.\n", type);
	exit (1);
}

void	fill_ambiant(t_elem *elem, char **splited)
{
	char	**rgb_split;
	int		i;

	if (splited[1] == NULL || splited[2] == NULL)
		fill_err(elem->type);
	rgb_split = ft_split(splited[2], ',');
	elem->light_ratio = ft_atof(splited[1]);
	if (elem->light_ratio < 0 || elem->light_ratio > 1)
		fill_err(elem->type);
	i = -1;
	while (++i < 3 && rgb_split[i] != NULL)
		elem->rgb[i] = ft_atoi(rgb_split[i]);
	i = -1;
	while (++i < 3)
	{
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255)
			fill_err(elem->type);
	}
}

void	fill_camera(t_elem *elem, char **splited)
{
	char	**xyz_split;
	char	**norm_xyz_split;
	int		i;

	if (splited[1] == NULL || splited[2] == NULL || splited[3] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(splited[1], ',');
	norm_xyz_split = ft_split(splited[2], ',');
	elem->fov = ft_atoi(splited[3]);
	i = -1;
	while (++i < 3 && xyz_split[i] != NULL && norm_xyz_split[i] != NULL)
	{
		elem->xyz[i] = ft_atof(xyz_split[i]);
		elem->norm_xyz[i] = ft_atof(norm_xyz_split[i]);
	}
}
