#ifndef GATHERDATA_H
#define GATHERDATA_H
#include "ParseJsonToData.h"
#define MAXBUF 1024
#define MAXBUF_2 32
#define MAXTRANS 10
#define MAXTRANS_2 8
typedef struct TRANS{
    int errorcode;
    char query[MAXBUF];
    char *translation[MAXTRANS];
    char phonetic[MAXBUF_2];
    char *explains[MAXTRANS];
    char *key[MAXTRANS];
    char **value[MAXTRANS_2];
}TRANS;
//Initialize trans structure.
//void trans_init(TRANS *trans);
//set data to trans structure.
//return 0 on success,-1 on failure.
//int trans_fill(TRANS *trans);
//create trans structure .
//0 on success.else -1.
int create_trans(TRANS *trans, cJSON *json);
#endif
