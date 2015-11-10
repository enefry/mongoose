// Copyright (c) 2015 Cesanta Software Limited
// All rights reserved

#include "mongoose.h"
#include "unistd.h"
#include "DataBuffer.h"
#include "stdio.h"
static char *s_http_port = "80";
static struct mg_serve_http_opts s_http_server_opts;

static DataBuffer document_root_str ;
static DataBuffer index_files_str ;
static DataBuffer access_log_file_str ;
static DataBuffer per_directory_auth_file_str ;
static DataBuffer auth_domain_str ;
static DataBuffer global_auth_file_str ;
static DataBuffer enable_directory_listing_str ;
static DataBuffer ssi_pattern_str ;
static DataBuffer ip_acl_str ;
static DataBuffer url_rewrites_str ;
static DataBuffer dav_document_root_str ;
static DataBuffer dav_auth_file_str ;
static DataBuffer hidden_file_pattern_str ;
static DataBuffer cgi_file_pattern_str ;
static DataBuffer cgi_interpreter_str ;
static DataBuffer custom_mime_types_str ;

static DataBuffer listening_port_str ;

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        mg_serve_http(nc, p, s_http_server_opts);
    }
}


void GetContextIdx(const char *key, int idx, int length , DataBuffer*data)
{
    DataBufferremoveAll(data);
    int contextBegin = idx+1;
    while(contextBegin < length && isspace (key[contextBegin]))
    {
        contextBegin ++;
    }
    int contextEnd = length;
    while(contextEnd > contextBegin && !isspace (key[contextEnd]))
    {
        contextEnd --;
    }
    DataBufferremoveAll(data);
    DataBufferAppendChars (data,key+contextBegin,contextEnd-contextBegin);
    DataBufferAppendChar (data,'\0');
}

