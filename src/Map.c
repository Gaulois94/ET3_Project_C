#include "Map.h"

uint32_t XML_depth = 0;

Map* Map_create(const char* path)
{
	Map* map          = (Map*)malloc(sizeof(Map));
	map->files        = List_createList();
	map->staticFiles  = List_createList();
	map->dynamicFiles = List_createList();

	//Init the parser
	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetUserData(parser, (void*)map);
	XML_SetElementHandler(parser, &startElement, &endElement);

	map->parser = parser;

	//Get the xml code
	FILE* file = fopen(path, "r");
	char line[100];

	while(fgets(line, 100, file) != NULL)
	{
		uint32_t lineLength = strlen(line);
		if(XML_Parse(parser, line, lineLength, 0) == 0)
			perror("Error in parsing the XML code");
	}

	fclose(file);
	file = NULL;

	if(XML_Parse(parser, NULL, 0, 1) == 0)
		perror("Error in parsing the XML code");

	XML_ParserFree(parser);

	return map;
}

void Map_draw(Map* map, Window* window)
{

}

void startElement(void *data, const char* name, const char** attrs)
{
	//Set the start_function while parsing the file
	if(!strcmp(name, "Files"))
		XML_SetElementHandler(((Map*)data)->parser, startElementFiles, endElement);
	else if(!strcmp(name, "Objects"))
		XML_SetElementHandler(((Map*)data)->parser, startElementObjects, endElement);
	else if(!strcmp(name, "Traces"))
		XML_SetElementHandler(((Map*)data)->parser, startElementTraces, endElement);
	XML_depth++;
}

void startElementFiles(void *data, const char* name, const char** attrs)
{
	uint32_t i;
	Map* map = (Map*)data;

	if(XML_depth == 1)
	{
		File* file = NULL;

		if(!strcmp(name, "Static"))
		{
			StaticFile* sf = (StaticFile*)malloc(sizeof(StaticFile));
			List_addData(map->staticFiles, sf);
            
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "file"))
					file = File_create(attrs[i+1]);

                else if(!strcmp(attrs[i], "spacing"))
                    getXYFromStr(attrs[i+1], &(sf->spacingX), &(sf->spacingY));

                else if(!strcmp(attrs[i], "tileSize"))
                    getXYFromStr(attrs[i+1], &(sf->tileSizeX), &(sf->tileSizeY));
			}
		}

        else if(!strcmp(name, "Dynamic"))
        {
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "file"))
					file = File_create(attrs[i+1]);
			}
        }

		if(file==NULL)
		{
			perror("Exit because can't load a file");
			//exit();
		}
		List_addData(map->files, file);
	}

	else if(XML_depth == 2)
	{
		if(List_getLen(map->files) == List_getLen(map->staticFiles)) //Because we load static files before dynamic files, if the len is equal, then the last file was static
		{
			StaticFile* sf = (StaticFile*) List_getData(map->staticFiles, List_getLen(map->staticFiles));
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "type") && !strcmp(attrs[i+1], "someType"))
				{
					
				}
			}
		}

		else
		{
		}
	}

	else if(XML_depth == 3) //We know that we are handling DynamicTiles
	{

	}
	XML_depth++;
}

void startElementObjects(void *data, const char* name, const char** attrs)
{
	XML_depth++;
}

void startElementTraces(void *data, const char* name, const char** attrs)
{
	XML_depth++;
}

void endElement(void *data, const char* name)
{
	XML_depth--;
	if(XML_depth == 1)
		XML_SetElementHandler(((Map*)data)->parser, startElement, endElement);
}

void getXYFromStr(const char* str, uint32_t* x, uint32_t* y)
{
    uint32_t i;
    for(i=0; str[i] != 'x' && str[i] != 'X' && str[i] != '\0'; i++);

    if(str[i] != '\0')
    {
        *x = atoi(str);
        *y = atoi(&(str[i+1]));
    }
}

void Map_destroy(Map* map)
{
	uint32_t i;
	for(i=0; i < List_getLen(map->files); i++)
		File_destroy((File*)List_getData(map->files, i));
	List_destroy(map->files);
	List_destroy(map->staticFiles);
	List_destroy(map->dynamicFiles);
}
