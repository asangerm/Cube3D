/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:31:18 by nfradet           #+#    #+#             */
/*   Updated: 2024/07/02 21:27:10 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void  init_textures_game(t_game *game)
{
    t_textures  tex;

    tex.so.img = NULL;
    tex.so.height = 0;
    tex.so.width = 0;
    tex.so.data = NULL;
    tex.so.bpp = 0;
    tex.so.size_line = 0;
    tex.so.endian = 0;
    game->textures = tex;
}

void  create_mlx_textures(t_game *game)
{
    t_info      info;
    // t_textures  tex;

    init_textures_game(game);
    info = game->map.map_info;
    // tex = game->textures;
    // ft_printf("path to south: %s\n", info.so_path);
    // ft_printf("mlx==NULL: %p\n", game->mlx);
    game->textures.so.img = mlx_xpm_file_to_image(game->mlx, info.so_path, &game->textures.so.width, &game->textures.so.height);
    if (game->textures.so.img == NULL)
		  ft_error(game, LOADING_TEX);
    // ft_printf("so.image.height :%d\n", game->textures.so.height);
    // ft_printf("path to north: %s\n", info.no_path);
    game->textures.no.img = mlx_xpm_file_to_image(game->mlx, info.no_path, &game->textures.no.width, &game->textures.no.height);
    if (game->textures.no.img == NULL)
		  ft_error(game, LOADING_TEX);

    // ft_printf("path to east: %s\n", info.ea_path);
    game->textures.ea.img = mlx_xpm_file_to_image(game->mlx, info.ea_path, &game->textures.ea.width, &game->textures.ea.height);
    if (game->textures.ea.img == NULL)
		  ft_error(game, LOADING_TEX);

    // ft_printf("path to west: %s\n", info.we_path);
    game->textures.we.img = mlx_xpm_file_to_image(game->mlx, info.we_path, &game->textures.we.width, &game->textures.we.height);
    if (game->textures.we.img == NULL)
		  ft_error(game, LOADING_TEX);
    
    game->textures.so.data = (int *)mlx_get_data_addr(game->textures.so.img, &game->textures.so.bpp, &game->textures.so.size_line, &game->textures.so.endian);
    game->textures.no.data = (int *)mlx_get_data_addr(game->textures.no.img, &game->textures.no.bpp, &game->textures.no.size_line, &game->textures.no.endian);
    game->textures.ea.data = (int *)mlx_get_data_addr(game->textures.ea.img, &game->textures.ea.bpp, &game->textures.ea.size_line, &game->textures.ea.endian);
    game->textures.we.data = (int *)mlx_get_data_addr(game->textures.we.img, &game->textures.we.bpp, &game->textures.we.size_line, &game->textures.we.endian);
}
