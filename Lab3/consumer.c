#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
int main()
{
	const int SIZE = 48;
	const char *name = "OA";
	int fd;
	int *ptr;
	fd = shm_open(name, O_RDWR,0666);
	ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	int sum = 0;
	while (*(ptr+10) < 10) {
		for (int i = 0; i < *(ptr+10); i++) {
			sum += *(ptr+i);
		}
		printf("sum is %d\n", sum);
		if (sum > 100) {
			*(ptr+11) = -1;
			break;
		}
		if (*(ptr+10) == 10) {
			*(ptr+11) = -1;
			break;
		}
		sum = 0;
		sleep(1);
	}
	sleep(2);
	munmap(ptr, SIZE);
	close(fd);
	shm_unlink(name);
	return 0;
}
