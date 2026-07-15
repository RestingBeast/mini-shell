#include "minishell.h"
#include <criterion/criterion.h>
#include <string.h>
#define SEG(txt, qte) ((t_segment){ .text = txt, .quote = qte })
#define TOK(lex, t) ((t_token){ .lexeme = lex, .type = t})

void	setup(void)
{
	printf("Starting Lexer test suite\n");
}

void	teardown(void)
{
	printf("Finished Lexer test suite\n");
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
			return (0);
		if (out[i]->quote != exp[i]->quote)
			return (0);
		if (strcmp(out[i]->text, exp[i]->text) != 0)
			return (0);
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
			return (0);
		if (out[i]->type != exp[i]->type)
			return (0);
		if (!compare_segment(out[i]->lexeme, exp[i]->lexeme))
			return (0);
		i++;
	}
	return (1);
}

t_token **mock_lex(void)
{
	t_token		**tokens;
	t_token		*tok;
	t_segment	**lexeme;
	t_segment	*seg;

	tokens = malloc(sizeof(t_token *) * 2);
	lexeme = malloc(sizeof(t_segment *) * 2);
	seg = malloc(sizeof(t_segment));
	tok = malloc(sizeof(t_token));

	if (!tokens || !lexeme || !seg || !tok)
		return (NULL);

	*seg = SEG("pwd", NONE);

	lexeme[0] = seg;
	lexeme[1] = NULL;

	*tok = TOK(lexeme, WORD);

	tokens[0] = tok;
	tokens[1] = NULL;

	return (tokens);
}

Test(Lexer, basic_test_1)
{
	t_segment seg1 = SEG("pwd", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token *expected[] = { &tok1, NULL };

	t_token	**tokens = mock_lex(); //lexer("pwd");

	cr_assert(
		compare_token(tokens, expected),
		"Test Failed: `pwd`"
	);
	//free_tokens(tokens);
	free(tokens[0]->lexeme[0]); // segment
	free(tokens[0]->lexeme);    // segment array
	free(tokens[0]);            // token
	free(tokens);               // token array
}

Test(Lexer, basic_test_2)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_segment seg2 = SEG("Hello, World", DOUBLE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);
	t_token *expected[] = { &tok1, &tok2, NULL };

	t_token	**tokens = lexer("echo \"Hello, World\"");

	cr_assert(
		compare_token(tokens, expected),
		"Test Failed: `echo \"Hello, World\"`"
	);
	//free_tokens(tokens);
}
