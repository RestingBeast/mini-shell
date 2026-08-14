#include "test.h"
#include <criterion/criterion.h>

// Command: echo "Hello, World"
Test(Lexer, basic_test)
{
	t_segment seg1 = SEG("echo", NONE);
	t_list lexeme1 = LST((void *) &seg1, NULL);

	t_segment seg2 = SEG("Hello, World", DOUBLE);
	t_list lexeme2 = LST((void *) &seg2, NULL);

	t_token tok1 = TOK(&lexeme1, WORD);
	t_token tok2 = TOK(&lexeme2, WORD);

	t_list lst = LST((void *) &tok2, NULL);
	t_list expected = LST((void *) &tok1, &lst);

	t_list *tokens = lexer("echo \"Hello, World\"");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}

// Command: echo 'He"llo Wo"rld'
Test(Lexer, single_quoted_word)
{
	t_segment seg1 = SEG("echo", NONE);
	t_list lexeme1 = LST((void *) &seg1, NULL);

	t_segment seg2 = SEG("He\"llo Wo\"rld", SINGLE);
	t_list lexeme2 = LST((void *) &seg2, NULL);

	t_token tok1 = TOK(&lexeme1, WORD);
	t_token tok2 = TOK(&lexeme2, WORD);

	t_list lst2 = LST((void *) &tok2, NULL);
	t_list expected = LST((void *) &tok1, &lst2);

	t_list *tokens = lexer("echo 'He\"llo Wo\"rld'");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}

// Command: echo He"llo" Wo'rld'
Test(Lexer, mixed_quotes)
{
	t_segment seg1 = SEG("echo", NONE);
	t_list lexeme1 = LST((void *) &seg1, NULL);

	t_segment seg2_1 = SEG("He", NONE);
	t_segment seg2_2 = SEG("llo", DOUBLE);
	t_list lexeme2_tail = LST((void *) &seg2_2, NULL);
	t_list lexeme2 = LST((void *) &seg2_1, &lexeme2_tail);

	t_segment seg3_1 = SEG("Wo", NONE);
	t_segment seg3_2 = SEG("rld", SINGLE);
	t_list lexeme3_tail = LST((void *) &seg3_2, NULL);
	t_list lexeme3 = LST((void *) &seg3_1, &lexeme3_tail);

	t_token tok1 = TOK(&lexeme1, WORD);
	t_token tok2 = TOK(&lexeme2, WORD);
	t_token tok3 = TOK(&lexeme3, WORD);

	t_list lst3 = LST((void *) &tok3, NULL);
	t_list lst2 = LST((void *) &tok2, &lst3);
	t_list expected = LST((void *) &tok1, &lst2);

	t_list *tokens = lexer("echo He\"llo\" Wo'rld'");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}

// Command: echo Hello World | grep "Hello"
Test(Lexer, pipe_and_quotes)
{
	t_segment seg1 = SEG("echo", NONE);
	t_list lexeme1 = LST((void *) &seg1, NULL);

	t_segment seg2 = SEG("Hello", NONE);
	t_list lexeme2 = LST((void *) &seg2, NULL);

	t_segment seg3 = SEG("World", NONE);
	t_list lexeme3 = LST((void *) &seg3, NULL);

	t_segment seg4 = SEG("grep", NONE);
	t_list lexeme4 = LST((void *) &seg4, NULL);

	t_segment seg5 = SEG("Hello", DOUBLE);
	t_list lexeme5 = LST((void *) &seg5, NULL);

	t_token tok1 = TOK(&lexeme1, WORD);
	t_token tok2 = TOK(&lexeme2, WORD);
	t_token tok3 = TOK(&lexeme3, WORD);
	t_token tok4 = TOK(NULL, PIPE);
	t_token tok5 = TOK(&lexeme4, WORD);
	t_token tok6 = TOK(&lexeme5, WORD);

	t_list lst6 = LST((void *) &tok6, NULL);
	t_list lst5 = LST((void *) &tok5, &lst6);
	t_list lst4 = LST((void *) &tok4, &lst5);
	t_list lst3 = LST((void *) &tok3, &lst4);
	t_list lst2 = LST((void *) &tok2, &lst3);
	t_list expected = LST((void *) &tok1, &lst2);

	t_list *tokens = lexer("echo Hello World | grep \"Hello\"");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}

