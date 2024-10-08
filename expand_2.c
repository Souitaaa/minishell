/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loot_box_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:13:28 by aabdenou          #+#    #+#             */
/*   Updated: 2024/10/01 16:53:42 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_and_quote(char **str_to_expand, int *i)
{
	*str_to_expand = ft_strjoin(*str_to_expand, "$");
	(*i)++;
}

void	special_case_in_heredoc(char *str, char **str_to_expand, int *i)
{
	char	tmp[2];

	tmp[0] = str[(*i)++];
	tmp[1] = '\0';
	*str_to_expand = ft_strjoin(*str_to_expand, tmp);
}

char	**get_key_before_expand(void)
{
	static char	*key;

	return (&key);
}

void	special_case(t_lexer *lexer, char **str_to_expand, int *i)
{
	char	tmp[2];

	tmp[0] = lexer->str[(*i)++];
	tmp[1] = '\0';
	*str_to_expand = ft_strjoin(*str_to_expand, tmp);
}
