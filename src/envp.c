#include "minishell.h"

void print_list(t_list* node)
{
	while(node != NULL)
	{
		printf("%s\n", (char*)node->content);
		node = node->next;
	}
}


t_list *copy_envp(char** envp)
{
	int	n;
	t_list* keep;
	t_list* head;

	head = ft_lstnew(ft_strdup(envp[0]));
	n = 1;
	while (envp[n] != NULL)
	{
		keep = ft_lstnew(ft_strdup(envp[n]));
		ft_lstadd_back(&head, keep);
		n++;
	}
	return(head);
}



