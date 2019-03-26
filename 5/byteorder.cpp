#include <stdio.h>
void byteorder()
{
	union
	{
		short value;
		char union_bytes[ sizeof( short ) ];
	} test;
	test.value = 0x0102;
	if (  ( test.union_bytes[ 0 ] == 1 ) && ( test.union_bytes[ 1 ] == 2 ) )
	{
		printf( "big endian\n" );
	}
	else if ( ( test.union_bytes[ 0 ] == 2 ) && ( test.union_bytes[ 1 ] == 1 ) )
	{
		printf( "little endian\n" );
	}
	else
	{
		printf( "unknown...\n" );
	}
}
#include<netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    byteorder();
    
    //网络字节序和主机字节序的转换
    union {
        short value;
        char union_bytes[sizeof(short)];
    } test;
    
    test.value = 0x0102; //二进制 100000010
    printf("host seq: %d,%d,%d\n", test.value,  test.union_bytes[ 0 ],  test.union_bytes[ 1 ]);
    test.value = htons(test.value);
    printf("net seq: %d,%d,%d\n", test.value,  test.union_bytes[ 0 ],  test.union_bytes[ 1 ]);
   
    //主机点分IP地址和网络uint地址的转换
    //主机->网络
    const char * host_str = "140.143.123.174";
    in_addr_t net_addr_t = inet_addr(host_str);
    printf("host_str:%s, net_str:%u\n", host_str, net_addr_t);
    //主机->网络
    struct in_addr net_addr;
    inet_aton(host_str, &net_addr);
    printf("host_str:%s, net_str:%u\n", host_str, net_addr.s_addr);
    //网络->主机
    char * p_host_str = inet_ntoa(net_addr);
    printf("host_str:%s, net_str:%u\n", p_host_str, net_addr.s_addr);
    
    //主机->网络
    uint32_t net_addr_tt = 0;
    inet_pton(AF_INET, host_str, &net_addr_tt);
    printf("host_str:%s, net_str:%u\n", host_str, net_addr_tt);

    inet_pton(AF_INET, host_str, &net_addr);
    printf("host_str:%s, net_str:%u\n", host_str, net_addr.s_addr);
    
    //网络->主机
    /*
     *#define INET_ADDRSTRLEN 16
      #define INET6_ADDRSTRLEN 46
     *
     *
     * */
    char host_addr[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &net_addr, host_addr, INET_ADDRSTRLEN);
    printf("host_str:%s, net_str:%u\n", host_addr, net_addr.s_addr);






    return 0;
}
