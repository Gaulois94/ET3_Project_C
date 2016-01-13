#include "ResourcesManager.h"

ResourcesManager* ResourcesManager_create()
{
	ResourcesManager* self = (ResourcesManager*)malloc(sizeof(ResourcesManager));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	self->len = 0;
	self->keys = NULL;
   	self->data = NULL;
	return self;
}

void* ResourcesManager_getData(ResourcesManager* self, const char* key)
{
	uint32_t i;
	for(i=0; i < self->len; i++)
		if(!strcmp(self->keys[i], key))
			return self->data[i];
	return NULL;
}

void* ResourcesManager_getDataByID(ResourcesManager* self, uint32_t id)
{
	return (id >= self->len) ? NULL : self->data[id];
}

const char* ResourcesManager_getKeyByID(const ResourcesManager* self, uint32_t id)
{
	return (id >= self->len) ? NULL : self->keys[id];
}

const char* ResourcesManager_getKey(const ResourcesManager* self, const void* data)
{
	uint32_t i;
	for(i=0; i < self->len; i++)
		if(self->data == data)
			return self->keys[i];
	return NULL;
}

uint32_t ResourcesManager_getLen(const ResourcesManager* self)
{
	return self->len;
}

bool ResourcesManager_addData(ResourcesManager* self, const char* key, void* data)
{
	uint32_t i;
	for(i=0;i < self->len; i++)
	{
		if(!strcmp(self->keys[i], key))
			return false;
	}

	self->len++;
	self->keys = (const char**)realloc(self->keys, self->len * sizeof(char*));
	self->data = (void**)realloc(self->data, self->len * sizeof(void*));

	self->keys[self->len-1] = key;
	self->data[self->len-1] = data;
	return true;
}

void* ResourcesManager_removeData(ResourcesManager* self, const char* key)
{
	uint32_t i;
	void* data = NULL;
	for(i=0; i < self->len; i++)
		if(!strcmp(self->keys[i], key))
		{
			data = self->data[i];
			uint32_t j;			
			for(j=i; j < self->len-1; j++)
			{
				self->keys[j] = self->keys[j+1];
				self->data[j] = self->data[j+1];

			}
			self->keys = (const char**)realloc(self->keys, (self->len-1) * sizeof(char*));
			self->data = (void*)realloc(self->keys, (self->len-1) * sizeof(char*));
			self->len--;
			break;
		}
	return data;
			
}

void ResourcesManager_destroy(ResourcesManager* self)
{
	free(self->keys);
	free(self->data);
	free(self);
}
