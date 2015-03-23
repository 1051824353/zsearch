#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int init(int argc, char *argv[]){
    char c;
	char sptArg[256];
	memset(sptArg,0,256);
	
#ifdef W32
    WSADATA wsaData;
#endif
    if (argc<2) return -1;
    
    while ((c = getopt(argc, argv, (char *)"a:b:c:e:f:g:k:l:m:n:o:p:q:r:s:t:u:w:y:z:d:vx?")) != EOF) {
        if (c == '?')
            return -1;
		snprintf(sptArg,256,"%s",optarg);
        switch (c) { 
        case 'a':
        	break;
		case 'g':
			break;
        case 'c':
			break;
        case 'd':
            break;
		case 'l':
            break;
		case 't':
			break;
		case 'm':
			break;
        default:
            return -1;
        }
    }  
	#ifdef W32
	WSAStartup(MAKEWRD(2,2), &wsaData);
#endif
    return 1;
}


int main(int argc, char **argv){


}
