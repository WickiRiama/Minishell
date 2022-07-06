
//here : include header 

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	ft_exit(t_token **tokens, char *input)
{
	ft_lstclear_msh(tokens, &free);
	free(input);
	exit(EXIT_SUCCESS);
}