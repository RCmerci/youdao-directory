#include "GatherData.h"
#include <stdlib.h>
static void trans_init(TRANS *trans){
    trans->errorcode = -1;
    trans->query[0]='\0';
    trans->translation[0] = NULL;
    trans->phonetic[0] = '\0';
    trans->explains[0] = NULL;
    trans->key[0] = NULL;
    trans->value[0] = NULL;
}
static int trans_fill(TRANS *trans,cJSON *json){
    trans->errorcode = error_code(json);
    if(trans->errorcode!=0)return 0;
    if(ret_query(json, trans->query)==-1)return -1;
    int i;
    for(i=0;i<MAXTRANS;++i)
        trans->translation[i] = malloc(sizeof(char)*MAXBUF);
    if(ret_translation(json,trans->translation)==-1){
        for(i=0;i<MAXTRANS;++i)free(trans->translation[i]);
        trans->translation[0] = NULL;
    }
    if(ret_phonetic(json, trans->phonetic)==-1)
        trans->phonetic[0] = '\0';
    for(i=0;i<MAXTRANS;++i)
        trans->explains[i] = malloc(sizeof(char)*MAXBUF);
    if(ret_explains(json, trans->explains)==-1){
        for(i=0;i<MAXTRANS;++i)free(trans->explains[i]);
        trans->explains[0] = NULL;
    }
    for(i=0;i<MAXTRANS;++i)
        trans->key[i] = malloc(sizeof(char)*MAXBUF);
    if(ret_key(json, trans->key)==-1){
        for(i=0;i<MAXTRANS;++i)free(trans->key[i]);
        trans->key[0] = NULL;
    }
    int j;
    for(i=0;i<MAXTRANS_2;++i){
        trans->value[i] = malloc(sizeof(char*)*MAXTRANS);
        for(j=0;j<MAXTRANS;++j){
            trans->value[i][j] = malloc(sizeof(char)*MAXBUF);
        }
    }
    if(ret_value(json, trans->value)==-1){
        for(i=0;i<MAXTRANS_2;++i){
            for(j=0;j<MAXTRANS;++j){
                free(trans->value[i][j]);
            }
            free(trans->value[i]);
        }
        trans->value[0] = NULL;
    }
    return 0;
}
int create_trans(TRANS *trans, cJSON *json){
    trans_init(trans);
    return trans_fill(trans,json);
}
