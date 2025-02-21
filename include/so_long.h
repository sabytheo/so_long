/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:04 by tsaby             #+#    #+#             */
/*   Updated: 2025/01/21 15:24:35 by tsaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	BUTTON_PRESS_MASK = 1L<<2,
	W = 119,
	S = 115,
	D = 100,
	A = 97,
	ESCAPE = 65307
};

typedef struct s_gamestruct
{
	int		fd;
	int		hmap;
	int		wmap;

	int		pcount;
	int		ccount;
	int		ecount;

	int		pos_x;
	int		pos_y;

	int		step;

	char	**map;
	char	**map_copy;

	void	*open;
	void	*empty;
	void	*wall;
	void	*exit;
	void	*player;
	void	*c;

	void	*mlx;
	void	*windows;

}			t_gamestruct;

int			open_map(t_gamestruct *solong, char **argv);
void		check_errors(t_gamestruct *solong);
void		define_image(t_gamestruct *solong);
void		print_image(t_gamestruct *solong);
void		case_print(t_gamestruct *solong, int x, int y);
int			define_control(int keypress, t_gamestruct *solong);
int			free_exit(t_gamestruct *solong);
int			check_path(t_gamestruct *solong);

#endif
