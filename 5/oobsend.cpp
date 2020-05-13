#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>      /* Declares errno and defines error constants */
int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );

    struct sockaddr_in server_address;
    bzero( &server_address, sizeof( server_address ) );
    server_address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &server_address.sin_addr );
    server_address.sin_port = htons( port );

    int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sockfd >= 0 );
    if ( connect( sockfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) < 0 )
    {
        printf( "connection failed:%d\n", errno );
    }
    else
    {
        char buffer[1024] = {0};
//#define BUF_SIZE 1024
//        int ret = recv(  sockfd, buffer, BUF_SIZE-1, 0 );
//        printf("recv:%d,\n%s\n", ret, buffer);
        printf( "send oob data out\n" );
        const char* oob_data = "abc";
        const char* normal_data = "/tmp/xx\r\n";
        send( sockfd, normal_data, strlen( normal_data ), 0 );
        //send( sockfd, oob_data, strlen( oob_data ), MSG_OOB );
        //send( sockfd, oob_data, strlen( oob_data ), MSG_OOB );
        //send( sockfd, oob_data, strlen( oob_data ), MSG_OOB );
        //send( sockfd, oob_data, strlen( oob_data ), MSG_OOB );
        //send( sockfd, normal_data, strlen( normal_data ), 0 );
#define BUF_SIZE 1024
        int idx = 0; 
        while(1) {
            int ret = recv(  sockfd, buffer+idx, BUF_SIZE-1-idx, 0 );
            if (ret == 0) {
                break;
            }
            printf("recv:%d,\n%s\n", ret, buffer+idx);
            idx  += ret;
        }
    }

    close( sockfd );
    return 0;
}
