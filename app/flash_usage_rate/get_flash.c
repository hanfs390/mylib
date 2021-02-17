#include <stdio.h>                                                                                                                  
#include <stdlib.h>
#include <unistd.h>
#include <sys/vfs.h>

int main()
{
	struct statfs diskInfo;

	/* get / flash */
	statfs("/", &diskInfo);  /* get rootfs flash info */
	unsigned long long totalBlocks = diskInfo.f_bsize;
	unsigned long long totalSize = totalBlocks * diskInfo.f_blocks;
	size_t mbTotalsize = totalSize>>20;  
	unsigned long long freeDisk = diskInfo.f_bfree*totalBlocks;  
	size_t mbFreedisk = freeDisk>>20;
	printf ("/  total=%dMB, free=%dMB\n", mbTotalsize, mbFreedisk);  

	/* get /boot flash */
	statfs("/boot", &diskInfo);  
	totalBlocks = diskInfo.f_bsize;  
	totalSize = totalBlocks * diskInfo.f_blocks;  
	mbTotalsize = totalSize>>20;  
	freeDisk = diskInfo.f_bfree*totalBlocks;  
	mbFreedisk = freeDisk>>20;  
	printf ("/boot  total=%dMB, free=%dMB\n", mbTotalsize, mbFreedisk);
	
	/* get /dev/shm flash */
	statfs("/dev/shm", &diskInfo);
	totalBlocks = diskInfo.f_bsize;
	totalSize = totalBlocks * diskInfo.f_blocks;
	mbTotalsize = totalSize>>20;
	freeDisk = diskInfo.f_bfree*totalBlocks;
	mbFreedisk = freeDisk>>20;
	printf ("/dev/shm  total=%dMB, free=%dMB\n", mbTotalsize, mbFreedisk);
}
