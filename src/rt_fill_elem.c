#include "rt_head.h"

void	fill_sphere(t_elem *elem, char **splited)
{
	char	**xyz_split;
	char	**rgb_split;
	int		i;

	if (splited[1] == NULL || splited[2] == NULL || splited[3] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(splited[1], ',');
	elem->diameter = ft_atof(splited[2]);
	rgb_split = ft_split(splited[3], ',');
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
}	

void	fill_plane(t_elem *elem, char **splited)
{
	char	**xyz_split;
	char	**rgb_split;
	char	**norm_xyz_split;
	int		i;

	if (splited[1] == NULL || splited[2] == NULL || splited[3] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(splited[1], ',');
	norm_xyz_split = ft_split(splited[2], ',');
	rgb_split = ft_split(splited[3], ',');
	i = -1;
	while (++i < 3 && xyz_split[i] != NULL && rgb_split[i] != NULL && norm_xyz_split[i] != NULL)
	{
		elem->xyz[i] = ft_atof(xyz_split[i]);
		elem->norm_xyz[i] = ft_atof(norm_xyz_split[i]);
		elem->rgb[i] = ft_atoi(rgb_split[i]);
	}
	i = -1;
	while (++i < 3)
	{
		free(xyz_split[i]);
		free(norm_xyz_split[i]);
		free(rgb_split[i]);
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255 || elem->norm_xyz[i] < -1 || elem->norm_xyz[i] > 1)
			fill_err(elem->type);
	}
}

void	fill_cylinder(t_elem *elem, char **splited)
{
	char	**xyz_split;
	char	**rgb_split;
	char	**norm_xyz_split;
	int		i;

	if (splited[1] == NULL || splited[2] == NULL || splited[3] == NULL || splited[4] == NULL || splited [5] == NULL)
		fill_err(elem->type);
	xyz_split = ft_split(splited[1], ',');
	norm_xyz_split = ft_split(splited[2], ',');
	elem->diameter = ft_atof(splited[3]);
	elem->height = ft_atof(splited[4]);
	rgb_split = ft_split(splited[5], ',');
	i = -1;
	while (++i < 3 && xyz_split[i] != NULL && rgb_split[i] != NULL && norm_xyz_split[i] != NULL)
	{
		elem->xyz[i] = ft_atof(xyz_split[i]);
		elem->norm_xyz[i] = ft_atof(norm_xyz_split[i]);
		elem->rgb[i] = ft_atoi(rgb_split[i]);
	}
	i = -1;
	while (++i < 3)
	{
		free(xyz_split[i]);
		free(norm_xyz_split[i]);
		free(rgb_split[i]);
		if (elem->rgb[i] < 0 || elem->rgb[i] > 255 || elem->norm_xyz[i] < -1 || elem->norm_xyz[i] > 1)
			fill_err(elem->type);
	}
}
