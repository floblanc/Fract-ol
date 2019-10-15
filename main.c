/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:17 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/13 21:22:14 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		ft_affich(t_data *data)
{
	ft_mandelbrot(data, (data->x_b - data->x_a), (data->y_b - data->y_a));
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->p_img, 0, 0);
	// printf("data->mouse_button = %d\n", data->mouse_button);
	return (0);
}

void	ft_screen(t_data *data)
{
	t_tga	tga;
	int		fd;
	// int		print[FENETRE_X * FENETRE_Y * 4];
	int		*print;
	int		mode_tmp;

	print = (int*)malloc(sizeof(int) * (FENETRE_X * FENETRE_Y * 4));
	mode_tmp = data->mode;
	data->mode = 0;
	ft_affich(data);
	data->mode = mode_tmp;

	tga.id_length = 0;
	tga.colour_map = 0;
	tga.data_type = 2;
	tga.colour_origin = 0;
	tga.colour_length = 0;
	tga.colour_depth = 0;
	tga.x_origin = 0;
	tga.y_origin = 0;
	tga.width = FENETRE_X;
	tga.height = FENETRE_Y;
	tga.bpp = 8 * 4;
	tga.imagedescriptor = 32;
	fd = open("a.tga", O_RDWR | O_CREAT , 0777);
	write(fd, &tga, 7);
	write(fd, &tga.colour_depth, 1);
	write(fd, &tga.x_origin, 10);
	for (int i = 0; i < FENETRE_X * FENETRE_Y; i++)
		print[i] = data->img[i] + 0xFF000000;
	if (write(fd, print, FENETRE_X * FENETRE_Y * 4) == -1)
		perror("Error : ");
	close(fd);
	free(print);
}

int		red_cross(t_data *data)
{
	exit(0);
	return (0);
}


void	ft_start_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
	data->p_img = mlx_new_image(data->mlx_ptr, FENETRE_X, FENETRE_Y);
	data->img = (int*)mlx_get_data_addr(data->p_img, &data->p.bpp, &data->p.sl, &data->p.endian);
	data->p.bpp /= 4;
	data->p.sl /= 4;
	data->zoom = 5;
	data->move_x = 0;
	data->move_y = 0;
	data->iteration_max = 20;
	data->mode = 0;
	data->fix = 0;
	data->x = 0;
	data->y = 0;
	data->x_a = -2.1;
	data->x_b = 0.6;
	data->y_a = -1.2;
	data->y_b = 1.2;
	data->div_q = 1;
	data->div = data->iteration_max / data->div_q;
	data->step_x = (data->x_b - data->x_a) * 0.01;
	data->step_y = (data->y_b - data->y_a) * 0.01;
	data->mouse_button = 0;
	data->mouse_x = 0;
	data->mouse_y = 0;
	data->mouse_z = 0;
}

int		main(int argc, char **argv)
{
	t_data		data;

	a = 0.5;
	b = 0.5;
	data.fract = 0;
	ft_start_data(&data);
	// ft_base(argv[1], &val);
	// mlx_hook(val.mlx[1], 2, 0, &ft_key_on, &val);
	mlx_hook(data.win_ptr, 2, 0, &ft_key, &data);
	mlx_loop_hook(data.mlx_ptr, &ft_affich, &data);
	mlx_hook(data.win_ptr, 6, 0, mouse_release_hook, &data);
	mlx_hook(data.win_ptr, 5, 0, &mouse_release, &data);
	mlx_mouse_hook(data.win_ptr, &mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, red_cross, &data);
	
	mlx_loop(data.mlx_ptr);
	return (0);
}

// gcc -lmlx -framework OpenGL -framework AppKit main.c ft_mandelbrot.c
// man /usr/share/man/man3/
