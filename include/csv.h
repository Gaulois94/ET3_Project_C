#ifndef  CSV_INC
#define  CSV_INC

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "typedefine.h"

typedef struct
{
	int32_t* values;
	uint32_t nbValue;
}CSVParser;

CSVParser* CSVParser_create();
bool       CSVParser_parse(CSVParser* self, const char* string);
const int32_t*   CSVParser_getValues(CSVParser* parser);
int32_t    CSVParser_getLen(CSVParser* parser);
void       CSVParser_destroy(CSVParser* self);

#endif
