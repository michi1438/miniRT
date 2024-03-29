/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_shapes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:57:25 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/18 11:52:00 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	fill_pyramid(t_elem *elem, char **split)
{
	char	**xyz_split;
	char	**rgb_split;
	char	**norm_xyz_split;

	if (split[1] == NULL || split[2] == NULL || split[3] == NULL
		|| split[4] == NULL || split [5] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(split[1], ',');
	norm_xyz_split = ft_split(split[2], ',');
	elem->radius = ft_atof(split[3]);
	elem->height = ft_atof(split[4]);
	rgb_split = ft_split(split[5], ',');
	fill_compl(elem, split, 6);
	fill_arrays(elem, xyz_split, rgb_split, norm_xyz_split);
	free_elem(elem, xyz_split, rgb_split, norm_xyz_split);
}

void	fill_cube(t_elem *elem, char **split)
{
	char	**xyz_split;
	char	**rgb_split;
	char	**norm_xyz_split;

	if (split[1] == NULL || split[2] == NULL || split[3] == NULL
		|| split[4] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(split[1], ',');
	norm_xyz_split = ft_split(split[2], ',');
	elem->height = ft_atof(split[3]);
	rgb_split = ft_split(split[4], ',');
	fill_compl(elem, split, 5);
	fill_arrays(elem, xyz_split, rgb_split, norm_xyz_split);
	free_elem(elem, xyz_split, rgb_split, norm_xyz_split);
}

void	fill_compl(t_elem *elem, char **split, int ss)
{
	if (split[ss])
	{
		elem->specular = ft_atof(split[ss]);
		if (elem->specular < -1)
			elem->specular = -1;
	}
	if (split[ss] && split[++ss])
		elem->is_checker = ft_atoi(split[ss]);
	return ;
}
