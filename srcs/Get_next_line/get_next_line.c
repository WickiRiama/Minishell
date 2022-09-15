/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:22:05 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 15:59:55 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line(int fd)
{
	long int	ret;
	char		*buf;
	static char	*tail[256];
	char		*line;

	if (ft_check_fd(fd, tail) == 1)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	tail[fd] = ft_strjoin_free(tail[fd], "\0");
	line = ft_strdup(tail[fd]);
	ret = ft_readline(fd, &buf, &line);
	if (ret < 0 || !buf)
	{
		ft_clean_gnl(buf, tail[fd], line);
		return (NULL);
	}
	ft_setline(&line, &tail[fd]);
	if (ret == 0 && !tail[fd] && line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	free(buf);
	return (line);
}
