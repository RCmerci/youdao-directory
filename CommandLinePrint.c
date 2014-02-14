#include "CommandLinePrint.h"
#define BEFORE_PRINT if(trans->errorcode!=0){\
        switch (trans->errorcode){\
            case 20:printf("要翻译的文本过长.\n");break;\
            case 30:printf("无法进行有效翻译.\n");break;\
            case 40:printf("不支持的语言类型.\n");break;\
            case 50:printf("无效的key.\n");break;\
            default:printf("母鸡呀= =、\n");\
                         return;\
        }}
void clprint_simple(TRANS *trans){
    BEFORE_PRINT
    printf("%s:\n", trans->query);
    if(trans->translation[0]!=NULL){
        int i=0;
        while(trans->translation[i][0]!='\0'){
            printf("\t%s\n", trans->translation[i]);
            ++i;
        }
    }
}
void clprint_full(TRANS *trans){
    BEFORE_PRINT
    printf("%s\t[%s]:\n", trans->query, trans->phonetic);
    if(trans->translation[0]!=NULL){
        printf("translation:\n");
        int i=0;
        while(trans->translation[i][0]!='\0'){
            printf("\t%s\n", trans->translation[i]);
            ++i;
        }
    }
    if(trans->explains[0]!=NULL){
        printf("explains:\n");
        int i=0;
        while(trans->explains[i][0]!='\0'){
            printf("\t%s\n",trans->explains[i]);
            ++i;
        }
    }
    if(trans->key[0]!=NULL&&trans->value[0]!=NULL){
        printf("=============================\n网络释义\n=============================\n");
        int i=0;
        while(trans->key[i][0]!='\0'&&trans->value[i][0][0]!='\0'){
            int j;
            printf("KEY: %s\n",trans->key[i]);
            for(j=0;trans->value[i][j][0]!='\0';++j){
                printf("%s || ",trans->value[i][j]);
            }
            printf("\n-----------------------------\n");
            ++i;
        }
    }

}
