/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:54:04 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/06 09:49:43 by mguerga          ###   ########.fr       */
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
//	char	*temp;
	t_list	*e_list;	
	t_elem	*elem;

	str = get_next_line(fd);
	while (str != NULL)
	{
		//ft_putstr_fd(str, 1);
		//temp = str;
		if (add_element(&e_list, str) != 0)
		{
//			free(temp);
			return (1);
		}
		str = get_next_line(fd);
//		free (temp);
	}
	elem = e_list->content;
	ft_printf("elem->type = %c\n", elem->type);
	e_list = e_list->next;
	elem = e_list->content;
	ft_printf("elem->type = %c\n", elem->type);
	put_to_screen(&e_list);
	return (0);
}

void	init_elem(t_elem *elem, char *str)
{
	char	**splited;
	//int		i;

	//i = 0;
	splited = ft_split(str, ' ');
	//if (is_format(splited[i] != 0))
	//	exit (1);
	elem->type = splited[0][0];
	if (elem->type == 'A')
		fill_ambiant(elem, splited);
/*	else if (elem->type == 'C')
		fill_camera(elem, splited);
	else if (elem->type == 'L')
		fill_light(elem, splited);
	else if (elem->type == 's')
		fill_sphere(elem, splited);
	else if (elem->type == 'p')
		fill_plane(elem, splited);
	else if (elem->type == 'c')
		fill_cylinder(elem, splited);
//	while (splited[i] != NULL)
//		ft_printf("%s\n", splited[i++]);
*/
}

int	add_element(t_list	**e_list, char *str)
{
	//fill struct for each element of the scene, if element doesn't fit return error and free the previous nodes...	
	(void)str;
	t_elem	*elem;
	elem = malloc(sizeof(t_elem));
	elem->type = 'U';
	init_elem(elem, str);
	ft_lstadd_front(e_list, ft_lstnew(elem));
	//ft_printf("%p\n", elem);
	//check more stuff...
	return (0);	
}
