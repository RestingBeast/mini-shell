#include <criterion/criterion.h>
#include "minishell.h"

#include <string.h>

void	setup(void)
{
	printf("Starting Lexer test suite\n");
}

void	teardown(void)
{
	printf("Finished Lexer test suite\n");
}

Test(Lexer, basic_test, .init = setup, .fini = teardown)
{
	cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4");
}
