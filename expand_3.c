	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loot_box.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdenou <aabdenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:14:01 by aabdenou          #+#    #+#             */
/*   Updated: 2024/08/13 16:27:26 by aabdenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_quote(t_lexer **lexer, char **str_to_expand)
{
	if (!(*lexer)->next)
	{
		*str_to_expand = ft_strdup("$");
		return (1);
	}
	if ((*lexer)->next->str[0] == '"' || (*lexer)->next->str[0] == '\'')
		(*lexer)->str = "";
	(*lexer) = (*lexer)->next;
	return (0);
}

char	*add_escape_characters(char *str)
{
	char	*newstr;

	int (i), (j), (len);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			len++;
		len++;
		i++;
	}
	newstr = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			newstr[j++] = 1;
		newstr[j] = str[i];
		j++;
		i++;
	}
	return (newstr[j] = '\0', newstr);
}

int	cheking_the_expand(char *str, t_env *env, int *i, char **str_to_expand)
{
	char	*key;
	char	*value;

	key = get_key(&str[*i]);
	value = get_value(env, key);
	*i += ft_strlen(key);
	if (value)
	{
		value = add_escape_characters(value);
		*str_to_expand = ft_strjoin(*str_to_expand, value);
	}
	return (0);
}

void	not_expandables(t_lexer **lexer)
{
	while ((*lexer)->next && (*lexer)->tokens != WORD)
		(*lexer) = (*lexer)->next;
	(*lexer) = (*lexer)->next;
}

void	expand_in_heredoc(char **str, t_env *env)
{
	int		i;
	char	*str_to_expand;

	str_to_expand = NULL;
	i = 0;
	while ((*str)[i] != '\0')
	{
		if (ft_strcmp(*str, "$") == 0)
		{
			*str = "$";
			return ;
		}
		if ((*str)[i] == '$' && ((*str)[i + 1] == '\'' || (*str)[i
				+ 1] == '\"'))
			dollar_and_quote(&str_to_expand, &i);
		if ((*str)[i] == '$' && ft_isdigit((*str)[i + 1])
			&& ft_strlen(*str) > 2)
			i += 2;
		if ((*str)[i] == '$' && ft_isalnum((*str)[i + 1]))
			(cheking_the_expand(*str, env, &i, &str_to_expand), i++);
		else
			special_case_in_heredoc(*str, &str_to_expand, &i);
	}
	*str = str_to_expand;
}
