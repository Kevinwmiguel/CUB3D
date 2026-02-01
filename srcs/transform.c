/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:06:51 by kwillian          #+#    #+#             */
/*   Updated: 2026/02/01 18:07:09 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	hex_to_int(const char *hex)
{
	char	tmp[3];
	int		r;
	int		g;
	int		b;

	if (ft_strlen(hex) != 6)
		return (0x000000);
	tmp[2] = '\0';
	tmp[0] = hex[0];
	tmp[1] = hex[1];
	r = (int)strtol(tmp, NULL, 16);
	tmp[0] = hex[2];
	tmp[1] = hex[3];
	g = (int)strtol(tmp, NULL, 16);
	tmp[0] = hex[4];
	tmp[1] = hex[5];
	b = (int)strtol(tmp, NULL, 16);
	return (r << 16 | g << 8 | b);
}
