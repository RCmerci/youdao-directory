#ifndef PARSEJSONTODATA_H
#define PARSEJSONTODATA_H
#include <string.h>
#include "cJSON.h"


/*  return errorcode.0 on success.
 *  20->sentence to translate too long.
 *  30->can't translate effectively.
 *  40->the language unsupport.
 *  50->wrong api key.
 * */
int error_code(cJSON *json);
/* fetch "query" field.the content to translate.
 * the content will be set in dst.
 * return 0 on success,else -1.
 * */
int ret_query(cJSON *json, char *dst);
/* fetch "translation" field,the result.
 * the content will be set in dst.
 * return 0 on success,else -1.
 * */
int ret_translation(cJSON *json, char **dst);
/* fetch "phonetic" field.
 * set in dst.
 * return 0 on success,else -1.
 * */
int ret_phonetic(cJSON *json, char *dst);
/* fetch "explains" field.
 * set in dst.
 * return 0 on success,else -1.
 * */
int ret_explains(cJSON *json, char **dst);
/* fetch "key" field.(web translate)
 * set in dst.
 * return 0 on success,else -1.
 * */
int ret_key(cJSON *json, char **dst);
/* fetch "value" field.(web translate)
 * set in dst.
 * return 0 on success,else -1.
 * */
int ret_value(cJSON *json, char ***dst);
/**********return the whole json string*****************************/
char *ret_whole(cJSON *json);
#endif
