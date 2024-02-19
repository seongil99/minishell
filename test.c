#include "minishell.h"
#include <stdio.h>

int	g_exit_code;


void check(void)
{
	system("leaks minishell");
}

int main(void)
{
	// atexit(check);
	init_action_table();
	init_goto_table();
	char *c = readline("input$ ");
	t_lst *lst = tokenize(c);
	t_lst *head = lst;
	int ret = parse_line(lst);
	printf("result : %s\n", (ret == 0 ? "REJECT" : "ACCEPT"));
	while (lst)
	{
		t_token *t = (t_token *)lst->data;
		printf("|%s| ", t->str);
		lst = lst->next;
	}
	printf("\n");
	lst_clear(&head, token_del);
	exit(0);
}
