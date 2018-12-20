#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <inttypes.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int usage() {
    printf("usage: sizeread <infile> <outfile>\n");
    return 1;
}

int main(int argc, char *argv[])
{
    int sfd, dfd, res;
    int64_t size;
    unsigned char *src, *dest;

    if (argc < 3)
        return usage();

    const char *srcfile = argv[1];
    const char *dstfile = argv[2];

    sfd = open(srcfile, O_RDONLY);
    if (sfd == -1)
        err(1, "%s", srcfile);

    res = read(sfd, &size, sizeof(size));
    if (res == -1)
        err(1, "%s", srcfile);

    src = mmap(NULL, size+sizeof(size), PROT_READ, MAP_PRIVATE, sfd, 0);
    if (src == MAP_FAILED)
        err(1, "%s mmap", srcfile);

    dfd = open(dstfile, O_RDWR | O_CREAT, 0666);
    if (!dfd)
        err(1, "%s", dstfile);

    res = ftruncate(dfd, size);
    if (res == -1)
        err(1, "%s", dstfile);

    dest = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
    if (dest == MAP_FAILED)
        err(1, "%s mmap", dstfile);

    fprintf(stderr, "reading %"PRId64" bytes from %s\n", size, srcfile);

    memcpy(dest, src+sizeof(size), size);

    munmap(src, size);
    munmap(dest, size);

    close(sfd);
    close(dfd);
    return 0;
}
