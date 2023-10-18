/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:11 by mguerga           #+#    #+#             */
/*   Updated: 2023/10/18 15:44:05 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HEAD_H
# define RT_HEAD_H

# include <stdio.h>
# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/src_libft.h"

// SCENE_PARSING.C
int	scene_parsing(int ac, char **av);
int	in_scene_parsing(int fd);

// ERR_HANDLING.C
int	print_err(char *str);

#endif // RT_HEAD_H
