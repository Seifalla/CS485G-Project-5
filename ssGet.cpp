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
    char *host, buf[MAXLINE];
    rio_t rio;
    char request[128];

    if (argc != 5) {
	fprintf(stderr, "usage: %s <host> <port> <secret key> <variable name>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

// check if numeric and in-range
    key = atoi(argv[3]);
    //pad = argv[5];
    varName = argv[4];

    if(varName.size() > 15){
	fprintf(stderr,"error: variable names should be at most 15 characters long");
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
		index = i;
		break;
	}

    strcat(request,Var);


    for(int i = index; i < (24-index); i ++)

    	request[8+i] = '\0';

    for(int i = 0; i < 24; i ++)
	cout<<(int)request[i]<<' '<<request[i]<<endl;

    //cout<<"int = "<<(int)request[7+index+1]<<endl;

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    char eof[2] = "\26";

	Rio_writen(clientfd, request, 24);
	Rio_writen(clientfd, eof, strlen(eof));
	Rio_readnb(&rio, buf, MAXLINE);
//	Rio_readn(0, buf, MAXLINE);

	if(buf[0] == -1){

		cout<<"failure"<<endl;
		exit(1);
	}
	else if(buf[0] == 0){

		unsigned int length = ((buf[4]<<24)&0xFF)+((buf[5]<<16)&0xFF)
                        +((buf[6]<<8)&0xFF)+((buf[7])&0xFF);

		ntohl(length);
		cout<<"length :"<<length<<endl;
		for(int i = 8; i < 8+length; i ++)
			cout<<buf[i];
		cout<<endl;
	}
	else 
		cout<<"invalid response"<<endl;
	//Fputs(buf, stdout);
    //}
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
/* $end echoclientmain */
