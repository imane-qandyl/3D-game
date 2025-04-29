/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:15:20 by lalwafi           #+#    #+#             */
/*   Updated: 2024/01/29 17:27:36 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		count;

	count = 0;
	if (!lst)
		return (0);
	current = lst;
	while (current != NULL)
	{
		current = current -> next;
		count++;
	}
	return (count);
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
// 	i forgot to add this
// }