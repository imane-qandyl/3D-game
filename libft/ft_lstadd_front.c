/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:14:03 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/29 17:07:46 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

// #include <stdio.h>
// int	main(void)
// {
// 	t_list *list;
// 	t_list	*a = ft_lstnew("abc");
// 	t_list	*b = ft_lstnew("123");
// 	t_list	*c = ft_lstnew("doremi");
// 	ft_lstadd_front(&list, a);
// 	ft_lstadd_front(&list, b);
// 	ft_lstadd_front(&list, c);
// 	t_list	*current = list;
// 	while (current)
// 	{
// 		printf("%s\n", current->content);
// 		current = current->next;
// 	}
// }