// Command: echo Hello >text
Test(Lexer, output_redirect_no_space)
{
	t_segment seg1 = SEG("echo", NONE);
	t_list lexeme1 = LST((void *) &seg1, NULL);

	t_segment seg2 = SEG("Hello", NONE);
	t_list lexeme2 = LST((void *) &seg2, NULL);

	t_segment seg3 = SEG("text", NONE);
	t_list lexeme3 = LST((void *) &seg3, NULL);

	t_token tok1 = TOK(&lexeme1, WORD);
	t_token tok2 = TOK(&lexeme2, WORD);
	t_token tok3 = TOK(NULL, REDIR_OUT);
	t_token tok4 = TOK(&lexeme3, WORD);

	t_list lst4 = LST((void *) &tok4, NULL);
	t_list lst3 = LST((void *) &tok3, &lst4);
	t_list lst2 = LST((void *) &tok2, &lst3);
	t_list expected = LST((void *) &tok1, &lst2);

	t_list *tokens = lexer("echo Hello >text");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}

// Command: < "$FILE" cat
Test(Lexer, input_redirect_space)
{
	t_segment seg1 = SEG("$FILE", DOUBLE);
	t_list lexeme1 = LST((void *) &seg1, NULL);

	t_segment seg2 = SEG("cat", NONE);
	t_list lexeme2 = LST((void *) &seg2, NULL);

	t_token tok1 = TOK(NULL, REDIR_IN);
	t_token tok2 = TOK(&lexeme1, WORD);
	t_token tok3 = TOK(&lexeme2, WORD);

	t_list lst3 = LST((void *) &tok3, NULL);
	t_list lst2 = LST((void *) &tok2, &lst3);
	t_list expected = LST((void *) &tok1, &lst2);

	t_list *tokens = lexer("< \"$FILE\" cat");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}

// Command: <<'EO F' cat
Test(Lexer, heredoc_before_command)
{
	t_token tok1 = TOK(NULL, HEREDOC);

	t_segment seg1 = SEG("EO F", SINGLE);
	t_list lexeme1 = LST((void *) &seg1, NULL);
	t_token tok2 = TOK(&lexeme1, WORD);

	t_segment seg2 = SEG("cat", NONE);
	t_list lexeme2 = LST((void *) &seg2, NULL);
	t_token tok3 = TOK(&lexeme2, WORD);

	t_list lst3 = LST((void *) &tok3, NULL);
	t_list lst2 = LST((void *) &tok2, &lst3);
	t_list expected = LST((void *) &tok1, &lst2);

	t_list *tokens = lexer("<<\'EO F\' cat");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}

// Command: echo 'World!'>>"$OUT"
Test(Lexer, append_after_command)
{
	t_segment seg1 = SEG("echo", NONE);
	t_list lexeme1 = LST((void *) &seg1, NULL);
	t_token tok1 = TOK(&lexeme1, WORD);

	t_segment seg2 = SEG("World!", SINGLE);
	t_list lexeme2 = LST((void *) &seg2, NULL);
	t_token tok2 = TOK(&lexeme2, WORD);

	t_token tok3 = TOK(NULL, APPEND);

	t_segment seg4 = SEG("$OUT", DOUBLE);
	t_list lexeme4 = LST((void *) &seg4, NULL);
	t_token tok4 = TOK(&lexeme4, WORD);

	t_list lst4 = LST((void *) &tok4, NULL);
	t_list lst3 = LST((void *) &tok3, &lst4);
	t_list lst2 = LST((void *) &tok2, &lst3);
	t_list expected = LST((void *) &tok1, &lst2);

	t_list *tokens = lexer("echo \'World!\'>>\"$OUT\"");

	cr_assert(compare_tokens(tokens, &expected));
	//free_tokens(tokens);
}
