using namespace std;

extern "C" {
#include "csapp.h"
#include <arpa/inet.h>
}

#include <iostream>
#include <string>
#include <vector>

//void echo(int connfd);

void Set(vector< vector<string> > &variables, string variableName, string value);
void Get(vector< vector<string> > variables, string variableName);
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
    vector<string> newVariable;
    newVariable.push_back("PATH");
    newVariable.push_back("/bin:/usr/bin");
    variables.push_back(newVariable);
    //newVariable.pop_back();
    //newVariable.pop_back();

    listenfd = Open_listenfd(port);

	//cout << "listened" << endl;

// we don't need the while loop because we only open one connection

    while (1) {
	
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	//cout << "accepted" << endl;

	/* Determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			   sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
	printf("server connected to %s (%s)\n", hp->h_name, haddrp);

	//echo(connfd);
	//size_t n;
    	char buf[MAXLINE];
    	rio_t rio;

    	Rio_readinitb(&rio, connfd);
	
	cout << "past rio init" << endl;

	Rio_readnb(&rio, buf, MAXLINE);

	cout << "past rio_read" << endl;

// for debugging purposes

	//for(int i = 0; i < 128; i ++)
	//	cout<<(int)buf[i]<<endl;

	//turn the first 4 bytes of the message into a string to compare
	// to the given secret key
	string key_check = "";
	//for(int i = 0; i < 4; i++)
	//{
// we need to treat the security key as a sequence of bytes, not characters

		unsigned int num = ((buf[0]<<24)&0xFF)+((buf[1]<<16)&0xFF)
			+((buf[2]<<8)&0xFF)+((buf[3])&0xFF);
		
		key_check += to_string(num); 
		//printf("%d",num);
	//}
	if(key_check != secret_key)
	{
		cout<<"error: invalid key"<<endl;
		Close(connfd);
	}
	else
	{
		int app = buf[4];		

//		cout<<buf[4]<<endl;

		if(app == '0')
		{
			string variableName = "";
			int pos = 8;
			while((int)buf[pos] != 0)
			{
				variableName += buf[pos];
				pos++;
			}
			cout<<"name: "<<variableName<<endl;

			char valueLenStr [4];
			//for(int j = 24; j < 28; j++)
			//{
			//	valueLenStr[j] = buf[j];
			//}

// again, all input numbers should be treated as bytes, not characters

						 
			int valueLen = ((buf[24]<<24)&0xFF)+((buf[25]<<16)&0xFF)
                        +((buf[26]<<8)&0xFF)+((buf[27])&0xFF);//atoi(valueLenStr);

			cout<<"length = "<<valueLen<<endl;

			string value = "";
			for(int k = 28; k < (28+valueLen); k++)
			{
				value += buf[k];
			} 

			cout<<"value: "<<value<<endl;

			Set(variables, variableName, value);
			
			char response[128];
			//char zero[1];
			char pad[] = {'p', 'a', 'd'};
			char zero[] = {0};
			char eof[2] = "\26";
			strcpy(response, zero);
			strcat(response, pad);
			for(int g = 0; g < 4; g++)
			{
				cout << "r: " <<  (int)response[g];
			}
			Rio_writen(connfd, response, 4);
			//Rio_writen(connfd, eof, strlen(eof));
			//Close(connfd);

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
      Close(connfd);

  }
    exit(0);
}

void Set(vector< vector<string> > &variables, string variableName, string value)
{
	//look if the variable already exists, and if so, update it
        bool found = false;
        for(int vari = 0; vari < variables.size(); vari++)
        {
                if(variables[vari][0] == variableName)
                {
                        variables[vari][1] = value;
			//cout << "in variables, value is:" << variables[vari][1] << endl;
                        found = true;
                }
        }

        //if it isn't found, add it to the list of variables
        if(found == false)
        {
                vector<string> insertVariable;
                insertVariable.push_back(variableName);
                insertVariable.push_back(value);
                variables.push_back(insertVariable);
        }

	return;
}

void Get(vector< vector<string> > variables, string variableName)
{
	//stuff
	
	return;
}
/* $end echoserverimain */
