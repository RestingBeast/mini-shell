#include "unit_test.h"

// Command: echo "Hello, World"
Test(Lexer, basic_test)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_segment seg2 = SEG("Hello, World", DOUBLE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);
	t_token *expected[] = { &tok1, &tok2, NULL };

	t_token	**tokens = lexer("echo \"Hello, World\"");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

// Command: echo 'He"llo Wo"rld'
Test(Lexer, single_quoted_word)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("He\"llo Wo\"rld", SINGLE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		NULL
	};

	t_token **tokens = lexer("echo 'He\"llo Wo\"rld'");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

// Command: echo He"llo" Wo'rld'
Test(Lexer, mixed_quotes)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2_1 = SEG("He", NONE);
	t_segment seg2_2 = SEG("llo", DOUBLE);
	t_segment *lexeme2[] = { &seg2_1, &seg2_2, NULL };

	t_segment seg3_1 = SEG("Wo", NONE);
	t_segment seg3_2 = SEG("rld", SINGLE);
	t_segment *lexeme3[] = { &seg3_1, &seg3_2, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);
	t_token tok3 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		NULL
	};

	t_token **tokens = lexer("echo He\"llo\" Wo'rld'");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

// Command: echo Hello World | grep "Hello"
Test(Lexer, pipe_and_quotes)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("Hello", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_segment seg3 = SEG("World", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };

	t_segment seg4 = SEG("grep", NONE);
	t_segment *lexeme4[] = { &seg4, NULL };

	t_segment seg5 = SEG("Hello", DOUBLE);
	t_segment *lexeme5[] = { &seg5, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);
	t_token tok3 = TOK(lexeme3, WORD);
	t_token tok4 = TOK(NULL, PIPE);
	t_token tok5 = TOK(lexeme4, WORD);
	t_token tok6 = TOK(lexeme5, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		&tok5,
		&tok6,
		NULL
	};

	t_token **tokens = lexer("echo Hello World | grep \"Hello\"");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

// Command: echo Hello >text
Test(Lexer, output_redirect_no_space)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("Hello", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_segment seg3 = SEG("text", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);
	t_token tok3 = TOK(NULL, REDIR_OUT);
	t_token tok4 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		NULL
	};

	t_token **tokens = lexer("echo Hello >text");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

// Command: < text cat
Test(Lexer, input_redirect_space)
{
	t_segment seg1 = SEG("$FILE", DOUBLE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("cat", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_token tok1 = TOK(NULL, REDIR_IN);
	t_token tok2 = TOK(lexeme1, WORD);
	t_token tok3 = TOK(lexeme2, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		NULL
	};

	t_token **tokens = lexer("< \"$FILE\" cat");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

// Command: << 'EO F' cat
Test(Lexer, heredoc_before_command)
{
	t_token tok1 = TOK(NULL, HEREDOC);

	t_segment seg1 = SEG("EO F", SINGLE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_token tok2 = TOK(lexeme1, WORD);

	t_segment seg2 = SEG("cat", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };
	t_token tok3 = TOK(lexeme2, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		NULL
	};

	t_token **tokens = lexer("<<\'EO F\' cat");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

// Command: echo 'World!'>>$OUT
Test(Lexer, append_after_command)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_token tok1 = TOK(lexeme1, WORD);

	t_segment seg2 = SEG("World!", SINGLE);
	t_segment *lexeme2[] = { &seg2, NULL };
	t_token tok2 = TOK(lexeme2, WORD);

	t_token tok3 = TOK(NULL, APPEND);

	t_segment seg4 = SEG("$OUT", DOUBLE);
	t_segment *lexeme4[] = { &seg4, NULL };
	t_token tok4 = TOK(lexeme4, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		NULL
	};

	t_token **tokens = lexer("echo \'World!\'>>\"$OUT\"");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}
