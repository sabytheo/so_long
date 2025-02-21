/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 09:50:27 by tsaby             #+#    #+#             */
/*   Updated: 2025/01/21 15:25:18 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_arg(char *mapname)
{
	char	*s;

	s = ".ber\0";
	if ((ft_strncmp(ft_strchr(mapname, '.'), s, 5)) != 0)
	{
		write(2, "File extension must be .ber\n", 28);
		exit(0);
	}
}

void	free_images(t_gamestruct *solong)
{
	if (solong->open)
		mlx_destroy_image(solong->mlx, solong->open);
	if (solong->empty)
		mlx_destroy_image(solong->mlx, solong->empty);
	if (solong->wall)
		mlx_destroy_image(solong->mlx, solong->wall);
	if (solong->exit)
		mlx_destroy_image(solong->mlx, solong->exit);
	if (solong->player)
		mlx_destroy_image(solong->mlx, solong->player);
	if (solong->c)
		mlx_destroy_image(solong->mlx, solong->c);
}

int	free_exit(t_gamestruct *solong)
{
	int	line;

	line = 0;
	free_images(solong);
	if (solong->windows)
		mlx_destroy_window(solong->mlx, solong->windows);
	if (solong->mlx)
	{
		mlx_destroy_display(solong->mlx);
		free(solong->mlx);
	}
	if (solong->map)
	{
		while (line < solong->hmap)
			free(solong->map[line++]);
		free(solong->map);
	}
	if (solong->fd > 0)
		close(solong->fd);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_gamestruct	solong;

	if (argc != 2)
	{
		write(2, "Number of arguments invalid\n", 28);
		exit(0);
	}
	check_arg(argv[1]);
	ft_memset(&solong, 0, sizeof(t_gamestruct));
	open_map(&solong, argv);
	check_errors(&solong);
	solong.mlx = mlx_init();
	if (!solong.mlx)
		return (0);
	solong.windows = mlx_new_window(solong.mlx, 120 * solong.wmap, 120
			* solong.hmap, "SO_LONG_ISAAC");
	define_image(&solong);
	print_image(&solong);
	mlx_key_hook(solong.windows, define_control, &solong);
	mlx_hook(solong.windows, ON_DESTROY, BUTTON_PRESS_MASK, free_exit, &solong);
	mlx_loop(solong.mlx);
}
