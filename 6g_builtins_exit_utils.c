/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6g_builtins_exit_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:31:12 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 10:08:41 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_sign_and_whitespace(char **str, int *sign)
{
	*sign = 1;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
}

int	convert_to_number(char *str, long long *number, int sign)
{
	long long	max_val;
	int			digit;

	*number = 0;
	if (sign == 1)
		max_val = LLONG_MAX;
	else
		max_val = -(LLONG_MIN + 1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		digit = *str - '0';
		if (*number > max_val / 10
			|| (*number == max_val / 10 && digit > max_val % 10))
			return (1);
		*number = *number * 10 + digit;
		str++;
	}
	*number *= sign;
	return (0);
}

long long	str_to_longlong_with_overflow_check(char *str, int *overflow)
{
	long long	number;
	int			sign;

	process_sign_and_whitespace(&str, &sign);
	*overflow = convert_to_number(str, &number, sign);
	return (number);
}

long	truncate_to_exit_code(long long number)
{
	if (number < 0)
		return (256 + number % 256);
	else
		return (number % 256);
}

int	validate_and_process_exit_code(char *input_str)
{
	long long	num;
	long		exit_code;
	int			overflow;

	overflow = 0;
	num = str_to_longlong_with_overflow_check(input_str, &overflow);
	if (overflow)
		return (-1);
	else
	{
		exit_code = truncate_to_exit_code(num);
		return (exit_code);
	}
}
