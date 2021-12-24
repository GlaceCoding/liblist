/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:35:46 by gphilipp          #+#    #+#             */
/*   Updated: 2021/12/24 15:37:30 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "liblist.h"

typedef struct s_mystring
{
	char	*word;
	int		count;
} mystring;

void	list_init_data(void *data)
{
	mystring	*jour;

	jour = (mystring *) data;

	jour->count++;
}

void	list_free_data(void *data)
{
	mystring	*jour;

	jour = (mystring *) data;

	jour->count = 0;
}

int	list_data_eq(void *data1, void *data2)
{
	mystring	*mystring1;
	mystring	*mystring2;

	mystring1 = (mystring *) data1;
	mystring2 = (mystring *) data2;
	if (strcmp(mystring1->word, mystring2->word) == 0)
		return (1);
	else
		return (0);
}

int	list_dtoi(void *data)
{
	mystring	*jour;

	jour = (mystring *) data;
	if (strcmp(jour->word, "Lundi") == 0)
		return (0);
	else if (strcmp(jour->word, "Mardi") == 0)
		return (1);
	else if (strcmp(jour->word, "Mercredi") == 0)
		return (2);
	else if (strcmp(jour->word, "Jeudi") == 0)
		return (3);
	else if (strcmp(jour->word, "Vendredi") == 0)
		return (4);
	else if (strcmp(jour->word, "Samedi") == 0)
		return (5);
	else if (strcmp(jour->word, "Dimanche") == 0)
		return (6);
	return (-1);
}

void	set_value(mystring *jour, char *str)
{
	jour->word = str;
	jour->count = 0;
}

int	filter(t_list **item, int index, t_list **plist)
{
	(void) item;
	(void) plist;
	return (index % 2);
}

MU_TEST(allowed_function) {
	mu_check(system("sh ./test/allowed_function.sh") == 0);
}

MU_TEST(test_list) {
	mystring	strings[7];

	set_value(&strings[0], "Lundi");
	set_value(&strings[1], "Mardi");
	set_value(&strings[2], "Mercredi");
	set_value(&strings[3], "Jeudi");
	set_value(&strings[4], "Vendredi");
	set_value(&strings[5], "Samedi");
	set_value(&strings[6], "Dimanche");

	t_list		*jours;
	t_list		*jours2;
	t_list		*cursor;
	mystring	*data;
	t_info		info;

	jours = list_new((void *) &strings[1]);
	mu_assert_string_eq("Mardi", strings[1].word);
	mu_assert_string_eq("Mardi", ((mystring *)jours->data)->word);
	mu_assert_int_eq(2, list_push(&jours, &strings[6]));
	mu_assert_string_eq("Mardi", ((mystring *)jours->data)->word);
	mu_assert_string_eq("Dimanche", ((mystring *)jours->next->data)->word);
	info = list_int_info(jours);
	mu_assert_int_eq(1, info.min);
	mu_assert_int_eq(6, info.max);
	mu_assert_int_eq(2, info.size);
	list_unshift(&jours, &strings[0]);
	mu_assert_string_eq("Lundi", ((mystring *)jours->data)->word);
	mu_assert_string_eq("Mardi", ((mystring *)jours->next->data)->word);
	mu_assert_string_eq("Dimanche", ((mystring *)jours->next->next->data)->word);
	mu_assert_int_eq(1, ((mystring *)jours->data)->count);
	mu_assert_int_eq(1, ((mystring *)jours->next->data)->count);
	mu_assert_int_eq(1, ((mystring *)jours->next->next->data)->count);
	info = list_int_info(jours);
	mu_assert_int_eq(0, info.min);
	mu_assert_int_eq(6, info.max);
	mu_assert_int_eq(3, info.size);
	jours2 = list_new((void *) &strings[2]);
	mu_assert_int_eq(2, list_push(&jours2, &strings[3]));
	mu_assert_int_eq(3, list_push(&jours2, &strings[5]));
	mu_assert_int_eq(3, list_length(jours2));
	list_unshift(&(jours2->next->next), &strings[4]);
	mu_assert_string_eq("Mercredi", ((mystring *)jours2->data)->word);
	mu_assert_string_eq("Jeudi", ((mystring *)jours2->next->data)->word);
	mu_assert_string_eq("Vendredi", ((mystring *)jours2->next->next->data)->word);
	mu_assert_string_eq("Samedi", ((mystring *)jours2->next->next->next->data)->word);
	data = (mystring *) jours2->next->next->next->data;
	mu_assert_int_eq(1, data->count);
	cursor = list_splice(&jours, 2, 0, &jours2);
	mu_check(NULL == cursor);
	mu_assert_int_eq(2, data->count);

	cursor = jours;
	mu_assert_string_eq("Lundi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Mardi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Mercredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Jeudi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Vendredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Samedi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Dimanche", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count);
	mu_check(NULL == cursor->next);

	cursor = jours;
	mu_assert_int_eq(7, list_length(cursor)); cursor = cursor->next;
	mu_assert_int_eq(6, list_length(cursor)); cursor = cursor->next;
	mu_assert_int_eq(5, list_length(cursor)); cursor = cursor->next;
	mu_assert_int_eq(4, list_length(cursor)); cursor = cursor->next;
	mu_assert_int_eq(3, list_length(cursor)); cursor = cursor->next;
	mu_assert_int_eq(2, list_length(cursor)); cursor = cursor->next;
	mu_assert_int_eq(1, list_length(cursor));
	mu_check(NULL == cursor->next); cursor = cursor->next;
	mu_assert_int_eq(0, list_length(cursor));

	jours2 = list_slice(&jours, 5, 2);
	mu_check(NULL != jours2);
	mu_assert_int_eq(3, data->count);
	cursor = jours2;
	mu_assert_string_eq("Samedi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(3, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Dimanche", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count);
	info = list_int_info(jours2);
	mu_assert_int_eq(5, info.min);
	mu_assert_int_eq(6, info.max);
	mu_assert_int_eq(2, info.size);
	mu_assert_int_eq(2, list_clear(&jours2));
	mu_check(NULL == jours2);
	mu_assert_int_eq(0, data->count);

	cursor = jours;
	mu_assert_string_eq("Lundi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Mardi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Mercredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Jeudi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Vendredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count);
	mu_check(NULL == cursor->next);
	data = (mystring *)cursor->data;
	mu_assert_int_eq(2, data->count);
	info = list_int_info(jours);
	mu_assert_int_eq(0, info.min);
	mu_assert_int_eq(4, info.max);
	mu_assert_int_eq(5, info.size);

	jours2 = list_new((void *) &strings[6]);
	list_unshift(&jours2, &strings[5]);
	list_unshift(&jours2, &strings[4]);
	mu_assert_string_eq("Vendredi", ((mystring *)jours2->data)->word);
	mu_assert_int_eq(3, ((mystring *)jours2->data)->count);
	mu_assert_int_eq(3, data->count);
	mu_assert_string_eq("Samedi", ((mystring *)jours2->next->data)->word);
	mu_assert_string_eq("Dimanche", ((mystring *)jours2->next->next->data)->word);
	cursor = list_splice(&jours, 4, 1, &jours2);
	mu_assert_string_eq("Vendredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(5, ((mystring *)cursor->data)->count);
	mu_assert_int_eq(5, data->count);
	mu_assert_int_eq(1, list_clear(&cursor));
	mu_check(NULL == cursor);
	mu_assert_int_eq(0, data->count);

	cursor = jours;
	mu_assert_string_eq("Lundi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Mardi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Mercredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Jeudi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_check(NULL != cursor);
	mu_assert_string_eq("Vendredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(0, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Samedi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Dimanche", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count);
	mu_check(NULL == cursor->next);
	info = list_int_info(jours);
	mu_assert_int_eq(0, info.min);
	mu_assert_int_eq(6, info.max);
	mu_assert_int_eq(7, info.size);

	list_free_data(list_shift(&jours));
	mu_assert_int_eq(6, list_length(jours));
	mu_assert_string_eq("Mardi", ((mystring *)jours->data)->word);
	list_unshift(&jours, &strings[0]);
	mu_assert_int_eq(7, list_length(jours));
	mu_assert_string_eq("Lundi", ((mystring *)jours->data)->word);

	list_free_data(list_pop(&jours));
	mu_assert_int_eq(6, list_length(jours));
	mu_check(NULL == jours->next->next->next->next->next->next);
	mu_assert_int_eq(7, list_push(&jours, &strings[6]));
	mu_assert_int_eq(7, list_length(jours));
	mu_assert_string_eq("Dimanche", ((mystring *)jours->next->next->next->next->next->next->data)->word);

	jours2 = list_map(&jours, filter);

	cursor = jours2;
	mu_assert_string_eq("Lundi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Mercredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(3, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Vendredi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Dimanche", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count);
	mu_check(NULL == cursor->next);
	mu_assert_int_eq(0, list_push_uniq(&jours2, &strings[0]));
	mu_assert_int_eq(4, list_length(jours2));
	mu_check(NULL == cursor->next);

	cursor = jours;
	mu_assert_string_eq("Mardi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(1, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Jeudi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count); cursor = cursor->next;
	mu_assert_string_eq("Samedi", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(2, ((mystring *)cursor->data)->count);
	mu_check(NULL == cursor->next);
	info = list_int_info(jours);
	mu_assert_int_eq(1, info.min);
	mu_assert_int_eq(5, info.max);
	mu_assert_int_eq(3, info.size);

	mu_assert_int_eq(4, list_push_uniq(&jours, &strings[6]));
	mu_assert_int_eq(4, list_length(jours));
	mu_check(NULL != cursor->next);
	cursor = cursor->next;
	mu_assert_string_eq("Dimanche", ((mystring *)cursor->data)->word);
	mu_assert_int_eq(3, ((mystring *)cursor->data)->count);
	mu_check(NULL == cursor->next);
}

MU_TEST(test_shift) {
	mystring	strings[7];
	mystring	*string_a;

	set_value(&strings[0], "Lundi");
	set_value(&strings[1], "Mardi");
	set_value(&strings[2], "Mercredi");
	set_value(&strings[3], "Jeudi");
	set_value(&strings[4], "Vendredi");
	set_value(&strings[5], "Samedi");
	set_value(&strings[6], "Dimanche");

	t_list		*jours;

	jours = list_new((void *) &strings[1]);
	mu_assert_int_eq(2, list_push(&jours, &strings[6]));
	mu_assert_string_eq("Mardi", ((mystring *)jours->data)->word);
	mu_assert_string_eq("Dimanche", ((mystring *)jours->next->data)->word);
	mu_assert_string_eq("Dimanche", ((mystring *)list_pop(&jours))->word);
	mu_assert_int_eq(0, (int)jours->next);
	mu_assert_int_eq(2, list_push(&jours, &strings[6]));
	mu_assert_string_eq("Dimanche", ((mystring *)jours->next->data)->word);
	string_a = (mystring *)list_shift(&jours);
	mu_assert_string_eq("Mardi", string_a->word);
	mu_assert_string_eq("Dimanche", ((mystring *)jours->data)->word);
	mu_assert_int_eq(0, (int)jours->next);
	mu_assert_int_eq(2, list_push(&jours, string_a));
	mu_assert_string_eq("Mardi", ((mystring *)jours->next->data)->word);
	list_unshift(&jours, list_pop(&jours));
	mu_assert_string_eq("Mardi", ((mystring *)jours->data)->word);
	mu_assert_string_eq("Dimanche", ((mystring *)jours->next->data)->word);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(allowed_function);

	MU_RUN_TEST(test_list);
	MU_RUN_TEST(test_shift);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
