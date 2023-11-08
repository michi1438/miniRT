/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:11 by mguerga           #+#    #+#             */
/*   Updated: 2023/11/08 11:28:07 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HEAD_H
# define RT_HEAD_H

# include <stdio.h>
//# include "../minilibx-linux/mlx.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/src_libft.h"
# include <math.h>

typedef struct s_elem
{
	char	type;
	int		rgb[3];
	float	xyz[3];
	float	norm_xyz[3];
	int		fov;
	float	diameter;
	float	height;
	float	light_ratio;
}	t_elem;

typedef struct s_scData
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_pp;
	int		line_len;
	int		endian;
	t_list	**e_list_displayed;	
}	t_scData;

// FILL_LIGHTSNCAMERA.c
void	fill_err(char type);
void	fill_ambiant(t_elem *elem, char **splited);
void	fill_camera(t_elem *elem, char **splited);
void	fill_light(t_elem *elem, char **splited);

// FILL_SHAPES.c
void	fill_arrays(t_elem *elem, char **xyz, char **rgb, char **norm);
void	fill_cylinder(t_elem *elem, char **split);
void	fill_sphere(t_elem *elem, char **split);
void	fill_plane(t_elem *elem, char **split);

// DISPLAY.C
int		kb_mlx(int keycd, t_scData *scrn);
int		put_to_screen(t_list **e_list);
void	mlx_pp(t_scData *img, int x, int y, int color);

// SCENE_PARSING.C
int		scene_parsing(int ac, char **av);
int		in_scene_parsing(int fd);
void	init_elem(t_elem *elem, char *str);
int		add_element(t_list	**e_list, char *str);

// UTILS.C (maybe put this in libft)
float	ft_atof(char *str);

// ERR_HANDLING.C
int		print_err(char *str);

// TESTING.C
void	print_elem(t_elem *elem);

#endif // RT_HEAD_H
