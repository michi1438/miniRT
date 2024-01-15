/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:11 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/15 14:06:34 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HEAD_H
# define RT_HEAD_H

# define S_WIDTH (1368)
# define S_HEIGHT (912)

# include <stdio.h>
# include <float.h>
# include "../minilibx-linux/mlx.h"
//# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/src_libft.h"
# include <math.h>

typedef struct s_elem
{
	char	type;
	float	specular;
	int		is_checker;
	char 	*path_to_img;
	int		rgb[3];
	float	xyz[3];
	float	norm_xyz[3];
	float	fov;
	float	sratio;
	float	radius;
	float	height;
	float	light_ratio;
	int		status;
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

// MATRICES.C
void	rt_matrix(float *ret, t_elem *cam_specs);

// SCENE.C
void	set_scene(t_scData *scrn, t_list **e_list);
void	first_rays(t_scData *scrn, t_list **e_list);
void	cycle_objects(int xy[2], float pscreen[3], t_elem *cam_specs, t_scData *scrn, t_list **e_list);
int		cycle_shadow(float n_vec[3], float orig_xyz[3], t_list **e_list, float n_len);

// FETCH_ELEM.C
t_elem	*findcam(t_list **e_list);
t_elem	*findamb(t_list **e_list);
t_elem	*findlight(t_list **e_list);

// INTERSECTING.C
float	intersect_sp(float *normal_dir, float orig_xyz[3], t_elem *obj);
int		solve_discriminent(float a, float b, float c, float *intersect_dist);

// VEC_MATH.C
float	dotprod(float *vec1, float *vec2);
void	vec_substract(float *res_vec, float *vec1, float *vec2);
void	normalize(float *xyz);

// FILL_CONTROL.c
void	set_uvalue(t_elem *elem);
void	init_elem(t_elem *elem, char *str);
int		add_element(t_list	**e_list, char *str);

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

// FILL_SHAPES2_& COMPL.c
void	fill_pyramid(t_elem *elem, char **split);
void	fill_cube(t_elem *elem, char **split);
void	fill_compl(t_elem *elem, char **split, int split_seg);

// DISPLAY.C
int		kb_mlx(int keycd, t_scData *scrn);
int		put_to_screen(t_list **e_list);
void	mlx_pp(t_scData *img, int x, int y, int color);

// SCENE_PARSING.C
int		scene_parsing(int ac, char **av);
int		in_scene_parsing(int fd);
void	musthave_elem(t_list *e_list);

// UTILS.C (maybe put this in libft)
float	ft_atof(char *str);
int		mix_color(t_elem *objects, t_list **e_list, float pscr[3]);
float	diffused(t_elem *objects, t_elem *light, float pscreen[3], t_list **e_list);

// ERR_HANDLING.C
int		print_err(char *str);

// TESTING.C
void	print_elem(t_elem *elem);

#endif // RT_HEAD_H