void readConfLine(const char*line,int length){
    if(length < 3 || line == NULL){
        return;
    }
    const char*key = line;
    while(isspace (*key)){
        key++;
    }
    length = length - ( key - line);
    int idx = 0;
    for(;idx<length;idx++){
        if(isspace (key[idx])){
            break;
        }
    }
    switch(idx){
    case 6 :
    {

        if( 0 == strncmp(key,"ip_acl" ,idx )){
            GetContextIdx(key,idx,length,&ip_acl_str);
            DataBufferAppendChar (&ip_acl_str,'\0');
            s_http_server_opts.ip_acl = DataBufferPtr(&ip_acl_str);
            break;
        }
        break;
    }
    case 11 :
    {

        if( 0 == strncmp(key,"index_files" ,idx )){
            GetContextIdx(key,idx,length,&index_files_str);
            DataBufferAppendChar (&index_files_str,'\0');
            s_http_server_opts.index_files = DataBufferPtr(&index_files_str);
            break;
        }
        if( 0 == strncmp(key,"auth_domain" ,idx )){
            GetContextIdx(key,idx,length,&auth_domain_str);
            DataBufferAppendChar (&auth_domain_str,'\0');
            s_http_server_opts.auth_domain = DataBufferPtr(&auth_domain_str);
            break;
        }
        if( 0 == strncmp(key,"ssi_pattern" ,idx )){
            GetContextIdx(key,idx,length,&ssi_pattern_str);
            DataBufferAppendChar (&ssi_pattern_str,'\0');
            s_http_server_opts.ssi_pattern = DataBufferPtr(&ssi_pattern_str);
            break;
        }
        break;
    }
    case 12 :
    {

        if( 0 == strncmp(key,"url_rewrites" ,idx )){
            GetContextIdx(key,idx,length,&url_rewrites_str);
            DataBufferAppendChar (&url_rewrites_str,'\0');
            s_http_server_opts.url_rewrites = DataBufferPtr(&url_rewrites_str);
            break;
        }
        break;
    }
    case 13 :
    {

        if( 0 == strncmp(key,"document_root" ,idx )){
            GetContextIdx(key,idx,length,&document_root_str);
            DataBufferAppendChar (&document_root_str,'\0');
            s_http_server_opts.document_root = DataBufferPtr(&document_root_str);
            break;
        }
        if( 0 == strncmp(key,"dav_auth_file" ,idx )){
            GetContextIdx(key,idx,length,&dav_auth_file_str);
            DataBufferAppendChar (&dav_auth_file_str,'\0');
            s_http_server_opts.dav_auth_file = DataBufferPtr(&dav_auth_file_str);
            break;
        }
        break;
    }
    case 14 :
    {

        if( 0 == strncmp(key,"listening_port" ,idx )){
            GetContextIdx(key,idx,length,&listening_port_str);
            DataBufferAppendChar (&listening_port_str,'\0');
            s_http_port = DataBufferPtr(&listening_port_str);
            break;
        }
        break;
    }
    case 15 :
    {

        if( 0 == strncmp(key,"access_log_file" ,idx )){
            GetContextIdx(key,idx,length,&access_log_file_str);
            DataBufferAppendChar (&access_log_file_str,'\0');
            s_http_server_opts.access_log_file = DataBufferPtr(&access_log_file_str);
            break;
        }
        if( 0 == strncmp(key,"cgi_interpreter" ,idx )){
            GetContextIdx(key,idx,length,&cgi_interpreter_str);
            DataBufferAppendChar (&cgi_interpreter_str,'\0');
            s_http_server_opts.cgi_interpreter = DataBufferPtr(&cgi_interpreter_str);
            break;
        }
        break;
    }
    case 16 :
    {

        if( 0 == strncmp(key,"global_auth_file" ,idx )){
            GetContextIdx(key,idx,length,&global_auth_file_str);
            DataBufferAppendChar (&global_auth_file_str,'\0');
            s_http_server_opts.global_auth_file = DataBufferPtr(&global_auth_file_str);
            break;
        }
        if( 0 == strncmp(key,"cgi_file_pattern" ,idx )){
            GetContextIdx(key,idx,length,&cgi_file_pattern_str);
            DataBufferAppendChar (&cgi_file_pattern_str,'\0');
            s_http_server_opts.cgi_file_pattern = DataBufferPtr(&cgi_file_pattern_str);
            break;
        }
        break;
    }
    case 17 :
    {

        if( 0 == strncmp(key,"dav_document_root" ,idx )){
            GetContextIdx(key,idx,length,&dav_document_root_str);
            DataBufferAppendChar (&dav_document_root_str,'\0');
            s_http_server_opts.dav_document_root = DataBufferPtr(&dav_document_root_str);
            break;
        }
        if( 0 == strncmp(key,"custom_mime_types" ,idx )){
            GetContextIdx(key,idx,length,&custom_mime_types_str);
            DataBufferAppendChar (&custom_mime_types_str,'\0');
            s_http_server_opts.custom_mime_types = DataBufferPtr(&custom_mime_types_str);
            break;
        }
        break;
    }
    case 19 :
    {

        if( 0 == strncmp(key,"hidden_file_pattern" ,idx )){
            GetContextIdx(key,idx,length,&hidden_file_pattern_str);
            DataBufferAppendChar (&hidden_file_pattern_str,'\0');
            s_http_server_opts.hidden_file_pattern = DataBufferPtr(&hidden_file_pattern_str);
            break;
        }
        break;
    }
    case 23 :
    {

        if( 0 == strncmp(key,"per_directory_auth_file" ,idx )){
            GetContextIdx(key,idx,length,&per_directory_auth_file_str);
            DataBufferAppendChar (&per_directory_auth_file_str,'\0');
            s_http_server_opts.per_directory_auth_file = DataBufferPtr(&per_directory_auth_file_str);
            break;
        }
        break;
    }
    case 24 :
    {

        if( 0 == strncmp(key,"enable_directory_listing" ,idx )){
            GetContextIdx(key,idx,length,&enable_directory_listing_str);
            DataBufferAppendChar (&enable_directory_listing_str,'\0');
            s_http_server_opts.enable_directory_listing = DataBufferPtr(&enable_directory_listing_str);
            break;
        }
        break;
    }
    }

}

