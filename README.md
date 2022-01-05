# Liblist

Custom linked list library in C.

You can use int list and string list in the same application without problem.

## Installation

### Add & Include file

Include `./includes/list.h`, copy/paste `./list.c` in our project.

Edit `list_init_data`, `list_free_data`, `list_data_eq` and `list_dtoi` according to our need.

### Configure your MAKEFILE

```make
all: libs $(NAME)

# [...]

LIBLIST = vendor/liblist/

libs: $(LIBLIST)liblist.a

$(LIBLIST)liblist.a:
	make -C $(LIBLIST)

libs_clean:
	make -C $(LIBLIST) clean

libs_fclean: libs_clean
	make -C $(LIBLIST) fclean

# [...]

fclean: libs_fclean clean
	rm -f $(NAME)
```

Add `libs libs_clean libs_fclean` to `.PHONY`rule.

## API

```c
typedef struct s_list	t_list;
struct s_list
{
	t_list		*next;
	void		*data;
};
```

### List create and add element

#### list_new

Create a new list.

```c
t_list	*list_new(void *data);
```

#### list_unshift

Prepend an element on the list (add at the current position, most of the time at the beginning of the list).

Note: If you go to the second element and you unshift you will add the element between the first and the second element.

```c
int	list_unshift(t_list **plist, void *data);
```

#### list_push

Append an element on the list (add at the end of the list).


```c
int	list_push(t_list **plist, void *data);
```

#### list_splice

Add or replace elements from *slist* to *plist* at the *start* position. The number of elements replaced or removed depend on *deleteCount* value.


```c
t_list	*list_splice(t_list **plist, int start, int deleteCount, t_list **slist);
```

### List clear and remove element

#### list_shift

Remove the first element and return the data.

Note: Use the return to free the data. Like: `list_free_data(list_shift(plist))`.

```c
void	*list_pop(t_list **plist)
```

#### list_unshift

Remove the last element and return the data.

Note: Use the return to free the data. Like: `list_free_data(list_pop(plist))`.

```c
void	*list_pop(t_list **plist);
```

#### list_slice

Remove elements on the list at the *start* position. The number of elements removed depend on *deleteCount* value. *deleteCount* can be negative to delete all element after *start* position.

Note: Use the return to free the data with `list_clear`.

```c
t_list	*list_slice(t_list **plist, int start, int deleteCount);
```

#### map

Call a function on every element in the list, and removes element if the given function returns false.

Note: Use the return to free the data with `list_clear`.

```c
t_list	*list_map(t_list **plist, int (*map)(t_list **item, int index,
											t_list **plist));
```

#### list_clear

Remove&Free all the element of the list. You have to call `list_create`, if you want a new list.

```c
int	list_clear(t_list **plist);
```

### List info

#### list_length

Returns the number of elements.

```c
int	list_length(t_list *plist);
```

#### list_max_value

Returns the max value.

```c
int	list_max_value(t_list *plist);
```

#### list_min_value

Returns the min value.

```c
int	list_min_value(t_list *plist);
```

#### list_length

Returns the t_info structure (min, max, size) of the list.

Note: Don't forget to recall the function after a change on the list.

```c
typedef struct s_list_info
{
	int			max;
	int			min;
	int			size;
}	t_info;

t_info	list_int_info(t_list *plist);
```

### List utils

#### list_push_uniq

Push *data* and returns true only if *data* are not in the list, or returns false if the element already present.

```c
int	list_push_uniq(t_list **plist, void *data);
```

#### list_get_int

Get the *data* in int format (this function call `list_dtoi` before returns).

```c
int	list_get_int(t_list *list);
```

#### list_get_str

Get the string *data*.

Note: **Only use** with a string data.

```c
char	*list_get_str(t_list *list);
```

#### list_last

Get the last element of the list.

Note: **Only use** with a string data.

```c
t_list	*list_last(t_list **plist);
```

## FAQ

### How can I print the list ?

#### With printf

```c
#include <stdio.h>

void	printf_list(t_list *stack)
{
	if (stack)
		printf("%d ", *(int *)stack->data);
	if (stack && stack->next)
		printf_list(stack->next);
}
```

#### With ft_putstr

```c
void	list_print_str(t_list *plist)
{
	if (!plist)
		return ;
	ft_putstr(plist->data);
	ft_putstr("\n");
	list_print_str(plist->next);
}
```
