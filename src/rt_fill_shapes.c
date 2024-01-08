/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_shapes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:17 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/08 10:28:30 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	fill_sphere(t_elem *elem, char **split)
{
	char	**xyz_split;
	char	**rgb_split;
	int		i;

	if (split[1] == NULL || split[2] == NULL || split[3] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(split[1], ',');
	elem->radius = ft_atof(split[2]) / 2;
	rgb_split = ft_split(split[3], ',');
	i = -1;
	while (++i < 3 && xyz_split[i] != NULL && rgb_split[i] != NULL)
	{
		elem->xyz[i] = ft_atof(xyz_split[i]);
		elem->rgb[i] = ft_atoi(rgb_split[i]);
	}
	i = -1;
	while (++i < 3)
	{
		free(xyz_split[i]);
		free(rgb_split[i]);
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255)
			fill_err(elem->type);
	}
	if (xyz_split != NULL && rgb_split != NULL)
	{
		free(xyz_split);
		free(rgb_split);
	}
}	

void	fill_plane(t_elem *elem, char **split)
{
	char	**xyz_split;
	char	**rgb_split;
	char	**norm_xyz_split;
	int		i;

	if (split[1] == NULL || split[2] == NULL || split[3] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(split[1], ',');
	norm_xyz_split = ft_split(split[2], ',');
	rgb_split = ft_split(split[3], ',');
	fill_arrays(elem, xyz_split, rgb_split, norm_xyz_split);
	i = -1;
	while (++i < 3)
	{
		free(xyz_split[i]);
		free(norm_xyz_split[i]);
		free(rgb_split[i]);
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255
			|| elem->norm_xyz[i] < -1 || elem->norm_xyz[i] > 1)
			fill_err(elem->type);
	}
}

void	fill_cylinder(t_elem *elem, char **split)
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
}

void	fill_arrays(t_elem *elem, char **xyz, char **rgb, char **norm)
{
	int	i;

	i = -1;
	while (++i < 3 && xyz[i] != NULL && rgb[i] != NULL && norm[i] != NULL)
	{
		elem->xyz[i] = ft_atof(xyz[i]);
		elem->norm_xyz[i] = ft_atof(norm[i]);
		elem->rgb[i] = ft_atoi(rgb[i]);
	}
}
