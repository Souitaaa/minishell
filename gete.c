/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gete.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:03:29 by csouita           #+#    #+#             */
/*   Updated: 2024/10/22 22:31:52 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_pos = 0;
    static int buffer_size = 0;
    char *line = NULL;
    int line_pos = 0;
    char c;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);

    line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!line)
        return (NULL);

    while (1)
    {
        if (buffer_pos >= buffer_size)
        {
            buffer_size = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_size <= 0)
                break;
        }

        c = buffer[buffer_pos++];
        line[line_pos++] = c;

        if (c == '\n')
            break;

        if (line_pos >= BUFFER_SIZE)
            break;
    }

    if (line_pos == 0)
    {
        free(line);
        return (NULL);
    }

    line[line_pos] = '\0';
    return (line);
}

main