/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfmakeimg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:48:43 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/15 22:38:45 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_writhelp(t_env *mx)
{
	int start;
	int i;

	start = 1;
	i = 18;
	mlx_string_put(mx->mlx, mx->win, 5, start + (i * 0),
		0xFFFFFF, "\"+/-\" - scaling");
	mlx_string_put(mx->mlx, mx->win, 5, start + (i * 1),
		0xFFFFFF, "\"Up, Down, Left, Right\" - moving");
	mlx_string_put(mx->mlx, mx->win, 5, start + (i * 2),
		0xFFFFFF, "\"NUM[824679]\" - rotation");
	mlx_string_put(mx->mlx, mx->win, 5, start + (i * 3),
		0xFFFFFF, "\"NUM5\" - on/off perspective");
	mlx_string_put(mx->mlx, mx->win, 5, start + (i * 4),
		0xFFFFFF, "\"NUM0\" - set to default");
	mlx_string_put(mx->mlx, mx->win, 5, start + (i * 5),
		0xFFFFFF, "\"Esc\" - exit");
}

static void	ft_calc_img_size(t_env *mx, int a, int b)
{
	int			scale;

	scale = mx->tr.scale;
	mx->img.l = ft_cmpdlt(a, mx->tr.min_y);
	mx->img.v = ft_cmpdlt(b, mx->tr.min_x);
	mx->img.l = (mx->img.l <= 0) ?
		mx->map->lnum * scale : mx->img.l + scale;
	mx->img.v = (mx->img.v <= 0) ?
		mx->map->vnum * scale : mx->img.v + scale;
}

static void	ft_get_img_size(t_env *mx)
{
	t_counters	t;
	t_ver		*res;

	ft_bzero(&t, sizeof(t_counters));
	mx->tr.min_x = 0;
	mx->tr.min_y = 0;
	if (mx->res)
		while (t.i < mx->map->lnum)
		{
			t.j = 0;
			while (t.j < mx->map->ln[t.i].num)
			{
				res = &(mx->res[(t.i * mx->map->vnum) + t.j]);
				mx->tr.min_x = (res->x < mx->tr.min_x) ? res->x : mx->tr.min_x;
				mx->tr.min_y = (res->y < mx->tr.min_y) ? res->y : mx->tr.min_y;
				t.x = (res->x > t.x) ? res->x : t.x;
				t.y = (res->y > t.y) ? res->y : t.y;
				t.j++;
			}
			t.i++;
		}
	ft_calc_img_size(mx, t.y, t.x);
}

static int	ft_init_img(t_env *mx)
{
	if (mx->img.ptr)
		mlx_destroy_image(mx->mlx, mx->img.ptr);
	ft_get_img_size(mx);
	if (!(mx->img.ptr = mlx_new_image(mx->mlx,
		mx->img.v, mx->img.l)))
		return (0);
	mx->img.bits_per_pix = sizeof(int) * 8;
	mx->img.size_line = sizeof(int) * mx->img.l;
	mx->img.endian = 0;
	if (!(mx->img.str = mlx_get_data_addr(mx->img.ptr,
		&(mx->img.bits_per_pix), &(mx->img.size_line), &(mx->img.endian))))
		return (0);
	return (1);
}

int			ft_drawimg(t_env *mx)
{
	int scale;

	scale = mx->tr.scale;
	mlx_clear_window(mx->mlx, mx->win);
	ft_calc_radians(mx);
	ft_fill_res(mx);
	if (!(ft_init_img(mx)))
		return (0);
	ft_put_res_to_img(mx);
	ft_put_lines_to_img(mx);
	mlx_put_image_to_window(mx->mlx, mx->win, mx->img.ptr,
		(mx->win_w / 2) - (mx->img.v / 2) + (mx->tr.v_start * scale),
		(mx->win_h / 2) - (mx->img.l / 2) + (mx->tr.l_start * scale));
	ft_writhelp(mx);
	return (1);
}
