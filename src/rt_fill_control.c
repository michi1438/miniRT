/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fill_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:04:41 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/18 11:42:15 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

void	set_uvalue(t_elem *elem)
{
	int	i;

	i = -1;
	elem->type = 'U';
	elem->specular = -1;
	elem->is_checker = 0;
	elem->fov = -2;
	elem->light_ratio = -2;
	elem->sratio = (float)S_WIDTH / S_HEIGHT;
	elem->radius = 0;
	elem->height = 0;
	elem->status = 0;
	while (++i < 3)
	{
		elem->rgb[i] = 0;
		elem->xyz[i] = 0;
		elem->norm_xyz[i] = 0;
	}
}

void	init_elem(t_elem *elem, char *str)
{
	char	**splited;
	int		i;

	splited = ft_split(str, ' ');
	set_uvalue(elem);
	elem->type = splited[0][0];
	if (init_must_have(elem, splited) == 1)
		;
	else if (elem->type == 's')
		fill_sphere(elem, splited);
	else if (elem->type == 'p')
		fill_plane(elem, splited);
	else if (elem->type == 'c')
		fill_cylinder(elem, splited);
	else if (elem->type == 'b')
		fill_cube(elem, splited);
	else if (elem->type == 'y')
		fill_pyramid(elem, splited);
	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	if (splited != NULL)
		free(splited);
}

int	init_must_have(t_elem *elem, char **splited)
{
	if (elem->type == 'A')
		fill_ambiant(elem, splited);
	else if (elem->type == 'C')
		fill_camera(elem, splited);
	else if (elem->type == 'L')
		fill_light(elem, splited);
	else
		return (0);
	return (1);
}

int	add_element(t_list	**e_list, char *str)
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem));
	if (elem == NULL)
		return (-1);
	init_elem(elem, str);
	ft_lstadd_front(e_list, ft_lstnew(elem));
	if (*e_list == NULL)
		return (-1);
	return (0);
}
