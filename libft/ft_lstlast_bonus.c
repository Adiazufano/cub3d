/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:34:21 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/21 10:10:37 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
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
// 	list -> next = list2;
// 	ft_lstadd_front(&list, list3);
// 	t_list *current = list;
// 	while (current)
// 	{
// 		printf("%s\n",(char *)current -> content);
// 		current = current -> next;
// 	}
// 	printf("%i\n",ft_lstsize(list));
// 	printf("%s\n",ft_lstlast(list));
// }