/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:48:11 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/21 10:11:48 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	temp = *lst;
	while (*lst)
	{
		temp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

// int main()
// {
//     t_list *lista = NULL;
//     int *valor1 = malloc(sizeof(int));
//     int *valor2 = malloc(sizeof(int));
//     int *valor3 = malloc(sizeof(int));

//     *valor1 = 10;
//     *valor2 = 20;
//     *valor3 = 30;

//     // Crear nodos
//     lista = ft_lstnew(valor1);
//     lista->next = ft_lstnew(valor2);
//     lista->next->next = ft_lstnew(valor3);

//     // Imprimir lista antes de clear
//     printf("Lista antes de ft_lstclear:\n");
//    	while (lista)
// 	{
// 		printf("%s\n",(char *)lista -> content);
// 		lista = lista -> next;
// 	}

//     // Limpiar toda la lista
//     ft_lstclear(&lista, del_int);

//     // Imprimir lista después de clear
//     printf("Lista después de ft_lstclear:\n");
//     while (lista)
// 	{
// 		printf("%s\n",(char *)lista -> content);
// 		lista = lista -> next;
// 	}

//     return 0;
// }
