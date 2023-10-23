/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:11 by mguerga           #+#    #+#             */
/*   Updated: 2023/10/23 20:40:27 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HEAD_H
# define RT_HEAD_H

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/src_libft.h"

typedef struct	s_elem
{
	int	type;
	int	RGB[3];
	int	xyz[3];
	int	norm_xyz[3];
	int	FOV;
	int light_ratio;
}	t_elem;

enum	e_type
{
	U = 11, // For undefined
	A,
	C,
	L,
	SP,
	PL,
	CY,
};

// SCENE_PARSING.C
int	scene_parsing(int ac, char **av);
int	in_scene_parsing(int fd);
int	add_element(t_list	**e_list, char *str);

// ERR_HANDLING.C
int	print_err(char *str);

#endif // RT_HEAD_H
