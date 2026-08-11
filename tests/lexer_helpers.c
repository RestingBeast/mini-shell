#include "test.h"

static const char	*quote_name(t_quote q)
{
	switch (q)
	{
		case NONE: return ("NONE");
		case SINGLE: return ("SINGLE");
		case DOUBLE: return ("DOUBLE");
	}
	return (NULL);
}

static int	compare_segments(t_list *out, t_list *exp)
{
	t_segment	*s1;
	t_segment	*s2;
	int			i;

	i = 0;
	while (out != NULL || exp != NULL)
	{
		if ((out && !exp) || (!out && exp))
			return (0);
		s1 = (t_segment *)out->content;
		s2 = (t_segment *)exp->content;
		if (s1->quote != s2->quote)
		{
			printf(
				"Segment #%d\n"
				"    Expected quote: %s\n"
				"    Actual quote:   %s\n",
				i + 1,
				quote_name(s2->quote),
				quote_name(s1->quote)
			);
			return (0);
		}
		if (strcmp(s1->text, s2->text) != 0)
		{
			printf(
				"Segment #%d\n"
				"    Expected text: %s\n"
				"    Actual text:   %s\n",
				i + 1,
				s2->text,
				s1->text
			);
			return (0);
		}
		out = out->next;
		exp = exp->next;
		i++;
	}
	return (1);
}

int	compare_tokens(t_list *out, t_list *exp)
{
	t_token	*t1;
	t_token	*t2;
	int		i;

	if (out == NULL)
		return (0);
	i = 0;
	while (out != NULL || exp != NULL)
	{
		if ((out && !exp) || (!out && exp))
			return (0);
		t1 = (t_token *)out->content;
		t2 = (t_token *)exp->content;
		if (t1->type != t2->type)
		{
			printf(
				"Token #%d\n"
				"    Expected type: %s\n"
				"    Actual type:   %s\n",
				i + 1,
				type_name(t2->type),
				type_name(t1->type)
			);
			return (0);
		}
		if (!compare_segments(t1->lexeme, t2->lexeme))
			return (0);
		out = out->next;
		exp = exp->next;
		i++;
	}
	return (1);
}
