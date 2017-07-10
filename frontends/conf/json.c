#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
cJSON * json;
static cJSON *get_json(char *filename){
	cJSON *js = NULL;
	FILE *f;
	long len;
	char *data;
	f = fopen(filename, "rb");
	if(f){
		fseek(f, 0, SEEK_END);
		len = ftell(f);
		fseek(f, 0, SEEK_SET);
		data = (char *)malloc(len + 1);
		fread(data, 1, len, f);
		fclose(f);
		js = cJSON_Parse(data);
	}
	return js;
}
static void show_json(cJSON *js){
	char *out;
	out = cJSON_Print(js);
	printf("%s\n", out);	
}
static cJSON * find_sym_from_json(char *name, cJSON *js){
	cJSON * found;
	found = cJSON_GetObjectItem(js, name);
	return found;
}
void add_str(cJSON * js, char * key, char *value){
	cJSON * child;
	for (child = js->child; child; child = child->next){
		if (cJSON_IsObject(child)){
			cJSON_AddStringToObject(child, key, value);
			add_str(child, key, value);
		} else if(cJSON_IsArray(child)) {
			add_str(child, key, value);
		}
	}
}
int main(){
	
	json = get_json("./ex.json");
	add_str(json, "map", "1");
	// cJSON_AddStringToObject(json, "test", "123");
	show_json(json);
}