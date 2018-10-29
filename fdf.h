/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:55:19 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/16 20:10:07 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <mlx.h>

typedef struct	s_mod
{
	int		scale;
	int		x_ang;
	int		y_ang;
	int		z_ang;
	double	x_rad;
	double	y_rad;
	double	z_rad;
	int		l_start;
	int		v_start;
	int		min_x;
	int		min_y;
	double	z_len;
}				t_mod;

typedef struct	s_ver
{
	int			x;
	int			y;
	int			z;
	uint32_t	colr;
}				t_ver;

typedef struct	s_mapln
{
	int		num;
	t_ver	*ver;
}				t_mapln;

typedef struct	s_map
{
	int			vnum;
	int			lnum;
	t_mapln		*ln;
}				t_map;

typedef struct	s_img
{
	void	*ptr;
	char	*str;
	int		bits_per_pix;
	int		size_line;
	int		endian;
	int		l;
	int		v;
}				t_img;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	int		win_h;
	int		win_w;
	int		needperspect;
	t_map	*map;
	t_ver	*res;
	t_img	img;
	t_mod	tr;
}				t_env;

typedef struct	s_brez
{
	double		dx;
	double		dy;
	double		dlt;
	uint32_t	colr;
	int			colrstp;
	int			axis;
	t_ver		*a;
	t_ver		*b;
}				t_brez;

typedef struct	s_counters
{
	int			x;
	int			y;
	int			i;
	int			j;
	t_ver		*ver;
	t_ver		*res;
}				t_counters;

t_map			*ft_mapread(char *file);
void			ft_centering_map(t_map *mx);
char			*ft_skip_wspace(char *str);
int				ft_cmpdlt(int a, int b);
int				ft_atoibase(char *str, int base);
int				ft_zextr(t_map *map);
int				ft_keycatch(int keycode, t_env *mx);
int				ft_exit_x(t_env *mx);
void			ft_setmxdefault(t_env *mx);
int				ft_drawimg(t_env *mx);
void			ft_imgput(t_env *mx, int l, int v, uint32_t colr);
void			ft_drawbeam(t_env *mx, t_ver *a, t_ver *b);
void			ft_rotate_vertex(t_env *mx, t_ver *res);
void			ft_calc_radians(t_env *mx);
int				ft_put_res_to_img(t_env *mx);
int				ft_put_lines_to_img(t_env *mx);
int				ft_init_res(t_env *mx);
void			ft_fill_res(t_env *mx);
void			ft_perspective(t_env *mx);

#endif
