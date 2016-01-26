#include "Datas.h"

ObjectDatas* ObjectDatas_create()
{
	ObjectDatas* objDatas = (ObjectDatas*)malloc(sizeof(ObjectDatas));
	if(objDatas == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	objDatas->CSVTileID = List_create();
	objDatas->CSVFileID = List_create();
	objDatas->createObject = NULL;
	return objDatas;
}

void ObjectDatas_destroy(ObjectDatas* self)
{
	uint32_t i;
	for(i=0; i < List_getLen(self->CSVTileID); i++)
	{
		free(List_getData(self->CSVTileID, i));
		free(List_getData(self->CSVFileID, i));
	}

	List_destroy(self->CSVTileID);
	List_destroy(self->CSVFileID);
	free(self);
}
