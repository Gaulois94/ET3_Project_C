#include "csv.h"

CSVParser* CSVParser_create()
{
	CSVParser* parser = (CSVParser*)malloc(sizeof(CSVParser));
	if(parser == NULL)
		return NULL;
	parser->values = NULL;
	parser->nbValue = 0;
	return parser;
}

bool CSVParser_parse(CSVParser* self, const char* string)
{
	int32_t value=0;
	int8_t signe=1;
	int32_t exposant=1;
	int8_t numberSize=-1;
	uint32_t stringIndice;

	for(stringIndice=0; string[stringIndice] != ',' && string[stringIndice] != ';' && string[stringIndice] != '\0' && string[stringIndice] != '\n'; stringIndice++)
	{
		if(string[stringIndice] == '-' && value == 0)
			signe *= -1;

		else if(string[stringIndice] == ' ')
			continue;

		else if(string[stringIndice] - '0' >= 0 && string[stringIndice] - '0' <= 9)
		{
			value += exposant * (string[stringIndice] - '0');
			exposant *= 10;
			numberSize++;
		}

		else
		{
			perror("Error while parsing. Abort \n");
			return false;
		}
	}

	if(numberSize == -1)
	{
		perror("Error while parsing. Abord \n");
		return false;
	}
	
	int32_t stringValue=0;
	int32_t i;
	for(i=0; i <= numberSize; i++)
	{
		stringValue *=10;
		stringValue += value % 10;
		value /=10;
	}

	stringValue *= signe;
	self->values = (int32_t*)realloc(self->values, (self->nbValue + 1)*sizeof(int32_t));
	self->values[self->nbValue] = stringValue;
	self->nbValue++;
	if(string[stringIndice] == '\n' || string[stringIndice] == '\0')	
		return true;
	return CSVParser_parse(self, &(string[stringIndice+1]));
}

const int32_t*   CSVParser_getValue(CSVParser* self)
{
	return self->values;
}
int32_t    CSVParser_getLen(CSVParser* self)
{
	return self->nbValue;
}
void       CSVParser_destroy(CSVParser* self)
{
	if(self->values)
		free(self->values);
	free(self);	
}
