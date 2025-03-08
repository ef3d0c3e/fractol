/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_args.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PRINTF_ARGS_H
# define PRINTF_ARGS_H

# include <ft_printf.h>

/**
 * @brief Prints repeated character
 *
 * @param fd The file descriptir to print to
 * @param pad The character used for padding
 * @param width The number of padding characters to print
 *
 * @returns The number of written characters, i.g `(width > 0) ? width : 0`
 */
int					__printf_pad(int fd, char pad, int width);
/**
 * @brief Returns the maximum between two operands
 *
 * @param x The first parameter
 * @param y The second parameter
 *
 * @returns `(x >= y) ? x : y`
 */
int					__printf_max(int x, int y);
/**
 * @brief Returns the minimum between two operands
 *
 * @param x The first parameter
 * @param y The second parameter
 *
 * @returns `(x >= y) ? y : x`
 */
int					__printf_min(int x, int y);
/**
 * @brief strlen for printf
 *
 * @param s The string to get the length of
 *
 * @returns The length of s
 */
int					__printf_strlen(const char *s);
/**
 * @brief strlen for printf
 *
 * @param s The string to get the length of
 *
 * @returns The length of s
 */
char				*__printf_strchr(const char *s, int c);

/**
 * @brief The type of padding
 */
enum e_printf_padding
{
	/**
	 * @brief Pad to the left (default)
	 */
	PRINTF_PADDING_LEFT,
	/**
	 * @brief Pad to the right
	 */
	PRINTF_PADDING_RIGHT,
	/**
	 * @brief Pad with leading zeros (numbers only)
	 */
	PRINTF_PADDING_ZEROS,
};

/**
 * @brief Formatting for a printf argument
 */
struct s_printf_fmt
{
	/**
	 * @brief The padding type
	 */
	enum e_printf_padding	padding;
	/**
	 * @brief Padding width
	 */
	int						width;
	/**
	 * @brief Use the alternate display form, i.e '#'
	 */
	int						alternate_form;	
	/**
	 * @brief The number indicating the precision.
	 */
	int						precision;
	/**
	 * @brief Flag that indicates that the format has precision
	 */
	int						has_precision;
	/**
	 * @brief Force the sign to be displayed,
	 * i.e '+' for positive numbers.
	 */
	int						force_sign;
	/**
	 * @brief Flag to indicate the number conversion has a space,
	 * therefore a space should be added before the number if it is
	 * positive (none if negative) and be accounted for padding.
	 */
	int						has_space;
};

/**
 * @brief Internal function that parses formatting arguments after the `%` sign
 *
 * @param s The string after a `%` sign
 *
 * @returns A newly created @ref s_printf_fmt
 *
 * @note In case the argument is incorrect, or defines parameters for the wrong
 * conversion, the behaviour of `printf()` is undefined.
 */
struct s_printf_fmt	__printf_parse_fmt(const char **s);

int					__printf_process_arg(
						int fd,
						const char **s,
						va_list ap
						);

/**
 * @brief Prints a character to the file descriptor
 *
 * When using `%c`, printf first converts the argument to `int`, then to
 * `unsigned char`
 *
 * @param fd The file descriptor to print to
 * @param fmt The formatting structure
 * @param c The charater to print
 *
 * @returns The number of written characters
 *
 * @note The fmt argument may be null, in which case this function is
 * equivalent to `write(fd, &c, 1)`
 */
int					__printf_print_char(
						int fd,
						struct s_printf_fmt *fmt,
						unsigned char c
						);
/**
 * @brief Prints a signed integer to the file descriptor
 *
 * @param fd The file descriptor to print to
 * @param fmt The formatting structure
 * @param x The signed integer to print
 *
 * @returns The number of written characters
 */
int					__printf_print_int(
						int fd,
						struct s_printf_fmt *fmt,
						int x
						);
/**
 * @brief Prints an unsigned integer to the file descriptor
 *
 * @param fd The file descriptor to print to
 * @param fmt The formatting structure
 * @param x The unsigned integer to print
 *
 * @returns The number of written characters
 */
int					__printf_print_unsigned(
						int fd,
						struct s_printf_fmt *fmt,
						unsigned int x
						);

/**
 * @brief Prints a string to the file descriptor
 *
 * @param fd The file descriptor to print to
 * @param fmt The formatting structure
 * @param s The string to print
 *
 * @returns The number of written characters
 *
 * @note The fmt argument may be null, in which case this function is
 * equivalent to `write(fd, s, strlen(s))`
 */
int					__printf_print_string(
						int fd,
						struct s_printf_fmt *fmt,
						const char *s
						);

/**
 * @brief Prints an unsigned number as hexadecimal
 *
 * @param fd The file descriptor to print to
 * @param fmt The formatting structure
 * @param x The value to print
 * @param uppercase Whether to print as uppercase
 *
 * @returns The number of written characters
 */
int					__printf_print_hex(
						int fd,
						struct s_printf_fmt *fmt,
						unsigned int x,
						int uppercase
						);

/**
 * @brief Prints a pointer as hexadecimal, prefixed with '0x'
 *
 * @param fd The file descriptor to print to
 * @param fmt The formatting structure
 * @param p The pointer to print
 *
 * @returns The number of written characters
 */
int					__printf_print_ptr(
						int fd,
						struct s_printf_fmt *fmt,
						void *p
						);

#endif // PRINTF_ARGS_H
