#include "List.h"

List* List_create()
{
	List* list = (List*)malloc(sizeof(List));
	if(list == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	list->head = NULL;
	list->len  = 0;
	return list;
}

void List_addData(List* self, void* data)
{
	ListElem* elem = (ListElem*)malloc(sizeof(ListElem));
	elem->next     = NULL;
	elem->data     = data;

	if(self->len == 0)
		self->head = elem;
	else
	{
		ListElem* queue = List_getElem(self, self->len-1);
		queue->next = elem;
	}
	self->len++;
}

ListElem* List_getElem(List* self, uint32_t id)
{
	if(id >= self->len)
		return NULL;

	ListElem* queue = self->head;
	uint32_t i;
	for(i=0; i < id; i++)
		queue = queue->next;
	return queue;
}

void List_clear(List* self)
{
	ListElem* elem =self->head;
	uint32_t i;
	for(i=0; i < self->len; i++)
	{
		ListElem* tmp = elem->next;
		free(elem);
		elem = tmp;
	}
}

void List_destroy(List* self)
{
	List_clear(self);
	free(self);
}

uint32_t List_getLen(const List* self)
{
	return self->len;
}

void* List_getData(List* self, uint32_t id)
{
	if(id >= self->len)
		return NULL;
	ListElem* queue = List_getElem(self, id);
	if(queue)
		return queue->data;
	return NULL;
}

void List_removeData(List* self, void* data)
{
	ListElem* elem = self->head;
	ListElem* tmp  = NULL;
	uint32_t i;
	for(i=0; i < self->len; i++)
	{
		if(elem->data == data)
		{
			if(tmp != NULL)
				tmp->next = elem->next;
			else
				self->head = elem->next;
			free(elem);
			return;
		}
		tmp = elem;
		elem = elem->next;
	}
	self->len--;
}

void* List_removeDataByID(List* self, uint32_t id)
{
	ListElem* queue = List_getElem(self, id);
	if(queue == NULL)
		return NULL;	

	void* data = queue->data;

	ListElem* queueBefore = List_getElem(self, id-1);
	if(queueBefore == NULL)
		self->head = queue->next;
	else
		queueBefore->next = queue->next;
	free(queue);
	self->len--;
			
	return data;
}
