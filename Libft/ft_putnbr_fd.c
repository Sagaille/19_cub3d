/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:09:52 by ldavids           #+#    #+#             */
/*   Updated: 2020/10/10 23:54:02 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned	int sign;

	if (fd < 0 || fd > 200)
		return ;
	sign = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -n;
	}
	if (sign >= 10)
		ft_putnbr_fd(sign / 10, fd);
	ft_putchar_fd(sign % 10 + '0', fd);
}
