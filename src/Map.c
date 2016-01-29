#include "Map.h"
#include "globalVar.h"

uint32_t XML_depth = 0;
uint32_t XML_NthColumn = 0;

Map* Map_create(const char* path)
{
	//Init all map variables
	Map* map          = (Map*)malloc(sizeof(Map));
	map->files        = List_create();
	map->staticFiles  = List_create();
	map->staticTraces = List_create();
	map->dynamicTraces = List_create();
	map->dynamicFiles = List_create();
	map->objects      = List_create();
	map->startX       = 0;
	map->startY       = 0;

	//Init the parser
	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetUserData(parser, (void*)map);
	XML_SetElementHandler(parser, &startElement, &endElement);
	map->parser = parser;

	//Get the xml code
	FILE* file = fopen(path, "r");
	if(file == NULL)
	{
		Map_destroy(map);
		return NULL;
	}
	char line[100];

	while(fgets(line, 100, file) != NULL)
	{
		uint32_t lineLength = strlen(line);
		if(XML_Parse(parser, line, lineLength, 0) == 0)
			perror("Error in parsing the XML code");
	}

	fclose(file);
	file = NULL;

	//Then finally launch the parse process
	if(XML_Parse(parser, NULL, 0, 1) == 0)
		perror("Error in parsing the XML code");

	XML_ParserFree(parser);

	return map;
}

SDL_Rect Map_getRect(Map* self)
{
	//Get the map rect
	SDL_Rect r;
	r.x = r.y = 0;
	r.w = self->nbCasesX * self->caseSizeX;
	r.h = self->nbCasesY * self->caseSizeY;
	return r;
}

void Map_draw(Map* self, Window* window)
{
	uint32_t i;
	//Draw every static traces
	for(i=0; i < List_getLen(self->staticTraces); i++)
	{
		StaticTrace* st = (StaticTrace*)List_getData(self->staticTraces, i);
		StaticTrace_draw(st, window);
	}

	//Then all the dynamic traces
	for(i=0; i < List_getLen(self->dynamicTraces); i++)
	{
		DynamicTrace* dt = (DynamicTrace*)List_getData(self->dynamicTraces, i);
		DynamicTrace_draw(dt, window);
	}
}

Tile* Map_getDynamicTile(Map* self, uint32_t x, uint32_t y)
{
	DynamicTrace* dt = (DynamicTrace*)List_getData(self->dynamicTraces, 0);
	if(!dt)
		return NULL;
	return DynamicTrace_getTile(dt, x, y);
}

List* Map_getDynamicList(Map* self, uint32_t x, uint32_t y)
{
	DynamicTrace* dt = (DynamicTrace*)List_getData(self->dynamicTraces, 0);
	if(!dt)
		return NULL;
	return DynamicTrace_getList(dt, x, y);
}

Tile* Map_getTileInfo(Map* self, int32_t x, int32_t y)
{
	uint32_t i;
	Tile* tile;
	for(i=0; i < List_getLen(self->staticTraces); i++)
	{
		StaticTrace* st = (StaticTrace*)List_getData(self->staticTraces, i);
		tile = StaticTrace_getTile(st, x, y);
		if(tile != NULL)
			return tile;
	}
	return NULL;
}

Object* Map_getObjectInfo(Map* self, int32_t x, int32_t y)
{
	uint32_t i;
	Object* object;
	for(i=0; i < List_getLen(self->staticTraces); i++)
	{
		StaticTrace* st = (StaticTrace*)List_getData(self->staticTraces, i);
		object = StaticTrace_getObject(st, x, y);
		if(object != NULL)
			return object;
	}
	return NULL;
}

SDL_Point Map_getStartCoords(Map* self)
{
	SDL_Point p;
	p.x = self->startX;
	p.y = self->startY;
	return p;
}

bool  Map_isOutside(Map* self, int32_t x, int32_t y)
{
	if(x < 0 || y < 0 || x / self->caseSizeX >= self->nbCasesX || y / self->caseSizeY >= self->nbCasesY)
		return true;
	return false;
}

