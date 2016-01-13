#ifndef  LIST_INC
#define  LIST_INC

typedef char bool;

typedef struct ListElem
{
	struct ListElem* next;
	void* data;
}ListElem;

typedef struct
{
	ListElem* head;
	uint32_t len;
}List;

List*    List_createList();
void     List_addData(List* self, void* data);
uint32_t List_getLen(const List* self);
void     List_getData(List* self, uint32_t id);
void     List_removeData(List* self, void* data);
void*    List_removeDataByID(List* self, uint32_t i);
void     List_clear(List* self);
void     List_destroy(List* self);
ListElem*     List_getElem(List* self, uint32_t i);

#endif
