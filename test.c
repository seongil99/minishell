#include "minishell.h"
#include <stdio.h>

void dfs(t_treenode *node)
{
	t_lst	*t;

	printf("%d\n", node->data->type);
	t = node->child;
	while (t)
	{
		dfs(t->data);
		t = t->next;
	}
}

void check(void)
{
	system("leaks minishell");
}

int main(void)
{
	atexit(check);
	init_action_table();
	init_goto_table();
	char *c = readline("input$ ");
	t_lst *lst = tokenize(c);
	t_lst *head = lst;
	t_treenode  *ret = parse_line(lst);
	printf("result : %s\n", (ret == 0 ? "REJECT" : "ACCEPT"));
	while (lst)
	{
		t_token *t = (t_token *)lst->data;
		printf("|%s| ", t->str);
		lst = lst->next;
	}
	printf("\n");
	dfs(ret);
	lst_clear(&head, token_del);
	tree_del(ret);
	exit(0);
}
