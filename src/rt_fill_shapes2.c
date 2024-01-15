/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_shapes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:57:25 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/15 14:21:23 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	fill_pyramid(t_elem *elem, char **split)
{
	char	**xyz_split;
	char	**rgb_split;
	char	**norm_xyz_split;
	int		i;

	if (split[1] == NULL || split[2] == NULL || split[3] == NULL
		|| split[4] == NULL || split [5] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(split[1], ',');
	norm_xyz_split = ft_split(split[2], ',');
	elem->radius = ft_atof(split[3]) / 2;
	elem->height = ft_atof(split[4]);
	rgb_split = ft_split(split[5], ',');
	fill_arrays(elem, xyz_split, rgb_split, norm_xyz_split);
	i = -1;
	while (++i < 3)
	{
		free(xyz_split[i]);
		free(norm_xyz_split[i]);
		free(rgb_split[i]);
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255 || elem->norm_xyz[i] < -1
			|| elem->norm_xyz[i] > 1)
			fill_err(elem->type);
	}
	if (xyz_split != NULL && rgb_split != NULL && norm_xyz_split != NULL)
	{
		free(norm_xyz_split);
		free(xyz_split);
		free(rgb_split);
	}
}

void	fill_cube(t_elem *elem, char **split)
{
	char	**xyz_split;
	char	**rgb_split;
	char	**norm_xyz_split;
	int		i;

	if (split[1] == NULL || split[2] == NULL || split[3] == NULL
		|| split[4] == NULL || split [5] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(split[1], ',');
	norm_xyz_split = ft_split(split[2], ',');
	elem->radius = ft_atof(split[3]) / 2;
	elem->height = ft_atof(split[4]);
	rgb_split = ft_split(split[5], ',');
	fill_arrays(elem, xyz_split, rgb_split, norm_xyz_split);
	i = -1;
	while (++i < 3)
	{
		free(xyz_split[i]);
		free(norm_xyz_split[i]);
		free(rgb_split[i]);
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255 || elem->norm_xyz[i] < -1
			|| elem->norm_xyz[i] > 1)
			fill_err(elem->type);
	}
	if (xyz_split != NULL && rgb_split != NULL && norm_xyz_split != NULL)
	{
		free(norm_xyz_split);
		free(xyz_split);
		free(rgb_split);
	}
}

void	fill_compl(t_elem *elem, char **split, int ss)
{
	if (split[ss])
	{
		elem->specular = ft_atof(split[ss]);
		printf ("passed %f \n", elem->specular);
		if (elem->specular < 0 || elem->specular > 1)
			fill_err(elem->type);
	}
	else
		return ;
	if (split[++ss])
		elem->is_checker = ft_atoi(split[ss]);
	else
		return ;
	if (split[++ss])
	{
		elem->path_to_img = ft_strdup(split[ss]);// FIXME this will leak when strdup
		//if (access(elem->path_to_img, F_OK) && access(elem->path_to_img, R_Ok)))
		//	fill_err(elem->type);
	}
}
