#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
int main()
{
	const int SIZE = 48;
	const char *name = "OA";
	int fd;
	int *ptr;
	srand(time(NULL));
	fd = shm_open(name, O_CREAT | O_RDWR,0666);
	ftruncate(fd, SIZE);
	ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	int count = 0;
	while (*(ptr+11) != -1)
	{
		int temp = 10 + (rand() % 11);
		printf("Randomed value: %d\n", temp);
		if (count < 10) {
			*(ptr+count) = temp;
			count++;
			*(ptr+10) = count;
		}
		sleep(1);
	}
	munmap(ptr, SIZE);
	close(fd);
	return 0;
}
