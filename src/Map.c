#include "Map.h"

int32_t XML_depth = 0;

Map* Map_create(const char* path)
{
	Map* map          = (Map*)malloc(sizeof(Map));
	map->files        = List_create();
	map->staticFiles  = List_create();
	map->staticTraces = List_create();
	map->dynamicFiles = List_create();

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
	if(!strcmp(name, "Window"))
	{
		Map* self = (Map*)data;
		uint32_t i;
		for(i=0; attrs[i]; i+=2)
		{
			if(!strcmp(attrs[i], "numberCases"))
				getXYFromStr(attrs[i+1], &self->nbCaseX, &self->nbCaseY);
			else if(!strcmp(attrs[i], "tileSize"))
				getXYFromStr(attrs[i+1], &self->caseSizeX, &self->caseSizeY);
		}
	}
	//Set the start_function while parsing the file
	else if(!strcmp(name, "Files"))
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

	if(XML_depth == 2)
	{
		File* file = NULL;

		if(!strcmp(name, "Static"))
		{
			printf("Static Files \n");
			uint32_t spacingX, spacingY, tileSizeX, tileSizeY;
            
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "file"))
				{
					char p[60];
					sprintf(p, "Resources/%s", attrs[i+1]);
					file = File_create(p);
				}

                else if(!strcmp(attrs[i], "spacing"))
                    getXYFromStr(attrs[i+1], &(spacingX), &(spacingY));

                else if(!strcmp(attrs[i], "tileSize"))
                    getXYFromStr(attrs[i+1], &(tileSizeX), &(tileSizeY));
			}
			StaticFile* sf = StaticFile_create(file, tileSizeX, tileSizeY, spacingX, spacingY);
			List_addData(map->staticFiles, sf);
		}

        else if(!strcmp(name, "Dynamic"))
        {
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "file"))
				{
					char p[60];
					sprintf(p, "Resources/%s", attrs[i+1]);
					file = File_create(p);
				}
			}
        }

		if(file==NULL)
		{
			perror("Exit because can't load a file");
		}
		List_addData(map->files, file);
	}

	else if(XML_depth == 3)
	{
		if(List_getLen(map->files) == List_getLen(map->staticFiles)) //Because we load static files before dynamic files, if the len is equal, then the last file was static
		{
			StaticFile* sf = (StaticFile*)List_getData(map->staticFiles, List_getLen(map->staticFiles)-1);
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "type") && !strcmp(attrs[i+1], "ground"))
				{
					printf("create ground\n");
					StaticTileDatas* std = (StaticTileDatas*)malloc(sizeof(StaticTileDatas));
					std->createStaticTile = &Ground_create;
					List_addData(sf->tileDatas, (void*)std);
				}

				else
					List_addData(sf->tileDatas, NULL);
			}
		}

		else
		{
		}
	}

	else if(XML_depth == 4) //We know that we are handling DynamicTiles
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
	Map* self = (Map*)data;
	if(XML_depth == 2)
	{
		if(!strcmp(name, "StaticTrace"))
		{
			uint32_t sizeX, sizeY, padX, padY;
			uint32_t i;
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "size"))
					getXYFromStr(attrs[i+1], &sizeX, &sizeY);
				else if(!strcmp(attrs[i], "shift"))
					getXYFromStr(attrs[i+1], &padX, &padY);
			}
			StaticTrace* st = StaticTrace_create(sizeX, sizeY, self->nbCaseX * ((sizeX-padX)/self->caseSizeX), self->nbCaseY * ((sizeY-padY) / self->caseSizeY), padX, padY);
			List_addData(self->staticTraces, (void*)st);
		}
	}

	else if(XML_depth == 3)
	{
		if(!strcmp(name, "Column"))
		{
			CSVParser* tileID = CSVParser_create();
			CSVParser* fileID = CSVParser_create();

			uint32_t i;
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "fileID"))
				{
					printf("fileID %d \n", attrs[i+1]);
					CSVParser_parse(fileID, attrs[i+1]);
				}

				else if(!strcmp(attrs[i], "tileID"))
				{
					printf("tileID %d \n", attrs[i+1]);
					CSVParser_parse(tileID, attrs[i+1]);
				}
			}

			CSVParser_destroy(tileID);
			CSVParser_destroy(fileID);
		}
	}
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
	List_destroy(map->dynamicFiles);

	for(i=0; i < List_getLen(map->staticTraces); i++)
		StaticTrace_destroy((StaticTrace*)List_getData(map->staticTraces, i), true);
	List_destroy(map->staticTraces);

	for(i=0; i < List_getLen(map->staticFiles); i++)
		StaticFile_destroy((StaticFile*)List_getData(map->staticFiles, i));
	List_destroy(map->staticFiles);

	free(map);
}

StaticFile*  StaticFile_create(File* file, uint32_t tileSizeX, uint32_t tileSizeY, uint32_t spacingX, uint32_t spacingY)
{
	StaticFile* sf = (StaticFile*)malloc(sizeof(StaticFile));
	if(sf == NULL)
		return NULL;
	sf->tileSizeX = tileSizeX;
	sf->tileSizeY = tileSizeY;
	sf->spacingX  = spacingX;
	sf->spacingY  = spacingY;

	sf->tileDatas = List_create();
	sf->file      = file;

	return sf;
}

void  StaticFile_destroy(StaticFile* self)
{
	uint32_t i;
	for(i=0; i < List_getLen(self->tileDatas); i++)
		free(List_getData(self->tileDatas, i));
 	List_destroy(self->tileDatas);
	free(self);
}
