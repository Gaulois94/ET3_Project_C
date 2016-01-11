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
uint32_t List_getLen(List* self);
void*    List_getData(List* self, uint32_t id);
void     List_deleteData(List* self, void* data);
void     List_clear(List* self, bool freeDatas);
void     List_destroy(List* self, bool freeDatas);

#endif
