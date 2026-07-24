#include "unit_test.h"

const char	*node_type_name(t_node_type type)
{
	switch (type)
	{
		case COMMAND: return ("COMMAND");
		case REDIR: return ("REDIR");
		case CTRL: return ("CTRL");
		case TARGET: return ("TARGET");
	}
	return (NULL);
}
