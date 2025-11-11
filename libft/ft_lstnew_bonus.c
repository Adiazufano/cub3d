/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:29:29 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/21 10:14:29 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list			*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list -> content = content;
	list -> next = NULL;
	return (list);
}
// int	main(void)
// {
// 	int i = {1, 2, 3};
// 	t_list *list = ft_lstnew(i);
// 	if (!list)
// 		return (1);
// 	t_list *current = list;
// 	while (current)
// 	{
// 		printf("%s",(char *)current -> content);
// 		current = current -> next;
// 	}
// }
