#include "ParseJsonToData.h"
//return 0 if exist.
static item_exist(cJSON *json, char *str){
    if(json->child == NULL)return -1;
    cJSON *c = json->child;
    while(c){
        if(strncmp(c->string, str, strlen(str)) == 0)return 0;
        c = c->next;
    }
    return -1;
}
int error_code(cJSON *json){
    return cJSON_GetObjectItem(json, "errorCode")->valueint;
}
int ret_query(cJSON *json, char *dst){
    if(item_exist(json, "query"))return -1;
    char *temp = cJSON_GetObjectItem(json, "query")->valuestring;
    memcpy(dst, temp, strlen(temp)+1);
    return 0;
}
int ret_translation(cJSON *json, char **dst){
    if(item_exist(json, "translation"))return -1;
    cJSON *temp = cJSON_GetObjectItem(json, "translation");
    int size = cJSON_GetArraySize(temp);
    if(size == 0)return -1;
    int i;
    char *str;
    for(i=0;i<size;++i){
        str = cJSON_GetArrayItem(temp, i)->valuestring;
        memcpy(*(dst+i), str, strlen(str)+1);
    }
    **(dst+i) = '\0';
    return 0;
}
int ret_phonetic(cJSON *json, char *dst){
    if(item_exist(json, "basic"))return -1;
    cJSON *obj = cJSON_GetObjectItem(json, "basic");
    if(item_exist(obj, "phonetic"))return -1;
    char *temp = cJSON_GetObjectItem(obj, "phonetic")->valuestring;
    memcpy(dst, temp, strlen(temp)+1);
    return 0;
}
int ret_explains(cJSON *json, char **dst){
    if(item_exist(json, "basic"))return -1;
    cJSON *obj = cJSON_GetObjectItem(json, "basic");
    if(item_exist(obj, "explains"))return -1;
    cJSON *temp = cJSON_GetObjectItem(obj, "explains");
    int size = cJSON_GetArraySize(temp);
    if(size == 0)return -1;
    int i;
    char *str;
    for(i=0;i<size;++i){
        str = cJSON_GetArrayItem(temp, i)->valuestring;
        memcpy(*(dst+i), str, strlen(str)+1);
    }
    **(dst+i) = '\0';
    return 0;
}
int ret_key(cJSON *json, char **dst){
    if(item_exist(json, "web"))return -1;
    cJSON *array = cJSON_GetObjectItem(json, "web");
    int size_1 = cJSON_GetArraySize(array);
    if(size_1 == 0)return -1;
    int i;
    for(i=0;i<size_1;++i){
        cJSON *json_1 = cJSON_GetArrayItem(array, i);
        if(item_exist(json_1, "key"))continue;
        char *str = cJSON_GetObjectItem(json_1, "key")->valuestring;
        memcpy(*(dst+i), str, strlen(str)+1);
    }
    **(dst+i) = '\0';
    return 0;
}
int ret_value(cJSON *json, char ***dst){
    if(item_exist(json, "web"))return -1;
    cJSON *array = cJSON_GetObjectItem(json, "web");
    int size_1 = cJSON_GetArraySize(array);
    if(size_1 == 0)return -1;
    int i,j,size_2;
    cJSON *obj, *array_1;
    char *str;
    for(i=0;i<size_1;++i){
        obj = cJSON_GetArrayItem(array, i);
        if(item_exist(obj, "value")){
            memcpy(**(dst+i), "None", 5);
            **(*(dst+i)+1) = '\0';
            continue;
        }
        array_1 = cJSON_GetObjectItem(obj, "value");
        size_2 = cJSON_GetArraySize(array_1);
        if(size_2 == 0){
            memcpy(**(dst+i),"None",5);
        }
        else{
            for(j=0;j<size_2;++j){
                str = cJSON_GetArrayItem(array_1, j)->valuestring;
                memcpy(*(*(dst+i)+j), str, strlen(str)+1);
            }
            **(*(dst+i)+j) = '\0';
        }
    }
    ***(dst+i) = '\0';
    return 0;
}
char *ret_whole(cJSON *json){
    return cJSON_Print(json);
}

