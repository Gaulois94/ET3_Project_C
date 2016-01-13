#ifndef  RESOURCES_INC
#define  RESOURCES_INC

#include "typedefine.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/* \struct ResourcesManager
 * \brief The structure handles datas such as TTF_Font, Texture*, etc. and maps them with key char* */
typedef struct
{
	void**         data;
	const char**   keys;
	uint32_t       len;
}ResourcesManager;

/** \brief init the resourcesManager
 * \return return the new ResourcesManager*/
ResourcesManager* ResourcesManager_create();

/** \brief return the data associate with the key
 * \param resources the ResourcesManager
 * \param key the key associate to the data
 * \return the data*/
void*             ResourcesManager_getData(ResourcesManager* resources, const char* key);

/** \brief return the key associate to the data
 * \param resources the ResourcesManager
 * \param data the pointer to data
 * \return the key*/
const char*       ResourcesManager_getKey(const ResourcesManager* resources, const void* data);

/** \brief return the length of the array ResourcesManager
 * \param resources the ResourcesManager
 * \return the len*/
uint32_t          ResourcesManager_getLen(const ResourcesManager* resources);

/** \brief get the data by its ID
 * \param resources the ResourcesManager
 * \param i the ID
 * \return the data*/
void*             ResourcesManager_getDataByID(ResourcesManager* resources, uint32_t i);

/** \brief get the key by its ID
 * \param resources the ResourcesManager
 * \param i the ID
 * \return the key*/
const char*             ResourcesManager_getKeyByID(const ResourcesManager* resources, uint32_t i);

/** \brief add a data to the ResourcesManager
 * \param resources the ResourcesManager
 * \param key the key which will be associate to the data
 * \param data the data
 * \return if the data table could be added (the key doesn't exist)*/
bool              ResourcesManager_addData(ResourcesManager* resources, const char* key, void* data);

/** \brief remove a data on the ResourcesManager associate with its key
 * \param resources the ResourcesManager
 * \param key the key
 * \return the data removed*/
void*             ResourcesManager_removeData(ResourcesManager* resources, const char* key);

/** \brief remove the ResourcesManager
 * \param resources the ResourcesManager*/
void              ResourcesManager_destroy(ResourcesManager* resources);

#endif
