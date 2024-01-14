/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_lightsncamera.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:04:36 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/08 12:08:59 by mguerga          ###   ########.fr       */
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
		free(rgb_split[i]);
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255)
			fill_err(elem->type);
	}
	if (rgb_split != NULL)
		free(rgb_split);
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
	elem->fov = ft_atof(splited[3]);//tan(ft_atof(splited[3]) / 2 * M_PI / 180);
	i = -1;
	while (++i < 3 && xyz_split[i] != NULL && norm_xyz_split[i] != NULL)
	{
		elem->xyz[i] = ft_atof(xyz_split[i]);
		elem->norm_xyz[i] = ft_atof(norm_xyz_split[i]) * M_PI;
	}
	i = -1;
	while (++i < 3)
	{
		free(xyz_split[i]);
		free(norm_xyz_split[i]);
//		printf("elem->norm_xyz[i] = %f\n", elem->norm_xyz[i]);
//		printf("M_PI = %f\n", M_PI + 0.001); // XXX this is cheating there is probably a better way...
		if (fabs(elem->norm_xyz[i]) > M_PI + 0.001)
			fill_err(elem->type);
	}
	if (xyz_split != NULL && norm_xyz_split != NULL)
	{
		free(xyz_split);
		free(norm_xyz_split);
	}
}

void	fill_light(t_elem *elem, char **splited)
{
	char	**xyz_split;
	char	**rgb_split;
	int		i;

	rgb_split = NULL;
	if (splited[1] == NULL || splited[2] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(splited[1], ',');
	if (splited[3] != NULL)
		rgb_split = ft_split(splited[3], ',');
	elem->light_ratio = ft_atof(splited[2]);
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
