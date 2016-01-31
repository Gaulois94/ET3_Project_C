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

/** \brief parse the string "string"
 * \param self the CSVParser itself
 * \param string the string to parse
 * \return return if the parser has correctly parsed the file or not*/
bool       CSVParser_parse(CSVParser* self, const char* string);

/** \brief get the value of the Parser
 * \param parser the CSVParser itself
 * \return the value array of the parser. Use getLen to get the value array's length*/
const int32_t*   CSVParser_getValues(CSVParser* parser);

/** \brief returns the length of the array values
 * \param self the CSVParser itself
 * \return the number of values of the parser*/
int32_t    CSVParser_getLen(CSVParser* parser);
void       CSVParser_destroy(CSVParser* self);

#endif
