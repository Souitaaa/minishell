/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:13:52 by csouita           #+#    #+#             */
/*   Updated: 2024/07/19 15:44:13 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_spaces(t_data *data) 
{
    int i = 0;
    int len = ft_strlen(data->line);

    while (i < len) 
    {
        while(data->line[i] == 32)
            i++;
        if ((data->line[i] == '>' && data->line[i + 1] == '>') || (data->line[i] == '<' && data->line[i + 1] == '<')) 
        {
            write(1, " ", 1);
            write(1, &data->line[i], 2);
            write(1, " ", 1);
            i += 2;
        }
        else if (data->line[i] == '>' || data->line[i] == '<' || data->line[i] == '|') 
        {
            write(1, " ", 1);
            write(1, &data->line[i], 1);
            write(1, " ", 1);
            i++;
        }
        else 
        {
            //men ba3d o n3awed had l3iba
            if (i > 0 && (data->line[i - 1] == '>' || data->line[i - 1] == '<' || data->line[i - 1] == '|') && data->line[i] == 32)
                write(1, &data->line[i], 1);
            else 
                write(1, &data->line[i], 1);
            i++;
        }
    }
}

void lexer(t_data *data)
{
    
    int i = 0;
    add_spaces(data->line);
    
    while(data->line[i])
    {
        if (data->line[i] == '|')
        {
            write(1,"PIPE\n",5);
            i++;
        }
        else if (data->line[i] == '>' && data->line[i + 1] == '>')
        {
            write(1,"append\n",8);
            i = i+2;
        }
        else if (data->line[i] == '<' && data->line[i + 1] == '<')
        {
            write(1,"HERDOC\n",8);
            i = i+2;
        }
        else if (data->line[i] == '>')
        {
            write(1,"readin\n",8);
            i++;
        }
        else if (data->line[i] == '<')
        {
            write(1,"readout\n",9);
            i++;
        }
        else 
            {
                while(data->line[i] != '>' && data->line[i] != '<' && data->line[i] != '|' && data->line[i])
                    i++;
                write(1,"Word\n",5);
            }
    }
}

