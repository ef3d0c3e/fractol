/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

/**
 * @brief Displays text according to a format string
 *
 * @param fmt The format string
 * @param ... The parameters
 *
 * @returns The number of characters written
 *
 * @warn If the format string is invalid, or a conversion has to the wrong
 * parameter, the result is undefined
 */
int					ft_printf(const char *fmt, ...);
/**
 * @brief Displays text according to a format string
 *
 * @param fmt The format string
 * @param pa The parameters
 *
 * @returns The number of characters written
 *
 * @warn If the format string is invalid, or a conversion has to the wrong
 * parameter, the result is undefined
 */
int					ft_vprintf(const char *fmt, va_list pa);
/**
 * @brief Displays text according to a format string
 *
 * @param fd The file descriptor to write to
 * @param fmt The format string
 * @param ... The parameters
 *
 * @returns The number of characters written
 *
 * @warn If the format string is invalid, or a conversion has to the wrong
 * parameter, the result is undefined
 */
int					ft_dprintf(int fd, const char *fmt, ...);
/**
 * @brief Displays text according to a format string
 *
 * @param fd The file descriptor to write to
 * @param fmt The format string
 * @param pa The parameters
 *
 * @returns The number of characters written
 *
 * @warn If the format string is invalid, or a conversion has to the wrong
 * parameter, the result is undefined
 */
int					ft_vdprintf(int fd, const char *fmt, va_list pa);

#endif // FT_PRINTF_H