void ReadConfigureFile(char* filePath)
{


    FILE *file = NULL;
    file = fopen(filePath,"r");
    if(file!=NULL){
        char temp[1024];
        int end = 0;
        DataBuffer dataBuffer;
        DataBufferInitial(&dataBuffer);
        int i = 0;
        while( 0 == end ){
            int length = fread(temp,1,sizeof(temp),file);
            if(length<=0){
                end = 1;
                break;
            }
            DataBufferAppendChars (&dataBuffer,temp,length);
            const char* ptr =  DataBufferPtr (&dataBuffer);
            unsigned int size = DataBufferSize(&dataBuffer);
            int j = i;
            i = 0;
            for(;j<size;j++){
                if(ptr[j] == '\n'){
                    readConfLine (ptr + i ,j - i );
                    i = j + 1 ;
                }
            }
            DataBufferpopLength (&dataBuffer,i);
            i = j + 1;
        }
        unsigned int size = DataBufferSize(&dataBuffer);
        if(size>0){
            const char* ptr =  DataBufferPtr (&dataBuffer);
            readConfLine (ptr,size);
        }
        DataBufferDealloc(&dataBuffer);
        fclose(file);
    }
}

void globalInitial(){
    DataBufferInitial(&document_root_str );
    DataBufferInitial(&index_files_str );
    DataBufferInitial(&access_log_file_str );
    DataBufferInitial(&per_directory_auth_file_str );
    DataBufferInitial(&auth_domain_str );
    DataBufferInitial(&global_auth_file_str );
    DataBufferInitial(&enable_directory_listing_str );
    DataBufferInitial(&ssi_pattern_str );
    DataBufferInitial(&ip_acl_str );
    DataBufferInitial(&url_rewrites_str );
    DataBufferInitial(&dav_document_root_str );
    DataBufferInitial(&dav_auth_file_str );
    DataBufferInitial(&hidden_file_pattern_str );
    DataBufferInitial(&cgi_file_pattern_str );
    DataBufferInitial(&cgi_interpreter_str );
    DataBufferInitial(&custom_mime_types_str );
    DataBufferInitial(&listening_port_str );
}
void globalDealloc(){
    DataBufferDealloc(&document_root_str );
    DataBufferDealloc(&index_files_str );
    DataBufferDealloc(&access_log_file_str );
    DataBufferDealloc(&per_directory_auth_file_str );
    DataBufferDealloc(&auth_domain_str );
    DataBufferDealloc(&global_auth_file_str );
    DataBufferDealloc(&enable_directory_listing_str );
    DataBufferDealloc(&ssi_pattern_str );
    DataBufferDealloc(&ip_acl_str );
    DataBufferDealloc(&url_rewrites_str );
    DataBufferDealloc(&dav_document_root_str );
    DataBufferDealloc(&dav_auth_file_str );
    DataBufferDealloc(&hidden_file_pattern_str );
    DataBufferDealloc(&cgi_file_pattern_str );
    DataBufferDealloc(&cgi_interpreter_str );
    DataBufferDealloc(&custom_mime_types_str );
    DataBufferDealloc(&listening_port_str );
}

int main(int argc,char** argv) {

    // Set up HTTP server parameters
    s_http_server_opts.document_root = ".";  // Serve current directory
    s_http_server_opts.enable_directory_listing = "yes";

    globalInitial ();

    struct mg_mgr mgr;
    struct mg_connection *nc;
    if( argc >= 2 ){
        ReadConfigureFile(argv[1]);
    }

    printf("Starting web server on port %s\n", s_http_port);
    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    mg_set_protocol_http_websocket(nc);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    globalDealloc ();
    return 0;
}
