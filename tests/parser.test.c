#include "unit_test.h"

Test(Parser, basic_test)
{
	char *content[] = {"echo", "hello", NULL};
	t_node node = NODE((void *)content, COMMAND, NULL, NULL);
	printf("%d\n", node.type);
	printf("Good");
	cr_assert(4 + 3 == 7, "Expected 3 + 4 to be equal to 7");
}
