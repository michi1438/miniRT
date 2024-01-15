/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_shapes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:57:25 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/15 19:45:35 by mguerga          ###   ########.fr       */
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
	elem->radius = ft_atof(split[3]);
	elem->height = ft_atof(split[4]);
	rgb_split = ft_split(split[5], ',');
	fill_compl(elem, split, 6);
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
		|| split[4] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(split[1], ',');
	norm_xyz_split = ft_split(split[2], ',');
	elem->height = ft_atof(split[3]);
	rgb_split = ft_split(split[4], ',');
	fill_compl(elem, split, 5);
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
		if (elem->specular < -1)
			elem->specular = -1;
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
		if (access(elem->path_to_img, F_OK) == -1) // FIXME Paths expect a space at the end... 
			fill_err(elem->type);
//		parse_img(elem, split[ss]);
	}
}
/*
void	parse_img(t_elem *elem, char *pt_img)
{
	int fd;
	int i;
	char *str;
	char **split;

	fd = open(pt_img, O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		split = ft_split(str, " ");
		while (split[i] != NULL)

		temp = str;
		str = get_next_line(fd);
		free(temp);
	}
}
*/
