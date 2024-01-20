/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:36:11 by mguerga           #+#    #+#             */
/*   Updated: 2024/01/18 16:46:31 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_HEAD_H
# define RT_HEAD_H

# define S_WIDTH 1000
# define S_HEIGHT 1000

# include <stdio.h>
# include "float.h"
# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
# else
#  include "../minilibx_opengl_20191021/mlx.h"
# endif
# include "../libft/src_libft.h"
# include <math.h>
# include <unistd.h>

# define RESOLUTION 0.006
# define SPECULAR 0.7
# define TOLERANCE 0.000001
# define ROT_SPEED 0.003

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define WHITE 0x11111111

# ifdef __linux__
#  define K_ENTER 65293
#  define K_SPACE 32
#  define K_TAB 65289
#  define K_ESC 65307
#  define K_UP 65362
#  define K_DOWN 65364
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_P 112
#  define K_MINUS 61
#  define K_PLUS 10
#  define K_R 114
#  define K_U 117
#  define K_J 106
#  define K_I 105
#  define K_K 107
#  define K_O 111
#  define K_L 108

#  define K_NUM_4 65430
#  define K_NUM_6 65432
#  define K_NUM_8 65431
#  define K_NUM_2 65433
#  define K_NUM_MINUS 65453
#  define K_NUM_PLUS 65451
# else
#  define K_ENTER 36
#  define K_SPACE 49
#  define K_TAB 48
#  define K_ESC 53
#  define K_UP 126
#  define K_DOWN 125
#  define K_LEFT 123
#  define K_RIGHT 124
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_P 35
#  define K_MINUS 27
#  define K_PLUS 24
#  define K_R 15
#  define K_U 32
#  define K_J 38
#  define K_I 34
#  define K_K 40
#  define K_O 31
#  define K_L 37

#  define K_NUM_4 86
#  define K_NUM_6 88
#  define K_NUM_8 91
#  define K_NUM_2 84
#  define K_NUM_MINUS 78
#  define K_NUM_PLUS 69
# endif

typedef unsigned int		t_uint;

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}	t_v3;

typedef t_v3				t_v;

enum	e_ObjectType
{
	Plane,
	Sphere,
	Cube,
	Pyramid,
	Cylinder
};

typedef enum e_ObjectType	t_objty;

typedef struct s_v3_tuple
{
	t_v	v1;
	t_v	v2;
}	t_v3tpl;

typedef struct s_floatint_tuple
{
	float	f;
	int		i;
}	t_fitpl;

typedef struct s_elem
{
	char	type;
	float	specular;
	int		is_checker;
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

enum	e_Direction
{
	Forward,
	Backward,
	Left,
	Right,
	Up,
	Down
};

typedef struct s_plane
{
	t_v	p1;
	t_v	p2;
	t_v	p3;
}	t_plane;

typedef struct s_line
{
	t_v	p1;
	t_v	p2;
}	t_line;

typedef struct s_matrix3d
{
	t_v	v1;
	t_v	v2;
	t_v	v3;
}	t_mtrx;

typedef struct s_camera
{
	float	canvas_width;
	float	canvas_height;
	t_v		eye;
	t_v		a;
	t_v		b;
	t_v		c;
}	t_camra;

enum	e_LightType
{
	Ambient,
	Point
};

typedef struct s_light
{
	enum e_LightType	type;
	t_v					color;
	t_v					pos;
}	t_light;

typedef struct s_image
{
	t_v		**pixels;
	float	target_width;
	float	width;
	float	height;
}	t_image;

typedef struct s_item
{
	enum e_ObjectType	type;
	t_v					pos;
	t_v					scale;
	t_v					color;
	float				specular;
	int					is_checker;
	t_v					z_ref_point;
	t_v					vertices[34];
	int					vertices_len;
	int					id;
	t_v					**pixel_cache;
	int					cache_width;
	int					cache_length;
	t_image				*image;
}	t_item;

typedef struct s_intersection
{
	t_v		pos;
	t_v		normal;
	t_line	ray;
	t_item	*item;
}	t_intsc;

typedef struct s_rtdata
{
	t_camra		camera;
	t_scData	*scrn;
	t_list		*items;
	t_list		*lights;

}	t_rtdata;

typedef struct s_terms
{
	t_v				d;
	t_v				v;
	t_v				c_;
	t_v				x_;
	t_v				n;
	float			d_v;
	float			x_v;
	float			t;
	t_v				normal;
	t_v				intr;
	float			a;
	float			b;
	float			c;
	float			r;
	float			discriminant;
	float			t1;
	float			t2;
	t_v				point;
	t_intsc			inter;
	t_intsc			inter2;
	float			dist;
	float			dist_;
	float			d1;
	float			d2;
	float			m1;
	float			m2;
	float			tmp;
	t_v				y_axis;
	t_v				x_axis;
	t_v				z_axis;
	float			x_dist;
	float			y_dist;
	float			z_dist;
	t_v				x;
	t_v				y;
	t_v				z;
	t_v				light_color;
	t_v				specular_color;
	t_v				diffuse_color;
	t_v				color;
}	t_terms;

typedef struct s_vecfour
{
	t_v	p1;
	t_v	p2;
	t_v	p3;
	t_v	p4;
}	t_vec4;

// MATRICES.C
void	rt_matrix(float *ret, t_elem *cam_specs);

// FETCH_ELEM.C
t_elem	*findcam(t_list **e_list);
t_elem	*findamb(t_list **e_list);
t_elem	*findlight(t_list **e_list);

// FILL_CONTROL.c
void	set_uvalue(t_elem *elem);
void	init_elem(t_elem *elem, char *str);
int		init_must_have(t_elem *elem, char **splited);
int		add_element(t_list	**e_list, char *str);

// FILL_LIGHTSNCAMERA.c
void	fill_err(char type);
void	fill_ambiant(t_elem *elem, char **splited);
void	fill_camera(t_elem *elem, char **splited);
void	fill_light(t_elem *elem, char **splited);
void	free_elem(t_elem *elem, char **split1, char **split2, char **split3);

// FILL_SHAPES.c
void	fill_arrays(t_elem *elem, char **xyz, char **rgb, char **norm);
void	fill_cylinder(t_elem *elem, char **split);
void	fill_sphere(t_elem *elem, char **split);
void	fill_plane(t_elem *elem, char **split);

// FILL_SHAPES2_& COMPL.c
void	fill_pyramid(t_elem *elem, char **split);
void	fill_cube(t_elem *elem, char **split);
void	fill_compl(t_elem *elem, char **split, int split_seg);

// KB_AND_PP_MLX.C
void	mlx_pp(t_scData *img, int x, int y, int color);
int		kb_mlx(int keycd, t_rtdata *data);
void	more_keys1(int keycd, t_rtdata *data);

// SCENE_PARSING.C
t_list	*scene_parsing(int ac, char **av);
t_list	*in_scene_parsing(int fd);
void	musthave_elem(t_list *e_list);

// UTILS.C (maybe put this in libft)
float	ft_atof(char *str);

// ERR_HANDLING.C
int		print_err(char *str);

// TESTING.C
void	print_elem(t_elem *elem);

// UTIL1.C
t_v3	v3(float x, float y, float z);
t_v		v3_add(t_v a, t_v b);
float	clamp(float val, float min, float max);
t_v		add_colors(t_v c1, t_v c2);
t_v		mult_colors(t_v c1, t_v c2);

// UTIL2.C
t_v		modify_color_intensity(t_v color, float scalar);
t_v		intensity_to_color(float intensity);
int		same_sign(float a, float b);
t_plane	plane_c(t_v p1, t_v p2, t_v p3);
t_v		plane_normal(t_plane plane);

// UTIL3.C
int		colinear_check(t_v v1);
t_plane	plane_from_normal(t_v point, t_v normal);
t_line	line_c(t_v p1, t_v p2);
t_mtrx	matrix3d_c(t_v v1, t_v v2, t_v v3);
int		same_side_of_line(t_line line, t_v A, t_v B);

// UTIL4.C
int		same_side_of_plane(t_plane plane, t_v A, t_v B);
t_v		rotate_point(t_v p, t_v v, t_v r);
float	vect_angle(t_v v1, t_v v2);
float	degree_to_radian(float angle);

// UTIL5.C
t_v		v3_sub(t_v a, t_v b);
t_v		v3_clone(t_v v);
t_v		v3_null(void);
int		v3_is_null(t_v v);
t_v		project_point(t_v point, t_camra camera);

// CAMERA.C
t_camra	camera_c(t_v pos, float eye_canv_dist, float fov);
t_v		camera_get_ac(t_camra camera);
t_v		camera_get_ab(t_camra camera);
t_plane	camera_get_canvas_plane(t_camra camera);
t_v		camera_get_center(t_camra camera);

// CAMERA2.C
t_v		camera_get_norm(t_camra camera);
void	camera_rotate(t_camra *camera,
			enum e_Direction direction, float amount);
void	camera_move(t_camra *camera, enum e_Direction direction, float amount);

// CAMERA3.C
t_v		get_point_canvas_rel(t_camra camera, t_v p);
t_v		camera_get_d(t_camra camera);

// ITEM.C
t_item	*create_item(enum e_ObjectType type,
			t_v3tpl pos_scale, t_v3tpl axe_color, t_fitpl sp_ch);
t_v		item_get_axis(t_item item);
void	item_draw_axes(t_rtdata data, t_item item);
t_uint	item_color_hex(t_item item);

// UTIL6.C
t_light	*light(enum e_LightType type, t_v color, t_v pos);
t_intsc	intersection(t_v pos, t_v normal, t_line ray, t_item *item);
t_v		mp_pto_phys(t_camra camera, t_v point, float ph_wdth, float ph_hght);
t_v		mp_phys_cam(t_camra camera, t_v point, float ph_wdth, float ph_hght);
t_v		v3_scale(t_v a, float scale);

// UTIL7.C
t_v		v3_invert(t_v a);
t_v		v3_abs(t_v a);
float	v3_len(t_v a);
t_v		v3_norm(t_v v);
float	v3_norm_squared(t_v v);

// UTIL8.C
t_v		v3_cross(t_v a, t_v b);
float	v3_dot(t_v a, t_v b);
t_v		project_point_onto_line(t_line line, t_v point);
float	point_plane_dist(t_v point, t_plane plane);
float	signed_point_plane_dist(t_v point, t_plane plane);

// UTIL9.C
t_v		project_point_onto_plane(t_v point, t_plane plane);
t_v		matrix_mult_vec(t_mtrx matrix, t_v v);
t_mtrx	matrix_scale(t_mtrx matrix, float scalar);
t_mtrx	matrix_mult(t_mtrx m1, t_mtrx m2);
t_mtrx	matrix_sub(t_mtrx m1, t_mtrx m2);

// UTIL 10.C
t_mtrx	get_identity_matrix(void);
t_v		get_cylinder_top(t_item cylinder);
t_v		get_cylinder_bottom(t_item cylinder);
t_v		intersect(t_line line, t_plane plane);
int		equals_with_tolerance(float val1, float val2);

// UTIL 11.C
int		vec_color_to_int(t_v color);
void	draw_line(t_scData *scrn, t_v p1, t_v p2, t_v color);
void	draw_square(t_scData *scrn, t_v pos, float size, t_v color);
void	draw_vect(t_scData *scrn, t_v v, t_v color);
void	connect_points(t_scData *scrn, t_v p1, t_v p2, t_item item);

// DRAW_LINE.C
void	draw_line_dda(t_scData *scrn, t_v p1, t_v p2, int color);

// UTIL12.C
void	fill_screen(t_scData *scrn, t_v color);
void	draw_segment(t_rtdata data, t_v p1, t_v p2, t_v color);
int		add_item(t_list **lst, t_elem *elem);
void	animate(t_rtdata data);
void	draw(t_rtdata data);

// UTIL13.C
t_v		color_from_int(int color);
void	sphere_vertices(t_v pos, t_v scale, t_item *item);
void	pyramid_vertices(t_v pos, t_v scale, t_item *item);
void	cube_vertices(t_v pos, t_v scale, t_item *item);
void	cylinder_vertices(t_v pos, t_v scale, t_item *item);

// UTIL14.C
void	draw_cube_mappings(t_scData *scrn, t_v mappings[34], t_item item);
void	draw_pyramid_mappings(t_scData *scrn, t_v mappings[34], t_item item);
void	draw_sphere_mappings(t_scData *scrn, t_v mappings[34], t_item item);
void	draw_cylinder_mappings(t_scData *scrn, t_v mappings[34], t_item item);

// UTIL15.C
void	move_item(t_item *item, t_v pos);
void	move_item_to(t_item *item, t_v pos);
void	rotate_item(t_item *item, t_v rot);
void	outline_item(t_rtdata data, t_item item);

// UTIL16.C
void	draw_mappings(t_rtdata data, t_item item, t_v mappings[34]);
t_line	*gen_rays(t_camra camera, int size, double resolution);
t_intsc	int_null(void );
int		int_is_null(t_intsc intersection);
t_intsc	intersect_ray_plane(t_line ray, t_plane plane);

// UTIL.17.C
t_intsc	intersect_ray_plane_item(t_line ray, t_item *plane);
t_intsc	intersect_ray_sphere(t_line ray, t_item *sphere);
int		point_inside_square(t_vec4 sqr, t_v point);
void	get_cube_squares(const t_item cube, t_v square_buffer[6][4]);
t_intsc	intersect_ray_cube(t_line ray, t_item *cube);

//UTIL18.C
t_intsc	int_create(t_v pos, t_v norm, t_line ray, t_item *item);
t_vec4	get_vec4(t_v p1, t_v p2, t_v p3, t_v p4);
int		point_inside_triangle(t_v s1, t_v s2, t_v s3, t_v point);
t_vec4	get_pyramid_base_square(t_item pyramid);
void	get_pyramid_triangles(const t_item pyramid, t_v tri_buffer[4][3]);

//UTIL19.C
t_intsc	intersect_ray_pyramid(t_line ray, t_item *pyramid);
t_intsc	ray_intersection(t_line ray, t_item *object);
t_v		compute_lighting(t_rtdata data, t_intsc intr, t_list *lights);

// UTIL20.C
t_intsc	intersect_ray_cylinder(t_line ray, t_item *cylinder);

// UTIL21.C
t_v		compute_specular(t_rtdata data, t_intsc intr, t_list *lights);
t_v		uv_at_chekers(t_v color1, t_v color2, t_v checkers_wh, t_v u_v);
t_v		spherical_map(t_v point, t_item sphere);
t_v		uv_at_image(t_image *rt_image, float u, float v);

// UTIL22.C
t_v		cylindrical_map(t_v point, t_item cylinder);

// UTIL23.C
t_v		get_item_color_image(t_intsc intr);
t_v		get_item_color(t_intsc intr);

// UTIL24.C
t_v		normalize_plane_point(t_v point, t_v origin, t_v normal);
t_v		cartesian_to_sphere(t_v point, t_item sphere);
t_v		chckr_pix_plan(t_v3tpl pt_orig, t_v normal, float step, t_v3tpl colors);
t_plane	get_intsc_plane(t_intsc intr);

// UTIL25.C
float	new_image_height(t_image *img, float new_width);
t_v		**get_pixels_from_image(t_image img, float target_width);
void	free_pixel_cache(t_v **cache);
t_v3tpl	tuple(t_v v1, t_v v2);

// UTIL 26.C
t_v		get_item_color_checkerboard(t_intsc intr);
t_intsc	cast_ray(t_rtdata data, t_line ray, int do_draw);
void	raytrace(t_rtdata data);
void	cast_ray_for_screen_coords(t_rtdata data, float x, float y);

// UTIL27.C
void	rotate_to_normal(t_item *item);

// UTIL28.C
t_line	gen_single_ray(t_camra camera, t_terms ts, double i, double j);
void	intsct_cube2(t_terms *ts, t_line ray, t_v cube_squares[6][4], int i);
void	g_intsc_pln2(t_plane *nearest_plane, t_v sq[6][4], int i, t_terms *ts);
void	cast_ray2(t_terms ts, t_rtdata data);

// UTIL29.C
double	get_resolution(void);
t_fitpl	floatint(float f, int i);
t_objty	get_item_type(t_elem *elem);
void	free_items(t_list **lst);

#endif // RT_HEAD_H
