#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int fd = 0;
	int c;
	char buf[BUFSIZ];
	int fileout_flag = 0;
	int fileout_fd = 1;

	opterr = 0;

	while ((c = getopt(argc, argv, "S:o:h")) != -1)
		switch (c) {
		case 'h':
			fprintf(stdout,
				"fake-xterm -o file [arguments to xterm, must include -S]\n");
			return 0;
		case 'S':
			fd = atoi(&optarg[2]);
			break;
		case 'o':
			if (fileout_flag)
				continue;
			fileout_flag = 1;
			fileout_fd =
			    open(optarg, O_CREAT | O_RDWR | O_TRUNC,
				 S_IRUSR | S_IWUSR);
			if (fileout_fd == -1) {
				perror("open file");
				return 1;
			}
			break;
		case '?':
			break;
		default:
			abort();
		}

	if (fd <= 0) {
		fprintf(stderr, "fake-xterm: Must specifiy -S\n");
		return 1;
	}

	if (write(fd, "0000000\n\r", 9) == -1) {
		perror("writeback");
		return 1;
	}

	while ((c = read(fd, buf, sizeof(buf)))) {
		if (c == -1) {
			perror("xread");
			return 1;
		}

		if (write(fileout_fd, buf, c) == -1) {
			perror("log write");
			return 1;
		}

	}

	close(fileout_fd);
	close(fd);

	exit(0);

}