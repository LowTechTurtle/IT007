#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <sys/time.h>

int main(int argc, char* argv[]) 
{
	if (argc != 2) {
		printf("chon mot command muon thuc hien\n");
		printf("Cach dung: ./measure_time \"<command> <argument> <argument>\"\n");	
		exit(0);
	}

	struct timeval tval_before, tval_after, tval_result;

	gettimeofday(&tval_before, NULL);
	system(argv[1]);
	gettimeofday(&tval_after, NULL);

	timersub(&tval_after, &tval_before, &tval_result);

	printf("Thoi gian thuc hien: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
	return 0;
}
