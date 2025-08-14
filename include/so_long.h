/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:14:00 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/14 17:43:49 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <stdbool.h>
# include <MLX42/MLX42.h>
# define TILE	64

typedef struct s_textures
{
	mlx_image_t	*grass;
	mlx_image_t	*wall;
	mlx_image_t	*exit;
	mlx_image_t	*collect;
	mlx_image_t	*player;
}	t_textures;

typedef struct s_player
{
	mlx_image_t	*right;
	mlx_image_t	*left;
	mlx_image_t	*front;
	mlx_image_t	*back;
	int			anim_frame;
	char		direction;
}	t_player;

typedef struct s_exit
{
	mlx_image_t	*sprites;
	int			exit_x;
	int			exit_y;
	int			anim_frame;
}	t_exit;

typedef struct s_map
{
	int		collectibles_counts;
	int		player_counts;
	int		exit_counts;
	int		height;
	int		width;
	char	**grid;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*player_img;
	mlx_image_t	*move_txt;
	t_map		map;
	t_player	player;
	t_exit		exit;
	t_textures	tx;
	void		*window;
	int			points;
	int			moves;
	int			player_x;
	int			player_y;
	int			screen_h;
	int			screen_w;
}	t_game;

//  Free the grid of the map structure.
void	free_grid(char **grid);

void	error_free(char *line, int fd, char *message);

// Free and returns when the parsers fails.
bool	cleanup_and_return(t_list **lst, t_map *map, bool status);

// Clean exit of the program.
void	ft_error(char *message);

// Functions to parse the maps.
bool	parse_map(char *file, t_map *map, t_list **lst);

// Function to create the array that is the map.
char	**create_array(t_list *list);

// Function that creates the grid and validates the player collectibles and exit.
bool	content_create(t_map *map, t_list *lines);

// Function that counts the elements in the lines inplace,
// when get_next_line reads.
bool	count_elements(t_map *map, char *line);

// Create the listt that contains a single line to create the arrays later.
// Update the lenght of the map. 
bool	create_lst(t_list **nodes, char *line, int *count);

// Function to determine if the map .name is valid
char	*check_file(char **argv);

// Function that verifies if the game is playable
bool	validate_path(t_game *game);

void	clean_exit(t_game *game, int code);

void	ft_key_hook(mlx_key_data_t keydata, void *param);

void	ft_close_window(void *param);

void	disable_collectible(t_game *game, int x, int y);

#endif