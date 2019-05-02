#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define CHECK(func) \
	do {			\
		int ret = func;   \
		if(ret < 0){	 \
			fprintf(stderr, "ERR: %d",__LINE__); \
			return -1;   \
		}\
	}while(0);

char *link_file;
char *org_file;

int print_Usage(char *argv){
	printf("prog %s: use opt below\n",argv);
	printf("%s -f <link file name>\n",argv);
	printf("%s -l <link file>\n",argv);
	printf("%s -h to get help\n",argv);
	return -1;
}
int parse_data(int argc, char **argv){
	char op;
	while ((op = getopt(argc,argv,"hf:l:")) != -1){
		switch(op){
			case 'f': org_file = optarg;
				break;
			case 'l': link_file = optarg;
				break;
			case 'h':
			default:
				print_Usage(argv[1]);
				break;
		}

	}

}
int main(int argc, char **argv){
	int fd;
	char buf[16];
	if(argc < 3){
		fprintf(stderr,"running the application format is \
wrong\n");
		print_Usage(*(argv));
		return -1;
	}
	parse_data(argc,argv);
	sprintf(buf,"rm %s",link_file);
        system(buf);

	fd = open(org_file, O_CREAT | O_RDWR, 0666);
	CHECK(fd);
	CHECK(link(org_file,link_file));
	printf("link successful\n");
	close(fd);
	return 0;
}
