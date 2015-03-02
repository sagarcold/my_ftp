#include"client.h"
void recv_data(int fd)
{
	bzero(down_read,10000);
	recv(fd,down_read,10000,0);
//	printf("%s\n",down_read);
	return ;
}


/*int  download_file()
{
        char buf[1];
        FILE *fp;
        fp=fopen(file,"w");

	while(1)
     	{
		bzero(buf,1);
		n= recv(control_fd,buf,1,0);
		if(n)
		fwrite(buf,1,1,fp);
                fclose(fp);
	}
	return n;
}*/
int download_file(int bytes)
{
        int buffersize = 0, file_fd,recv_size = 0,size = bytes, read_size, write_size;
        char imagearray[bytes],verify = '1';
        FILE *image;
 	if(size <= 0 )
        {
                printf("Error has occurred. Size less than or equal to 0\n");
                return -1;
        }
        image = fopen(file, "wb");
        if( image == NULL)
        {
                printf("Error has occurred. Image file could not be opened\n");
                return -1;
        }
        printf("%d\n",size);
        while(recv_size<size)
        {
                ioctl(data_fd, FIONREAD, &buffersize);
                if(buffersize > 0 )
                {
                        if(!(read_size = read(data_fd,imagearray, buffersize)))
                        {
                                printf("%s", strerror(errno));
                                 return 1;
                        }
                        else
                        {
                                if(buffersize!=0)
                                write_size = fwrite(imagearray,1,(buffersize), image);
                        }

                if(write_size != buffersize)
                {
                        printf("write and buffersizes wrong\n");
                }
                if(read_size !=write_size)
                {
                        printf("error in read write\n");
                }
                buffersize = buffersize-read_size;
                recv_size +=read_size;
                }
	
        }
	if(recv_size == bytes)
	printf("Received the file of size:%d bytes\n",recv_size);
        else
	printf("Received only %d bytes",bytes-recv_size);                
        return 1;
}


int display_list()
{
	int val,actual;
	bzero(down_read,1448);
	ioctl(data_fd,FIONREAD,&actual);
	//printf("%d\n",actual);
	while(val = recv(data_fd,down_read,1448,0)>0)
	{
		//if(actual == 0)
		//break;
		/*if(val<0)
	{
		
		perror("recv");
		return 0;
	}*/
	//printf("Received..%dbytes of data\n",val);
		printf("%s",down_read);
	//	ioctl(data_fd,FIONREAD,&actual);
		//printf("I am here\n");
	//printf("%d\n",actual);
		bzero(down_read,1448);
	}
	bzero(command,30);
	strcpy(command,"ABOR\r\n");
	if(write(data_fd,command,strlen(command))<0)
	{
		perror("write");
		exit(0);
	}
	printf("wrote:%s\n",command);
	bzero(command,30);
	__fpurge(stdout);
	close(data_fd);
	printf("Data connection closed\n");
	//write_command();
	return val;
}
int write_command()
{

	int i=0,j=0,cnt=0,cnt2=0;
	char user[10]="USER ";
	char pass[10]="PASS ";
	char buf[100];
	char temp_file[100];
	static int cnt1;
	char*temp = "\0";
	if(cnt1>1)
	{
		printf("\nftp>");
		gets(command);
		while(!strcmp(command,temp))
		{
			printf("\nftp>");
			gets(command);
		}
	}
	else if(cnt1<=1)
	{
		bzero(command,30);
		gets(command);
	}
	//if(strcmp(command,'\0'))
	//printf("\nftp>");
	//while((strcmp(buf,"\n"))==0)
	//{
	//	printf("...\n");
	//	printf("\nftp>");
	//	gets(buf);
	//}
	//strcpy(command,buf);
	switch(cnt1)
	{	
		case 0:
			memcpy(command+5,command,strlen(command));
			memcpy(command,user,5);
			printf("%s\n",command);
			//*command = '\0';
			break;
		case 1:
			
			//bzero(command,30);
			memcpy(command+5,command,strlen(command));
			memcpy(command,pass,5);
			printf("%s\n",command);
			break;
	}
	if(strstr(command,"retr"))
	{
		printf("Retreiving.....\n");
		while(command[i]!='\0')
		{i++;
			
		//printf("%c\n",command[i]);
		}
		//i++;
		//cnt2++;
		//printf("%s\n",command+i);
		for(j=0;(command[i])!='/';i--)
		{
			file[j++]=command[i];
			//printf("%c",file[j]);
		}
			file[j]='\0';
			i = 0;
			j--;
		while(j>=0)
		{
			temp_file[i++] = file[j];
			j--;
		}
		temp_file[i]= '\0';
		strcpy(file,temp_file);
		printf("file name:%s\n",file);
	}
	strcat(command,"\r\n");
	//printf("%s\n",command);
	//memset(command,0,sizeof(command));
	write(control_fd,command,strlen(command));
	cnt1++;
	//printf("%s\n",command);
	return 0;
}

int convert_port(char* buf)
{
	//printf("%s\n",buf);
	unsigned int i,t=0;
	int flag=0,decCtr=0,tport1,tport2;
	char tmpPort[6];
	for(i=0;i<strlen(buf);i++)
	{
		if(buf[i]=='(')
		{ 
			flag = 1;i++;
		}
		if(buf[i]==')')
		{ 
			hostname[t]='\0';
			break;
		}
		if(flag==1)
		{
			if(buf[i] != ',')
			{ 
				hostname[t]=buf[i];t++;
			}
        		else
			{  
				hostname[t]='.';t++;
			}
		}
	}
	t=0;
	decCtr=0;
	for(i=0;i<strlen(hostname);i++)
	{ 
		if(hostname[i]=='.')
		decCtr++;
		if(decCtr==4 && hostname[i]!='.')
		{
			tmpPort[t]=hostname[i];
			t++;
		}
		if(hostname[i+1]=='.')
		{ 
			tmpPort[t]='\0';
			tport1=atoi(tmpPort);
			t=0;
		}
		if(decCtr==5 && hostname[i]!='.')
		{
			tmpPort[t]=hostname[i];
			t++;
			if(hostname[i+1]=='\0')
                	{
				tmpPort[t]='\0';
				tport2=atoi(tmpPort);
				t=0;
                 	}
		}	
	}
	port = tport1 * 256 + tport2;
	decCtr=0;
	for(i=0;i<strlen(hostname);i++)
	{
		if(hostname[i]=='.')
		{
			decCtr++;
		}
		if(decCtr>3)
		hostname[i]='\0';
	}
	return 0;
}
