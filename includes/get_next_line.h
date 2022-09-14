/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:33:21 by mriant            #+#    #+#             */
/*   Updated: 2022/03/04 15:45:00 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> //NULL malloc free
# include <sys/types.h> // open read
# include <sys/uio.h> // read
# include <unistd.h> // read
# include <stdio.h> // printf
# include <sys/stat.h> // open
# include <fcntl.h> // open

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin_free(char *s, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
long int	ft_readline(int fd, char **buf, char **line);
void		ft_setline(char **line, char **tail);

#endif
