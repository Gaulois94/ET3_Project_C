#include "Datas.h"

ObjectDatas* ObjectDatas_create()
{
	ObjectDatas* objDatas = (ObjectDatas*)malloc(sizeof(ObjectDatas));
	if(objDatas == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	objDatas->List_create();
	objDatas->createObject = NULL;
	return objDatas;
}
