/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:19:24 by aabdenou          #+#    #+#             */
/*   Updated: 2024/10/01 17:35:53 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			if (!env->value)
				return (ft_strdup(""));
			else
				return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*to_expand(char *str)
{
	int	i;
	int	start;
	int	end;

	i = 1;
	start = i;
	while (str[i] && ft_isalnum(str[i]))
	{
		if (str[i] == '?' && str[i + 1])
			return (ft_strdup("?"));
		i++;
	}
	end = i;
	return (ft_substr(str, start, end - start));
}

int	check_quotes_in_expand(char *str)
{
	if (str[0] == '"' || str[0] == '\'')
		return (1);
	return (0);
}

void	expand_helper(t_lexer **lexer, t_env *env, char **str_to_expand)
{
	int	i;

	i = 0;
	while ((*lexer)->str[i])
	{
		if (ft_strcmp((*lexer)->str, "$") == 0)
		{
			if (quote_after_dollar(lexer, str_to_expand))
				break ;
		}
		else if ((*lexer)->str[i] == '$' && (ft_isdigit((*lexer)->str[i + 1])
				&& (ft_strlen((*lexer)->str) > 2)))
			i += 2;
		else if ((*lexer)->str[i] == '$' && (ft_isalnum((*lexer)->str[i + 1])))
		{
			probability_to_expand((*lexer)->str, env, &i, str_to_expand);
			i++;
		}
		else
			special_case(*lexer, str_to_expand, &i);
	}
}

void expand(t_lexer *lexer, t_env *env)
{
	char	*str_to_expand;

	while (lexer)
	{
		str_to_expand = NULL;
		if (lexer->tokens == HEREDOC)
		{
			dont_expand(&lexer);
			continue ;
		}
		else if (lexer->tokens == WORD && lexer->str[0] != '\'')
		{
			expand_helper(&lexer, env, &str_to_expand);
			lexer->str = str_to_expand;
		}
		printf("expanded ==== %s\n",lexer->str);
		lexer = lexer->next;
	}
}