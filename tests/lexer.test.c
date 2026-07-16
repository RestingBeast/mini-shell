#include "unit_test.h"

Test(Lexer, basic_test_1)
{
	t_segment seg1 = SEG("pwd", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token *expected[] = { &tok1, NULL };

	t_token	**tokens = lexer("pwd");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
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

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

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

Test(Lexer, embedded_double_quotes)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2_1 = SEG("He", NONE);
	t_segment seg2_2 = SEG("llo Wo", DOUBLE);
	t_segment seg2_3 = SEG("rld", NONE);
	t_segment *lexeme2[] = { &seg2_1, &seg2_2, &seg2_3, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		NULL
	};

	t_token **tokens = lexer("echo He\"llo Wo\"rld");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

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

	t_token **tokens = lexer("echo 'He\"$llo Wo\"rld'");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, mixed_quotes)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2_1 = SEG("He", NONE);
	t_segment seg2_2 = SEG("$llo", DOUBLE);
	t_segment *lexeme2[] = { &seg2_1, &seg2_2, NULL };

	t_segment seg3_1 = SEG("Wo", NONE);
	t_segment seg3_2 = SEG("$rld", SINGLE);
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

	t_token **tokens = lexer("echo He\"$llo\" Wo'$rld'");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, output_redirect)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("Hello", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_segment seg3 = SEG("text1", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);
	t_token tok3 = TOK(NULL, REDIRECT_OUT);
	t_token tok4 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		NULL
	};

	t_token **tokens = lexer("echo Hello >text1");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, multiple_output_redirects)
{
	t_segment seg1 = SEG("echo", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("Hello", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_segment seg3 = SEG("text1", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };

	t_segment seg4 = SEG("text2", NONE);
	t_segment *lexeme4[] = { &seg4, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(lexeme2, WORD);
	t_token tok3 = TOK(NULL, REDIRECT_OUT);
	t_token tok4 = TOK(lexeme3, WORD);
	t_token tok5 = TOK(NULL, REDIRECT_OUT);
	t_token tok6 = TOK(lexeme4, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		&tok5,
		&tok6,
		NULL
	};

	t_token **tokens = lexer("echo Hello >text1 > text2");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, multiple_input_redirects_no_spaces)
{
	t_segment seg1 = SEG("text1", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("cat", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_segment seg3 = SEG("text2", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };

	t_token tok1 = TOK(NULL, REDIRECT_IN);
	t_token tok2 = TOK(lexeme1, WORD);
	t_token tok3 = TOK(lexeme2, WORD);
	t_token tok4 = TOK(NULL, REDIRECT_IN);
	t_token tok5 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		&tok5,
		NULL
	};

	t_token **tokens = lexer("<text1 cat <text2");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, multiple_input_redirects_spaces)
{
	t_segment seg1 = SEG("cat", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };

	t_segment seg2 = SEG("text1", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };

	t_segment seg3 = SEG("text2", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };

	t_token tok1 = TOK(lexeme1, WORD);
	t_token tok2 = TOK(NULL, REDIRECT_IN);
	t_token tok3 = TOK(lexeme2, WORD);
	t_token tok4 = TOK(NULL, REDIRECT_IN);
	t_token tok5 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		&tok5,
		NULL
	};

	t_token **tokens = lexer("cat < text1 < text2");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, heredoc_before_command)
{
	t_token tok1 = TOK(NULL, HEREDOC);

	t_segment seg1 = SEG("EOF", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_token tok2 = TOK(lexeme1, WORD);

	t_segment seg2 = SEG("cat", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };
	t_token tok3 = TOK(lexeme2, WORD);

	t_token tok4 = TOK(NULL, HEREDOC);

	t_segment seg3 = SEG("END", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };
	t_token tok5 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		&tok5,
		NULL
	};

	t_token **tokens = lexer("<<EOF cat << END");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, multiple_heredocs)
{
	t_segment seg1 = SEG("cat", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_token tok1 = TOK(lexeme1, WORD);

	t_token tok2 = TOK(NULL, HEREDOC);

	t_segment seg2 = SEG("EOF", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };
	t_token tok3 = TOK(lexeme2, WORD);

	t_token tok4 = TOK(NULL, HEREDOC);

	t_segment seg3 = SEG("END", NONE);
	t_segment *lexeme3[] = { &seg3, NULL };
	t_token tok5 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		&tok5,
		NULL
	};

	t_token **tokens = lexer("cat << EOF <<END");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, append_before_command)
{
	t_token tok1 = TOK(NULL, APPEND);

	t_segment seg1 = SEG("hello", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_token tok2 = TOK(lexeme1, WORD);

	t_segment seg2 = SEG("echo", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };
	t_token tok3 = TOK(lexeme2, WORD);

	t_segment seg3 = SEG("hello", SINGLE);
	t_segment *lexeme3[] = { &seg3, NULL };
	t_token tok4 = TOK(lexeme3, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		NULL
	};

	t_token **tokens = lexer(">>hello echo 'hello'");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}

Test(Lexer, append_before_and_after_command)
{
	t_token tok1 = TOK(NULL, APPEND);

	t_segment seg1 = SEG("hello", NONE);
	t_segment *lexeme1[] = { &seg1, NULL };
	t_token tok2 = TOK(lexeme1, WORD);

	t_segment seg2 = SEG("echo", NONE);
	t_segment *lexeme2[] = { &seg2, NULL };
	t_token tok3 = TOK(lexeme2, WORD);

	t_segment seg3 = SEG("world", DOUBLE);
	t_segment *lexeme3[] = { &seg3, NULL };
	t_token tok4 = TOK(lexeme3, WORD);

	t_token tok5 = TOK(NULL, APPEND);

	t_segment seg4 = SEG("world", NONE);
	t_segment *lexeme4[] = { &seg4, NULL };
	t_token tok6 = TOK(lexeme4, WORD);

	t_token *expected[] = {
		&tok1,
		&tok2,
		&tok3,
		&tok4,
		&tok5,
		&tok6,
		NULL
	};

	t_token **tokens = lexer(">>hello echo \"world\" >> world");

	cr_assert(compare_token(tokens, expected));
	//free_tokens(tokens);
}
