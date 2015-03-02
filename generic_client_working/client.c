#include "client.h"
/*-------------Function Prototypes--------------------*/
void recv_data(int);
int write_command();
int convert(char * );
int download_file(int);
int display_list();
/*-------------Main Function--------------------------*/
int main(int argc, char**argv)
{
	
	int sock_fd, newfd, flag = 0;
	struct sockaddr_in server;
        struct stat obj;
//	printf("%d----\n",argc);
	if(argc<3)
	{
		switch(argc)
		{
			case 1:
				printf("USAGE:<./exe><PORT><IP ADDRESS>\n");
				exit(1);
				break;
			case 2:
				printf("USAGE:<./exe><PORT><IP ADDRESS>\n");
				exit(1);
				break;
		}
	}
	if((control_fd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		perror("socket");
		exit(1);
	}
	else printf("Socket created\n"); 
	//printf("%d\n",control_fd);
	server.sin_family = AF_INET;
	//printf("AF_INET\n");
        server.sin_port = htons(atoi(argv[1]));
	//printf("Port number\n");
        server.sin_addr.s_addr = inet_addr(argv[2]) ;
	//printf("IP address\n");
	int c = connect(control_fd, (struct sockaddr*)&server, sizeof(server));
	if(c<0)
	{
		perror("connect");
		exit(1);
	}
	else if(c==0)
	{
		__fpurge(stdout);
		printf("Connected\n");
	}
	while(1)
	{
	//	printf("Enter a command\n");
		/*if(!flag)
		{
			write_command();
			flag = 0;
		}*/
		
		//write_command();
		recv_data(control_fd);
		printf("%s",down_read);
		rcvd_val = atoi(down_read);
		switch(rcvd_val)
		{
			case 220:
				printf("Name:(%s kesavaraju):",argv[2]);
				write_command();
				//__fpurge(stdin);
				printf("%s",down_read);
				//flag++;
				break;
				
			case 331:	
				//printf("%s\n",down_read);
				printf("Password:");
				__fpurge(stdin);
				//printf("%s",down_read);
				//flag++;
				write_command();
				//flag++;
				break;
			case 230:
				//printf("%d",port);
				__fpurge(stdin);
				write_command();
				//flag++;
				break;
			case 221:
				__fpurge(stdin);
				printf("Bye.. Bye.. quiting..!!\n");
				exit(0);
				break;
				
			case 227:
				if(convert_port(down_read))
				{
					printf("Could not convetr port number\n");
					break;
				}
				struct sockaddr_in serv1;
				if((data_fd=socket(AF_INET,SOCK_STREAM,0))<0)
				perror("socket");
				serv1.sin_family=AF_INET;
				serv1.sin_port=htons(port);
				serv1.sin_addr.s_addr=inet_addr(argv[2]);
				if((newfd=(connect(data_fd,(struct sockaddr*)&serv1,sizeof(server)))<0))		
				perror("connect");
				//__fpurge(stdin);
				printf("data connection established\n");
				write_command();
				break;
			case 150:
         			 if(strstr(down_read,"BINARY"))
                                {	
                                  	//printf("Download case\n");
					char* stream = malloc(100);
					int bytes;
					strcpy(stream, down_read);
					while(*(stream)!='(')
					{	
						//printf("%s\n",stream);
						stream++;
					}
						stream++;
					bytes = atoi(stream);
					printf("%d\n",bytes);
					__fpurge(stdout);
					printf("stream\n");
					//strcpy(stream,down_read);
					    download_file(bytes);
			
				}
                                /*      write_command();
                                        break;
                                }*/
                                else if(strstr(down_read,"list"))
                                {
				//	__fpurge(stdout);
					//nt temp_i;
                                        display_list();
					//printf("returned from function with %d\n",temp_i);
					
                                        //write_command();
				}
                                //      exit(0);

				break;
			case 226:
			//	printf("Closing Data Connection\n");
				__fpurge(stdout);
				write_command();
				break;
			case 257:
			//	printf("Path name created\n");
				__fpurge(stdout);
				write_command();
				break;
			case 550:
			//	printf("Failed to change the directory\n");	
				__fpurge(stdout);
				write_command();
				break;
			case 250:
			//	printf("Succesfully changed the directory\n");
				__fpurge(stdout);
				write_command();
				break;
			case 421:
				__fpurge(stdout);
				exit(1);
				break;
			case 425:
			//	printf("Using passive mode");
				__fpurge(stdout);
				write_command();
				break;
			case 500:
				//printf("Unknown command\n");
				__fpurge(stdout);
				write_command();
				break;
			case 530:
				//printf("\n");
				printf("password incorrect:\n");
				//write_command();
				exit(0);
				break;
			/*default:
				write_command();
				recv_data(control_fd);
				break;	*/			
				
		}	
	}
	return 0;
}
