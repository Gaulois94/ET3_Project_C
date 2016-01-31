#ifndef  LIST_INC
#define  LIST_INC

#include "typedefine.h"
#include "stdlib.h"
#include "stdio.h"

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

List*    List_create();

/** \brief add a data to the list
 * \param self the List itself
 * \param data the data to be added*/
void     List_addData(List* self, void* data);

/** \brief get the number of datas that the List contains
 * \param self the List itself
 * \return the number of data of the list*/
uint32_t List_getLen(const List* self);

/** \brief get the data at id
 * \param self the List itself
 * \param id the id of the data
 * \return the data which corresponds of the id. Returns NULL if the id is too big*/
void*    List_getData(List* self, uint32_t id);

/** \brief remove the data data in the List
 * \param self the List itself
 * \param the data to remove*/
void     List_removeData(List* self, void* data);

/** \brief remove the data at the position id
 * \param self the List itself
 * \param i the position of the data
 * \return the data removed*/
void*    List_removeDataByID(List* self, uint32_t i);

/** \brief clear all the content of the List
 * \param self the List itself*/
void     List_clear(List* self);
void     List_destroy(List* self);

/** \brief get the ListElem at the position i
 * \param self the List itself
 * \param i the position of the ListElem
 * \return the ListElem at the position i. Returns NULL if the position i isn't valid*/
ListElem*     List_getElem(List* self, uint32_t i);

#endif
