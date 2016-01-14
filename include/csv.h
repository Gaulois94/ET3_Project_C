#ifndef  CSV_INC
#define  CSV_INC

typedef struct
{
	int32_t* values;
	uint32_t nbValue;
}CSVParser;

CSVParser* CSVParser_create();
bool       CSVParser_parse(CSVParser* self, const char* string);
const int32_t*   CSVParser_getValue(CSVParser_getValue);
int32_t    CSVParser_getLen(CSVParser_getValue);
void       CSVParser_destroy(CSVParser* self);

#endif
