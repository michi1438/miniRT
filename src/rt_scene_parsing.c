/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:54:04 by mguerga           #+#    #+#             */
/*   Updated: 2023/10/23 20:45:47 by mguerga          ###   ########.fr       */
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
//	ft_printf("%d\n", (t_elem *)(e_list->content)->type);
	return (0);
}

int	add_element(t_list	**e_list, char *str)
{
	//fill struct for each element of the scene, if element doesn't fit return error and free the previous nodes...	
	(void)str;
	t_elem	*elem;
	elem = malloc(sizeof(t_elem));
	elem->type = U;
	//elem = init_elem(str);
	ft_lstadd_front(e_list, ft_lstnew(elem));
	ft_printf("%d\n", elem->type);
	return (0);	
}
