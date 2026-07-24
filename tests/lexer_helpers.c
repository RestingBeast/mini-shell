#include "unit_test.h"

const char	*quote_name(enum Quote q)
{
	switch (q)
	{
		case NONE: return ("NONE");
		case SINGLE: return ("SINGLE");
		case DOUBLE: return ("DOUBLE");
	}
	return (NULL);
}

const char	*type_name(enum Type t)
{
	switch (t)
	{
		case WORD: return ("WORD");
		case PIPE: return ("PIPE");
		case REDIRECT_IN: return ("REDIRECT_IN");
		case REDIRECT_OUT: return ("REDIRECT_OUT");
		case HEREDOC: return ("HEREDOC");
		case APPEND: return ("APPEND");
	}
	return (NULL);
}

int	compare_segment(t_segment **out, t_segment **exp)
{
	int	i;

	if (out == NULL)
		return (0);
	i = 0;
	while (out[i] != NULL || exp[i] != NULL)
	{
		if (out[i] == NULL || exp[i] == NULL)
		{
			printf(
				"Segment #%d\n\tLexeme Length is not the same\n"
				"",
				(i + 1)
			);
			return (0);
		}
		if (out[i]->quote != exp[i]->quote)
		{
			printf(
				"Segment #%d\n"
				"    Expected quote: %s\n"
				"    Actual quote:   %s\n",
				i + 1,
				quote_name(exp[i]->quote),
				quote_name(out[i]->quote)
			);
			return (0);
		}
		if (strcmp(out[i]->text, exp[i]->text) != 0)
		{
			printf(
				"Segment #%d\n"
				"    Expected text: %s\n"
				"    Actual text:   %s\n",
				i + 1,
				exp[i]->text,
				out[i]->text
			);
			return (0);
		}
		i++;
	}
	return (1);
}

int	compare_token(t_token **out, t_token **exp)
{
	int	i;

	if (out == NULL)
		return (0);
	i = 0;
	while (out[i] != NULL || exp[i] != NULL)
	{
		if (out[i] == NULL || exp[i] == NULL)
		{
			printf(
				"Token #%d\n\tToken Length is not the same\n",
				(i + 1)
			);
			return (0);
		}
		if (out[i]->type != exp[i]->type)
		{
			printf(
				"Token #%d\n"
				"    Expected type: %s\n"
				"    Actual type:   %s\n",
				i + 1,
				type_name(exp[i]->type),
				type_name(out[i]->type)
			);
			return (0);
		}
		if (!compare_segment(out[i]->lexeme, exp[i]->lexeme))
			return (0);
		i++;
	}
	return (1);
}
