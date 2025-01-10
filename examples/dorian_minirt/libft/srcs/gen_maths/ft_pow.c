/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:26:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/26 13:42:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_powerf(double x, int exp)
{
	double	temp;

	if (exp == 0)
		return (1);
	temp = ft_powerf (x, exp / 2);
	if ((exp % 2) == 0)
		return (temp * temp);
	else
	{
		if (exp > 0)
			return (x * temp * temp);
		else
			return ((temp * temp) / x);
	}
}
