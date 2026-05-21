/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:12:33 by kwillian          #+#    #+#             */
/*   Updated: 2026/05/18 16:22:49 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	valid_elements(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	is_valid_wall(char c)
{
	return (c == '1');
}
