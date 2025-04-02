#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "/home/aelbour/MLX42/include/MLX42/MLX42.h"

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	if (!param)
		param = NULL;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");

	// If we RELEASE the 'K' key, print "World".
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");

	// If we HOLD the 'L' key, print "!".
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		puts("GOODBYE"), exit(1);
}

void my_scrollhook(double xdelta, double ydelta, void* param)
{
	if (!param)
		param = NULL;
	// Simple up or down detection.
	if (ydelta > 0)
		puts("Up!");
	else if (ydelta < 0)
		puts("Down!");
	
	// Can also detect a mousewheel that go along the X (e.g: MX Master 3)
	if (xdelta < 0)
		puts("Sliiiide to the left!");
	else if (xdelta > 0)
		puts("Sliiiide to the right!");
}

void ft_draw_rect(mlx_t *mlx, int32_t start, int32_t end)
{
	int x, y;

	x = start;
	mlx_image_t	*img = mlx_new_image(mlx, 1000, 1000);
	while(x <= end)
	{
		y = start;
		mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		mlx_put_pixel(img, x, y-1, 0xFFFFFFFF);
		mlx_put_pixel(img, x, y+1, 0xFFFFFFFF);
		while(y < end)
		{
			if (x == start || x == end)
			{
				mlx_put_pixel(img, x+1, y, 0xFFFFFF0);
				mlx_put_pixel(img, x, y, 0xFFFFFF0);
				mlx_put_pixel(img, x - 1, y, 0xFFFFFF0);

			}
			y++;
		}
		mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		mlx_put_pixel(img, x, y-1, 0xFFFFFFFF);
		mlx_put_pixel(img, x, y+1, 0xFFFFFFFF);
		x++;
	}

    mlx_image_to_window(mlx, img, 0, 0);
}

int32_t	main(void)
{
	mlx_t* mlx = mlx_init(1000, 1000, "AYMANE", true);
	if (!mlx)
		exit(EXIT_FAILURE);

	ft_draw_rect(mlx, 500, 998);

	// Run the main loop and terminate on quit.  
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_scroll_hook(mlx, &my_scrollhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
	}

// export LD_LIBRARY_PATH=$HOME/glfw_install/lib:$LD_LIBRARY_PATH