void startElement(void *data, const char* name, const char** attrs)
{
	//Get the window valye (nbCases and tileSize)
	if(!strcmp(name, "Window"))
	{
		Map* self = (Map*)data;
		uint32_t i;
		for(i=0; attrs[i]; i+=2)
		{
			if(!strcmp(attrs[i], "numberCases"))
				getXYFromStr(attrs[i+1], &self->nbCasesX, &self->nbCasesY);
			else if(!strcmp(attrs[i], "tileSize"))
				getXYFromStr(attrs[i+1], &self->caseSizeX, &self->caseSizeY);
		}
	}

	//Set the correct start function following the section (Files for Files, etc.)
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
		File* file = NULL; //The image file

		//If the section if for Static files
		if(!strcmp(name, "Static"))
		{
			//Then get the information about it
			uint32_t spacingX, spacingY, tileSizeX, tileSizeY;
			for(i=0; attrs[i]; i+=2)
			{
				//The path
				if(!strcmp(attrs[i], "file"))
				{
					char p[60];
					sprintf(p, "Resources/%s", attrs[i+1]);
					file = File_create(p);
				}

				//The spacing
                else if(!strcmp(attrs[i], "spacing"))
                    getXYFromStr(attrs[i+1], &(spacingX), &(spacingY));

				//And tile size
                else if(!strcmp(attrs[i], "tileSize"))
                    getXYFromStr(attrs[i+1], &(tileSizeX), &(tileSizeY));
			}
			//Then create it and store it
			StaticFile* sf = StaticFile_create(file, tileSizeX, tileSizeY, spacingX, spacingY);
			List_addData(map->staticFiles, sf);
		}

		//Or if the file is a Dynamic file
        else if(!strcmp(name, "Dynamic"))
        {
			for(i=0; attrs[i]; i+=2)
			{
				//Get the path of the file
				if(!strcmp(attrs[i], "file"))
				{
					char p[60];
					sprintf(p, "Resources/%s", attrs[i+1]);
					file = File_create(p);
				}
			}

			//Then create it and store it
			DynamicFile* df = DynamicFile_create(file);
			List_addData(map->dynamicFiles, df);
        }

		//If a file isn't created
		if(file==NULL)
		{
			perror("Exit because can't load a file \n");
			return;
		}
		//Store this file (the image one)
		List_addData(map->files, file);
	}

	else if(XML_depth == 3)
	{
		if(List_getLen(map->files) == List_getLen(map->staticFiles)) //Because we load static files before dynamic files, if the len is equal, then the last file was static
		{
			//Get the last static file
			StaticFile* sf = (StaticFile*)List_getData(map->staticFiles, List_getLen(map->staticFiles)-1);
			for(i=0; attrs[i]; i+=2)
			{
				//Following the type, we set the tile datas (over all its pointer to the create function. It is it which will be called for created this tile after that, when needed.
				if(!strcmp(attrs[i], "type"))
				{
					if(!strcmp(attrs[i+1], "ground"))
					{
						StaticTileDatas* std = (StaticTileDatas*)malloc(sizeof(StaticTileDatas));
						std->createStaticTile = &Ground_create;
						List_addData(sf->tileDatas, (void*)std);
					}
					else if(!strcmp(attrs[i+1], "coin"))
					{
						StaticTileDatas* std = (StaticTileDatas*)malloc(sizeof(StaticTileDatas));
						std->createStaticTile = &Coin_create;
						List_addData(sf->tileDatas, (void*)std);
					}

					else if(!strcmp(attrs[i+1], "start"))
					{
						StaticTileDatas* std = (StaticTileDatas*)malloc(sizeof(StaticTileDatas));
						std->createStaticTile = &TileStart_create;
						List_addData(sf->tileDatas, (void*)std);
					}

					else
						List_addData(sf->tileDatas, NULL);
				}
			}
		}

		//If we aren't dealing with static files, then we are with dynamic files
		else
		{
			DynamicFile* df = (DynamicFile*)List_getData(map->dynamicFiles, List_getLen(map->dynamicFiles)-1);

			//Creating a dynamic entity which will contain all the subrect for this animation (dynamic == animation), and the create function for this tile
			DynamicEntity* de = (DynamicEntity*)malloc(sizeof(DynamicEntity));
			de->tileRects = List_create();
			de->update = NULL;
			de->data = NULL;

			uint32_t i;
			for(i=0; attrs[i]; i+=2)
			{
				//Following the name
				if(!strcmp(attrs[i], "name"))
				{
					if(!strcmp(attrs[i+1], "goomba"))
					{
						de->createDynamicTile = &Goomba_create;
						de->update = &basicIA;
						de->data = globalVar_game;
					}
					ResourcesManager_addData(df->dynamicEntities, "goomba", (void*)de);
				}
			}
		}
	}

	//This part is only for dynamic files, wich contain position and size for dynamic entities
	else if(XML_depth == 4)
	{
		//Get the last dynamic files
		DynamicFile* df = (DynamicFile*)List_getData(map->dynamicFiles, List_getLen(map->dynamicFiles)-1);
		DynamicEntity* de = (DynamicEntity*)ResourcesManager_getDataByID(df->dynamicEntities, ResourcesManager_getLen(df->dynamicEntities)-1);

		//Then create the rect for this animation
		SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
		uint32_t i;
		for(i=0; attrs[i]; i+=2)
		{
			if(!strcmp(attrs[i], "pos"))
				getXYFromStr(attrs[i+1], &(rect->x), &(rect->y));

			else if(!strcmp(attrs[i], "size"))
				getXYFromStr(attrs[i+1], &(rect->w), &(rect->h));
		}
		List_addData(de->tileRects, (void*)rect);
	}
	XML_depth++; //We see to the next XML depth
}

