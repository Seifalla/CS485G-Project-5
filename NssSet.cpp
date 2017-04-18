
/* $begin echoclientmain */
//#include "csapp.h"

extern "C" {
#include "csapp.h"
}
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) 
{
    int clientfd, port;
    unsigned int key;
    char type[2] = "0";
    char pad[4] = "pad";
    string varName;
    unsigned int length;
    string value;
    char *host, buf[MAXLINE];
    rio_t rio;
    char request[128];

    if (argc != 6) {
	fprintf(stderr, "usage: %s <host> <port> <secret key> <variable name> <value>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

// check if numeric and in-range
    key = atoi(argv[3]);
    //pad = argv[5];
    varName = argv[4];
    value = argv[5];

    if(varName.size() > 15){
	fprintf(stderr,"error: variable names should be at most 15 characters long");
	exit(1);
    }
    if(value.size() > 100){
        fprintf(stderr,"error: values should be at most 100 characters long");
        exit(1);
    }

// debug

    char keyStr[20];

    char Var[15];

    char val[100];

    //key = htonl(key);

//    sprintf(keyStr,"%d",key);

    keyStr[0] = (key >> 24) & 0xFF;

    keyStr[1] = (key >> 16) & 0xFF;

    keyStr[2] = (key >> 8) & 0xFF;

    keyStr[3] = (key) & 0xFF;

    keyStr[4] = '\0';

    for(int i = 0; i < 4; i ++)
	if(keyStr[i] == '\0')
               keyStr[i] = '0';

    strcpy(request, keyStr);

    strcat(request, type);

    strcat(request,pad);

    strcpy(Var, varName.c_str());

    int index;

    for(int i = 0; i < 15; i++)

	if(Var[i] == '\0'){
//		cout<<i<<endl;
		index = i;
		break;
	}

    strcat(request,Var);

    char size[4];

    //sprintf(size,"%d",(int)value.size());

    //strcat(request,size);

    for(int i = index; i < (24-index); i ++)

    	request[8+i] = '\0';

    //cout<<"int = "<<(int)request[7+index+1]<<endl;

    size[0] = ((int)value.size() >> 24) & 0xFF;
    size[1] = ((int)value.size() >> 16) & 0xFF;
    size[2] = ((int)value.size() >> 8) & 0xFF;
    size[3] = ((int)value.size()) & 0xFF;

    for(int i = 0; i < 3; i ++)
	if(size[i] == '\0')
		size[i] = '0';

    for(int i = 24; i < 28; i++){

	request[i] = size[i-24];
    }
    //cout<<"int = "<<(int)request[7+index+1]<<endl;
    strcpy(val,value.c_str());

    //strcat(request,val);

    //cout<<"size = "<<(int)value.size()<<endl;

    for(int i = 28; i <  28+value.size(); i ++){

		request[i] = val[i-28];
    }

    //printf("%s",request);

//    for(int i = 0; i < 128; i ++)
//	cout<<(int)request[i]<<' '<<request[i]<<endl;

    //cout<<"int = "<<(int)request[7+index+1]<<endl;

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    char eof[2] = "\26";

//    while (Fgets(buf, MAXLINE, stdin) != NULL) {
//	Fgets(buf, MAXLINE, stdin);
	Rio_writen(clientfd, request, 128);
	Rio_writen(clientfd, eof, strlen(eof));
	Rio_readnb(&rio, buf, 0);
//	Rio_readn(0, buf, MAXLINE);
	Fputs(buf, stdout);
    //}
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
/* $end echoclientmain */
