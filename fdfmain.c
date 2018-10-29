/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akokoshk <akokoshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 20:33:20 by akokoshk          #+#    #+#             */
/*   Updated: 2018/01/16 22:02:11 by akokoshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void	ft_setmxdefault(t_env *mx)
{
	mx->tr.scale = 1;
	mx->tr.l_start = 0;
	mx->tr.v_start = 0;
	mx->tr.x_ang = -15;
	mx->tr.y_ang = -10;
	mx->tr.z_ang = 20;
	mx->tr.x_rad = 0;
	mx->tr.y_rad = 0;
	mx->tr.z_rad = 0;
	mx->tr.min_x = (mx->map) ? (mx->map->lnum * mx->tr.scale) / 2 : 0;
	mx->tr.min_y = (mx->map) ? (mx->map->vnum * mx->tr.scale) / 2 : 0;
	mx->tr.z_len = 0;
	mx->needperspect = 0;
}

t_env	*ft_init_mlx(void)
{
	t_env	*mx;

	if (!(mx = ft_memalloc(sizeof(t_env))))
		return (NULL);
	mx->win_h = 700;
	mx->win_w = 900;
	mx->mlx = mlx_init();
	if (!(mx->win = mlx_new_window(mx->mlx,
		mx->win_w, mx->win_h, "akokoshk's FDF")))
		return (NULL);
	ft_setmxdefault(mx);
	return (mx);
}

int		main(int ac, char **av)
{
	t_env	*mx;

	if (!(mx = ft_init_mlx()))
		return (0);
	if (ac == 1)
		ft_putstr("Usage : ./fdf <filename>\n");
	else if (!(mx->map = ft_mapread(av[1])))
		return (0);
	else
	{
		mx->tr.scale += (mx->map->lnum < (mx->win_h / 3)
			&& mx->map->vnum < (mx->win_w / 3)) ? 2 : 0;
		ft_centering_map(mx->map);
		ft_init_res(mx);
		if (!(ft_drawimg(mx)))
			exit(0);
		mlx_hook(mx->win, 2, 0, ft_keycatch, mx);
		mlx_hook(mx->win, 17, 1L << 17, ft_exit_x, mx);
		mlx_loop(mx->mlx);
	}
	return (0);
}