void startElementObjects(void *data, const char* name, const char** attrs)
{
	Map* map = (Map*)data;
	if(XML_depth == 2)
	{
		uint32_t i;
		ObjectDatas* objDatas = ObjectDatas_create();
		//Get object information
		for(i=0; attrs[i]; i+=2)
		{
			if(!strcmp(attrs[i], "numberCase"))
				getXYFromStr(attrs[i+1], &(objDatas->nbCasesX), &(objDatas->nbCasesY));
			else if(!strcmp(attrs[i], "tileSize"))
				getXYFromStr(attrs[i+1], &(objDatas->tileSizeX), &(objDatas->tileSizeY));

			//And set the pointer function for creating this object
			else if(!strcmp(attrs[i], "name"))
			{
				if(!strcmp(attrs[i+1], "finish"))
					objDatas->createObject = &Finish_create;
			}
		}
		List_addData(map->objects, (void*)objDatas);
	}

	//Here we deal with information about tile (what tile it is ?)
	else if(XML_depth == 3)
	{
		char* tileID;
		char* fileID;
		uint32_t i;
		for(i=0; attrs[i]; i+=2)
		{
			//Get the file ID bound to these tiles
			if(!strcmp(attrs[i], "fileID"))
			{
				fileID = (char*)malloc(sizeof(char)*(1+strlen(attrs[i+1])));
				strcpy(fileID, attrs[i+1]);
			}

			//And the tile id for this file
			else if(!strcmp(attrs[i], "tileID"))
			{
				tileID = (char*)malloc(sizeof(char)*(1+strlen(attrs[i+1])));
				strcpy(tileID, attrs[i+1]);
			}
		}

		//Create CSV datas
		ObjectDatas* objDatas = (ObjectDatas*)List_getData(map->objects, List_getLen(map->objects)-1);
		List_addData(objDatas->CSVTileID, tileID);
		List_addData(objDatas->CSVFileID, fileID);
	}

	XML_depth++;
}

