/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:26:49 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 18:17:48 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	arg_checker(t_game *game, int argc, char **argv)
{
	(void) argv;
	if (argc < 2)
		ft_error(game, TOO_FEW_ARG);
	if (argc > 2)
		ft_error(game, TOO_MUCH_ARG);
}

void	parsing(t_game *game, int argc, char **argv)
{
	arg_checker(game, argc, argv);
}
