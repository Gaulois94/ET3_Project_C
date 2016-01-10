#include "Map.h"

uint32_t XML_depth = 0;

Map* openMap(const char* path)
{
	Map* map          = (Map*)malloc(sizeof(Map));
	map->staticFiles  = List_createList();
	map->dynamicFiles = List_createList();

	//Init the parser
	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetUserData(parser, (void*)map);
	XML_SetElementHandler(parser, startElement, end_element);

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

	if(XML_depth == 1)
	{
		if(!strcmp(name, "Static"))
		{
			StaticFiles* sf = (StaticFiles*)malloc(sizeof(StaticFiles));
            
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "file"))
                {
                    SDL_Surface* image;
                    SDL_Texture* texture=NULL;
                    if(!(image = IMG_Load(attrs[i+1])))
                        SDL_Texture* texture = SDL_CreateTextureFromSurface(globalVar_window->renderer, image);
                    sf->texture = texture;
                }

                else if(!strcmp(attrs[i], "spacing"))
                    getXYFromStr(attrs[i+1], &(sf->spacingX), &(sf->spacingY));

                else if(!strcmp(attrs[i], "tileSize"))
                    getXYFromStr(attrs[i+1], &(sf->tileSizeX), &(sf->tileSizeY));
			}
		}

        else if(!strcmp(name, "StaticTile"))
        {
        }
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
		XML_SetElementHandler(((Map*)data)->parser, startElement, end_element);
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
