/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:10:22 by tsaby             #+#    #+#             */
/*   Updated: 2025/01/20 16:08:18 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_collectable(t_gamestruct *solong, int x, int y)
{
	mlx_put_image_to_window(solong->mlx, solong->windows, solong->c, y * 120, x
		* 120);
}

void	print_player(t_gamestruct *solong, int x, int y)
{
	mlx_put_image_to_window(solong->mlx, solong->windows, solong->player, y
		* 120, x * 120);
}

void	define_image(t_gamestruct *solong)
{
	int	i;
	int	j;

	solong->empty = mlx_xpm_file_to_image(solong->mlx, "img/empty.xpm", &i, &j);
	if (!solong->empty)
		free_exit(solong);
	solong->wall = mlx_xpm_file_to_image(solong->mlx, "img/wall.xpm", &i, &j);
	if (!solong->wall)
		free_exit(solong);
	solong->player = mlx_xpm_file_to_image(solong->mlx, "img/char.xpm", &i, &j);
	if (!solong->player)
		free_exit(solong);
	solong->c = mlx_xpm_file_to_image(solong->mlx, "img/c.xpm", &i, &j);
	if (!solong->c)
		free_exit(solong);
	solong->exit = mlx_xpm_file_to_image(solong->mlx, "img/exit.xpm", &i, &j);
	if (!solong->exit)
		free_exit(solong);
	solong->open = mlx_xpm_file_to_image(solong->mlx, "img/open.xpm", &i, &j);
	if (!solong->open)
		free_exit(solong);
}

void	print_image(t_gamestruct *solong)
{
	int		x;
	int		y;
	char	*step;

	step = ft_itoa(solong->step);
	if (!step)
		free_exit(solong);
	x = 0;
	while (x < solong->hmap)
	{
		y = 0;
		while (y < solong->wmap)
		{
			case_print(solong, x, y);
			y++;
		}
		x++;
	}
	mlx_string_put(solong->mlx, solong->windows, 150, 150, 0xFFFFFF, step);
	ft_printf("You have done %d step\n", solong->step);
	free(step);
}

void	case_print(t_gamestruct *solong, int x, int y)
{
	if (solong->map[x][y] == '1')
		mlx_put_image_to_window(solong->mlx, solong->windows, solong->wall, y
			* 120, x * 120);
	if (solong->map[x][y] == '0')
		mlx_put_image_to_window(solong->mlx, solong->windows, solong->empty, y
			* 120, x * 120);
	if (solong->map[x][y] == 'C')
		print_collectable(solong, x, y);
	if (solong->map[x][y] == 'P')
		print_player(solong, x, y);
	if (solong->map[x][y] == 'E')
		mlx_put_image_to_window(solong->mlx, solong->windows, solong->exit, y
			* 120, x * 120);
	if (solong->map[x][y] == 'E' && solong->ccount == 0)
		mlx_put_image_to_window(solong->mlx, solong->windows, solong->open, y
			* 120, x * 120);
}
