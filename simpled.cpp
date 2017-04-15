/*oserveri.c - An iterative echo server 
 */ 
/* $begin echoserverimain */
//#include "csapp.h"

using namespace std;

extern "C" {
#include "csapp.h"
#include <arpa/inet.h>
}

#include <iostream>
#include <string>
#include <vector>

//void echo(int connfd);

void Set(vector< vector<string> > variables, string variableName, string value);
void Get(string variableName);
//void Digest();
//void Run();

int main(int argc, char **argv) 
{
    int listenfd, connfd, port;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    if (argc != 3) {
	fprintf(stderr, "usage: <port> <secret_key>\n");
	exit(0);
    }

    port = atoi(argv[1]);
    string secret_key = string(argv[2]);

    vector< vector<string> > variables;	

    listenfd = Open_listenfd(port);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	/* Determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			   sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
	printf("server connected to %s (%s)\n", hp->h_name, haddrp);

	//echo(connfd);
	size_t n;
    	char buf[MAXLINE];
    	rio_t rio;

    	Rio_readinitb(&rio, connfd);
	
	n = rio_readnb(&rio, buf, MAXLINE);

	

	//turn the first 4 bytes of the message into a string to compare
	// to the given secret key
	string key_check = "";
	for(int i = 0; i < 4; i++)
	{
		key_check += buf[i]; 
	}
	if(key_check != secret_key)
	{
		Close(connfd);
	}
	else
	{
		int app = buf[4];		

		if(app == 0)
		{
			string variableName = "";
			int pos = 8;
			while(buf[pos] != '\0')
			{
				variableName += buf[pos];
				pos++;
			}

			char valueLenStr [4];
			for(int j = 24; j < 28; j++)
			{
				valueLenStr[j] = buf[j];
			}			 
			int valueLen = atoi(valueLenStr);
			
			string value = "";
			for(int k = 28; k < (27+valueLen); k++)
			{
				value += buf[k];
			} 

			Set(variables, variableName, value);
		}
		else if(app == 1)
                {

                }
		else if(app == 2)
                {

                }
		else if(app == 3)
                {

                }
		else
                {
			
                }
	}
	//if(n != 0)
	//{
	//	
	//}
	
    	//while((n = Rio_readnb(&rio, buf, MAXLINE)) != 0) { //line:netp:echo:eof
        	//printf("server received %d bytes\n", (int)n);
		
        	//Rio_writen(connfd, buf, n);
    	//}

	//Close(connfd);
    }
    exit(0);
}

void Set(vector< vector<string> > variables, string variableName, string value)
{
	cout << "got here" << endl;		

	return;
}

void Get(vector< vector<string> > variables, string variableName)
{
	//stuff
	
	return;
}
/* $end echoserverimain */

//void echo(int connfd) 
//{
//    size_t n; 
//    char buf[MAXLINE]; 
//    rio_t rio;
//
//    Rio_readinitb(&rio, connfd);
//    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { //line:netp:echo:eof
//	printf("server received %d bytes\n", (int)n);
//	Rio_writen(connfd, buf, n);
//    }
//}
