/* A EN-CH-EN directory wrote in c.
 * Use cJSON,curl and youdao API.
 * 2014-2-12 
 */
#include "GatherStuff.h"
int simple_flag = 1;
char *str_to_trans;
TRANS trans_res;
void help_print(){
    printf("usage:\n");
    printf("\t -f  print full-version translation\n");
    printf("\t -q \"string to translate\"\n");
}
void argv_check(int argc,char **argv){
    if(argc<2){
        help_print();
        exit(EXIT_FAILURE);
    }
    int res,q_time=0;
    while((res = getopt(argc, argv, "q:f"))!=-1){
        switch (res){
            case 'q':
                if(optarg == NULL){
                    help_print();
                    exit(EXIT_FAILURE);
                }
                ++q_time;
                str_to_trans = optarg;break;
            case 'f':
                simple_flag = 0;break;
            default:
                help_print();
                exit(EXIT_FAILURE);
        }
    }
    if(q_time==0){
        help_print();
        exit(EXIT_FAILURE);
    }

}
size_t write_func(char *ptr, size_t size, size_t nmemb, void *userdata){
    memcpy(userdata, ptr, size*nmemb);
    ((char *)userdata)[size*nmemb] = '\0';
    return size*nmemb;
}
void * trans_thread(void *unuse){
    CURLcode retcode;
    CURL *curl = curl_easy_init();
    if(curl==NULL){
        fprintf(stderr,"translate failed_1\n");
        pthread_exit("-1");
    }
    char buf[512],ret_buf[MAXBUF*2],*convert_str;
    sprintf(buf, "%s", APIkey);
    convert_str = curl_easy_escape(curl,str_to_trans,strlen(str_to_trans));
    strcat(buf, convert_str);
    curl_easy_setopt(curl, CURLOPT_URL, buf);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret_buf);
    retcode = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if(retcode != 0){
        fprintf(stderr,"translate failed_2\n");
        pthread_exit("-1");
    }
    cJSON *json;
    json = cJSON_Parse(ret_buf);
    if(create_trans(&trans_res, json) == -1){
        fprintf(stderr,"translate failed_3\n");
        pthread_exit("-1");
    }
    if(simple_flag == 1)
        clprint_simple(&trans_res);
    else
        clprint_full(&trans_res);
    curl_free(convert_str);
    pthread_exit("0");
}
int main(int argc, char **argv){
    pthread_t thread_1;
    int ret_code;
    argv_check(argc,argv);
    pthread_create(&thread_1, NULL, trans_thread, NULL);
    ret_code = pthread_join(thread_1, NULL);
    //printf("retcode:%d\n",ret_code);
    return 0;
}