void startElementTraces(void *data, const char* name, const char** attrs)
{
	Map* self = (Map*)data;
	if(XML_depth == 2)
	{
		//Are we dealing with static trace ?
		if(!strcmp(name, "StaticTrace"))
		{
			//Get the size and the padding of it
			uint32_t sizeX, sizeY, padX, padY;
			uint32_t i;
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "size"))
					getXYFromStr(attrs[i+1], &sizeX, &sizeY);
				else if(!strcmp(attrs[i], "shift"))
					getXYFromStr(attrs[i+1], &padX, &padY);
			}
			//Then create and store it
			StaticTrace* st = StaticTrace_create(sizeX, sizeY, self->nbCasesX * ((sizeX-padX)/self->caseSizeX), self->nbCasesY * ((sizeY-padY) / self->caseSizeY), padX, padY);
			List_addData(self->staticTraces, (void*)st);
			XML_NthColumn=0;
		}
		
		//Or create a dynamic trace
		else if(!strcmp(name, "DynamicTrace"))
		{
			//Give the map caseSize and map nbCases for squaring it (useful for collision : we don't check over all the trace !)
			DynamicTrace* dt = DynamicTrace_create(self->nbCasesX, self->nbCasesY, self->caseSizeX, self->caseSizeY);
			List_addData(self->dynamicTraces, (void*)dt);
		}
	}

	else if(XML_depth == 3)
	{
		//COlumn is for static tile
		if(!strcmp(name, "Column"))
		{
			//Get the last static trace
			StaticTrace* st = (StaticTrace*)List_getData(self->staticTraces, List_getLen(self->staticTraces)-1);

			//Get tileID, object ID and fileID CSV values
			CSVParser* tileCSVID = CSVParser_create();
			CSVParser* fileCSVID = CSVParser_create();
			CSVParser* objectCSVID = CSVParser_create();

			//And parse these CSV
			uint32_t i;
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "fileID"))
					CSVParser_parse(fileCSVID, attrs[i+1]);

				else if(!strcmp(attrs[i], "tileID"))
					CSVParser_parse(tileCSVID, attrs[i+1]);
				else if(!strcmp(attrs[i], "objectID"))
					CSVParser_parse(objectCSVID, attrs[i+1]);
			}

			//Get CSV values
			const int32_t* tileID   = CSVParser_getValues(tileCSVID);
			const int32_t* fileID   = CSVParser_getValues(fileCSVID);
			const int32_t* objectID = CSVParser_getValues(objectCSVID);

			//We check if we have normal tiles to parse
			for(i=0; i < CSVParser_getLen(tileCSVID); i++)
			{
				if(tileID[i] != -1 && fileID[i] != -1)
				{
					//Getthe file following the file ID (id 0 --> first file created)
					StaticFile* sf  = List_getData(self->staticFiles, fileID[i]);

					//And create this tile
					Tile* tile      = StaticFile_createTile(sf, tileID[i], false);

					//If the tile is created
					if(tile != NULL)
					{
						if(st != NULL)
							StaticTrace_addTile(st, tile, XML_NthColumn, i); //Add it

						//And if this tile is the beginning of the map
						if(Tile_getInfo(tile) & BEGIN)
						{
							//!Set the start point of the map
							const SDL_Rect* tileRect = Drawable_getRect((Drawable*)tile);
							self->startX = tileRect->x;
							self->startY = tileRect->y;
						}
					}
				}

				//Then we look at the objects
				//Object id start from 1.
				else if(objectID[i] > 0)
				{
					//Get the object datas for this id
					ObjectDatas* objDatas   = (ObjectDatas*)List_getData(self->objects, objectID[i]-1);
					if(objDatas->createObject == NULL)
						continue;

					//Create this object
					Object* obj = objDatas->createObject(objDatas->nbCasesX, objDatas->nbCasesY, objDatas->tileSizeX, objDatas->tileSizeY);

					uint32_t j;
					for(j=0; j < List_getLen(objDatas->CSVTileID); j++)
					{
						//Parse CSV fileID and tileID
						CSVParser* objectTileID = CSVParser_create();
						CSVParser* objectFileID = CSVParser_create();

						CSVParser_parse(objectTileID, (char*)List_getData(objDatas->CSVTileID, j));
						CSVParser_parse(objectFileID, (char*)List_getData(objDatas->CSVFileID, j));

						const uint32_t* tileID = CSVParser_getValues(objectTileID);
						const uint32_t* fileID = CSVParser_getValues(objectFileID);

						//Then create the tiles bound to the Object
						uint32_t k;
						for(k=0; k < CSVParser_getLen(objectTileID); k++)
						{
							//Get the file with the fileID
							StaticFile* sf = (StaticFile*)List_getData(self->staticFiles, fileID[k]);
							if(sf == NULL)
								continue;

							//And create the tile
							Tile* tile = StaticFile_createTile(sf, tileID[k], true);
							if(tile == NULL)
								continue;

							//Then add this tile
							Object_addTile(obj, j, k, tile);
						}

						//Destroy CSV value
						CSVParser_destroy(objectTileID);
						CSVParser_destroy(objectFileID);
					}
					StaticTrace_addObject(st, obj, XML_NthColumn, i);
				}
			}

			//Destroy useless variable
			CSVParser_destroy(tileCSVID);
			CSVParser_destroy(fileCSVID);
			CSVParser_destroy(objectCSVID);
			XML_NthColumn++;
		}

		//If we are with dynamic tile
		else if(!strcmp(name, "DynamicTile"))
		{
			//Get information about is
			char name[50];
			uint32_t fileID;
			int32_t posX, posY;
			uint32_t tileID;

			uint32_t i;
			for(i=0; attrs[i]; i+=2)
			{
				if(!strcmp(attrs[i], "tileID"))
					tileID = atoi(attrs[i+1]);
				else if(!strcmp(attrs[i], "position"))
					getXYFromStr(attrs[i+1], &posX, &posY);
				else if(!strcmp(attrs[i], "fileID"))
					fileID = atoi(attrs[i+1]);
				else if(!strcmp(attrs[i], "animName"))
					strcpy(name, attrs[i+1]);
			}

			//Get the last dynamic trace
			DynamicTrace* dt = (DynamicTrace*)List_getData(self->dynamicTraces, List_getLen(self->dynamicTraces)-1);

			//The correct dynamic file
			DynamicFile* df = List_getData(self->dynamicFiles, fileID - List_getLen(self->staticFiles));
			if(df)
			{
				uint32_t i;
				//Get the entity of this tile
				DynamicEntity* de = (DynamicEntity*)ResourcesManager_getData(df->dynamicEntities, name);

				//Get the texture rect for this animation
				SDL_Rect* textureRect = (SDL_Rect*)List_getData(de->tileRects, tileID);

				//Set the tile position
				SDL_Rect dest;
				dest.x = posX;
				dest.y = posY;
				dest.w = textureRect->w;
				dest.h = textureRect->h;

				//Need this array for giving all our SDL_Rect* on TectureRect to the animation
				const SDL_Rect** subRects = (const SDL_Rect**)malloc(sizeof(SDL_Rect*)*List_getLen(de->tileRects));
				for(i=0; i < List_getLen(de->tileRects); i++)
					subRects[i] = (SDL_Rect*)List_getData(de->tileRects, i);
				
				//Then finally create the tile
				Tile* tile = de->createDynamicTile(&dest, File_getTexture(df->file), subRects, List_getLen(de->tileRects), 0, 8);
				Tile_setUpdate(tile, de->update, de->data);
				DynamicTrace_addTile(dt, tile);
				free(subRects);
			}
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
	if(map == NULL)
		return;
	uint32_t i;
	if(map->files)
	{
		for(i=0; i < List_getLen(map->files); i++)
			File_destroy((File*)List_getData(map->files, i));
		List_destroy(map->files);
	}
	List_destroy(map->dynamicFiles);

	for(i=0; i < List_getLen(map->staticTraces); i++)
		StaticTrace_destroy((StaticTrace*)List_getData(map->staticTraces, i), true);
	List_destroy(map->staticTraces);

	for(i=0; i < List_getLen(map->staticFiles); i++)
		StaticFile_destroy((StaticFile*)List_getData(map->staticFiles, i));
	List_destroy(map->staticFiles);

	for(i=0; i < List_getLen(map->dynamicTraces); i++)
		DynamicTrace_destroy((DynamicTrace*)List_getData(map->dynamicTraces, i));
	List_destroy(map->dynamicTraces);

	for(i=0; i < List_getLen(map->objects); i++)
		ObjectDatas_destroy((ObjectDatas*)List_getData(map->objects, i));
	List_destroy(map->objects);

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

List* StaticFile_getTiles(StaticFile* self)
{
	return self->tileDatas;
}

Tile* StaticFile_createTile(StaticFile* self, int32_t tileID, bool def)
{
	StaticTileDatas* tile ;
	//If we don't want to use the default tile
	if(!def)
	{
		//Then create it
		tile = (StaticTileDatas*)(List_getData(self->tileDatas, tileID));
		if(tile == NULL)
			return NULL;
	}

	//Get the texture of this file
	SDL_Texture* texture = File_getTexture(self->file);
	//And its size
	int32_t tWidth, tHeight;
	SDL_QueryTexture(texture, NULL, NULL, &tWidth, &tHeight);

	//Get the tile position on X 
	uint32_t numberTileX=0;
	while(tWidth > 0)
	{
		tWidth -= self->tileSizeX;
		if(numberTileX != 0)
			tWidth -= self->spacingX;
		numberTileX++;
	}
	
	//Then create the subrect of this tile
	SDL_Rect subRect;
	subRect.x = (tileID % numberTileX) * (self->tileSizeX + self->spacingX);
	subRect.y = (tileID / numberTileX) * (self->tileSizeY + self->spacingY);
	subRect.w = self->tileSizeX;
	subRect.h = self->tileSizeY;

	//And return it
	if(!def)
		return tile->createStaticTile(texture, &subRect); //Create the tile
	return DefaultTile_create(texture, &subRect); //return the default tile
}

DynamicFile* DynamicFile_create(File* file)
{
	DynamicFile* df = (DynamicFile*)malloc(sizeof(DynamicFile));
	if(df==NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	df->file = file;
	df->dynamicEntities = ResourcesManager_create();
	return df;
}

void DynamicFile_destroy(DynamicFile* self)
{
	uint32_t i;
	for(i=0; i < ResourcesManager_getLen(self->dynamicEntities); i++)
		free(ResourcesManager_getDataByID(self->dynamicEntities, i));
	ResourcesManager_destroy(self->dynamicEntities);
	free(self);
}

void  StaticFile_destroy(StaticFile* self)
{
	uint32_t i;
	for(i=0; i < List_getLen(self->tileDatas); i++)
		free(List_getData(self->tileDatas, i));
 	List_destroy(self->tileDatas);

	free(self);
}
