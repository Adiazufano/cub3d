/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:25:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/21 10:12:00 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last -> next)
			last = last -> next;
		last -> next = new;
	}
}
// int	main(void)
// {
// 	t_list *list = ft_lstnew("Hola Mundo");
// 	if (!list)
// 		return (1);
// 	t_list	*list2 = ft_lstnew("Adios");
// 		if(!list2)
// 			return (1);
// 	t_list	*list3 = ft_lstnew("Prueba");
// 		if (!list3)
// 			return(1);
// 	t_list	*list4 = ft_lstnew("ADD");
// 	if(!list4)
// 		return (1);
// 	list -> next = list2;
// 	ft_lstadd_front(&list, list3);
// 	ft_lstadd_back(&list, list4);
// 	t_list *current = list;
// 	while (current)
// 	{
// 		printf("%s\n",(char *)current -> content);
// 		current = current -> next;
// 	}
// 	printf("%i\n",ft_lstsize(list));
// 	printf("%s\n",ft_lstlast(list));
// }