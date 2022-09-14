/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:33:21 by mriant            #+#    #+#             */
/*   Updated: 2022/09/14 17:01:19 by mriant           ###   ########.fr       */
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
char		*ft_strjoin_free(char *s, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
long int	ft_readline(int fd, char **buf, char **line);
void		ft_setline(char **line, char **tail);
int			ft_check_fd(int fd, char *tail[256]);
void		ft_clean_gnl(char *buf, char *tail, char *line);

#endif
