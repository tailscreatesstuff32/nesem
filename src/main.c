#include "fce.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static char rom[1048576];

void do_exit() // normal exit at SIGINT
{
	kill(getpid(), SIGKILL);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: nesem romfile.nes\n");
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Failed while opening ROM.\n");
		exit(1);
	}

	int nread = fread(rom, sizeof(rom), 1, fp);
	if(nread == 0 && ferror(fp)) {
		fprintf(stderr, "Failed while reading ROM.\n");
		exit(1);
	}

	if (fce_load_rom(rom) != 0) {
		fprintf(stderr, "Invalid or unsupported ROM.\n");
		exit(1);
	}
	signal(SIGINT, do_exit);
	fce_init();
	fce_run();
	return 0;
}
