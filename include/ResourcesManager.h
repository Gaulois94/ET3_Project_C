#ifndef  RESOURCES_INC
#define  RESOURCES_INC

#include "typedefine.h"

/* \struct ResourcesManager
 * \brief The structure handles datas such as TTF_Font, Texture*, etc. and maps them with key char* */
typedef struct
{
	void**         data;
	const char**   keys;
	uint32_t       len;
}ResourcesManager;

ResourcesManager* ResourcesManager_init();
void*             ResourcesManager_getData(ResourcesManager* resources, const char* key);
const char*       ResourcesManager_getKey(ResourcesManager* resources, const void* data);
uint32_t          ResourcesManager_getLen(ResourcesManager* resources);
void              ResourcesManager_addData(ResourcesManager* resources, const char* key, void* data);
bool              ResourcesManager_deleteData(ResourcesManager* resources, const char* key);
void              ResourcesManager_destroy(ResourcesManager* resources);

#endif
