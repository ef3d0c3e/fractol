/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ARGS_H
# define ARGS_H

# include <util/pos.h>

/**
 * @brief Displays program usage and exit
 */
void
print_usage(const char *program);
/**
 * @brief Displays program help and usage, then exit
 */
void
print_help(const char *program);
/**
 * @brief Displays program version and exit
 */
void
print_version(void);
void
/**
 * @brief Parses the program's positional arguments or exit
 */
parse_positional(
	const char *program,
	const char *s,
	int *positional,
	t_pos *win_size);
/**
 * @brief Parses the downsampling amount, or exit
 */
int
parse_downsampling(const char *s);
/**
 * @brief Parses the kernel id, or exit
 */
int
parse_kernel(const char *s);
/**
 * @brief Parses the oversampling amount
 */
int
parse_oversampling(const char *s);

#endif // ARGS_H
