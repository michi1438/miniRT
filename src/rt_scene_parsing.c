/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:54:04 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/16 13:14:23 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_head.h"

int	scene_parsing(int ac, char **av)
{
	int	av_size;
	int	fd;

	if (ac != 2)
		return (print_err("You must have 1 scene as argument !\n"));
	av_size = ft_strlen(av[1]);
	if (av_size < 4 || ft_strncmp(&av[1][av_size - 3], ".rt", 4))
		return (print_err("The scene must be in the \".rt\" format !\n"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_err("The scene does not exist !\n"));
	if (in_scene_parsing(fd) != 0)
		return (1);
	return (0);
}

int	in_scene_parsing(int fd)
{
	char	*str;
	t_list	*e_list;	
//	t_elem	*elem;
	char	*temp;

	str = get_next_line(fd);
	ft_lstadd_front(&e_list, ft_lstnew(NULL));
	while (str != NULL)
	{
		temp = str;
		if (add_element(&e_list, str) != 0)
		{
			free(temp);
			return (1);
		}
		str = get_next_line(fd);
		free (temp);
	}
//	ft_lstclear(&e_list, free);
	musthave_elem(e_list);
	put_to_screen(&e_list);
	return (0);
}

void	musthave_elem(t_list *e_list)
{
	t_elem	*elem;
	int		c;

	c = 0;
	while (e_list->content != NULL)
	{
		elem = e_list->content;
		if (elem->type == 'C')
			c = 1;
		e_list = e_list->next;
	}
	if (c != 1)
	{
		print_err("The .rt file does'nt contain a camera !\n");	
		exit (1);
	}
}

void	set_uvalue(t_elem *elem)
{
	int	i;

	i = -1;
	elem->type = 'U';
	elem->fov = -2;
	elem->light_ratio = -2;
	elem->diameter = 0;
	elem->height = 0;
	while (++i < 3)
	{
		elem->rgb[i] = -2;
		elem->xyz[i] = 0;
		elem->norm_xyz[i] = -2;
	}
}

void	init_elem(t_elem *elem, char *str)
{
	char	**splited;
	int		i;

	splited = ft_split(str, ' ');
	set_uvalue(elem);
	elem->type = splited[0][0];
	if (elem->type == 'A')
		fill_ambiant(elem, splited);
	else if (elem->type == 'C')
		fill_camera(elem, splited);
	else if (elem->type == 'L')
		fill_light(elem, splited);
	else if (elem->type == 's')
		fill_sphere(elem, splited);
	else if (elem->type == 'p')
		fill_plane(elem, splited);
	else if (elem->type == 'c')
		fill_cylinder(elem, splited);
	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
}

int	add_element(t_list	**e_list, char *str)
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem));
	if (elem == NULL)
		return (-1);
	init_elem(elem, str);
	ft_lstadd_front(e_list, ft_lstnew(elem));
//	printf("e_list = %p\n", *e_list);
	if (*e_list == NULL)
		return (-1);
	//check more stuff...
	return (0);
}
