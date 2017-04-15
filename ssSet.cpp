/*
 * echoclient.c - An echo client
 */
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

    sprintf(keyStr,"%d",key);

    strcpy(request, keyStr);

    strcat(request, type);

    strcat(request,pad);

    strcpy(Var, varName.c_str());

    strcat(request,Var);

    char size[3];

    sprintf(size,"%d",(int)value.size());

    strcat(request,size);

    strcpy(val,value.c_str());

    strcat(request,val);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    char eof[2] = "\26";

//    while (Fgets(buf, MAXLINE, stdin) != NULL) {
//	Fgets(buf, MAXLINE, stdin);
	Rio_writen(clientfd, request, strlen(request));
	Rio_writen(clientfd, eof, strlen(eof));
	Rio_readnb(&rio, buf, strlen(buf));
//	Rio_readn(0, buf, MAXLINE);
	Fputs(buf, stdout);
    //}
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
/* $end echoclientmain */
