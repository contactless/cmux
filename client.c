
/* tty over tcp client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

extern char* program_invocation_short_name;

void usage()
{
	fprintf(stderr, "usage: %s <address>\n", program_invocation_short_name);
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		usage();
		errx(EXIT_FAILURE, "invalid argc");
	}


	struct sockaddr_in saddr;
	memset(& saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family = PF_INET;

	if (!inet_aton(argv[1], &saddr.sin_addr)) {
		if (errno == EINVAL) {
			warnx("invalid address argument: %s", argv[1]);
			usage();
		}
		err(EXIT_FAILURE, "inet_aton() failed");
	}

	saddr.sin_port = htons(65535);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		err(EXIT_FAILURE, "socket() failed");

	
	if (connect(sock, (struct sockaddr*) (& saddr), sizeof(struct sockaddr_in)) == -1)
		err(EXIT_FAILURE, "connect() failed");

	const int SIZE_BUF = 128;
	char buf[SIZE_BUF];
	
	while (fgets(buf, sizeof(buf), stdin)) {
		buf[strlen(buf)-1] = '\r';
		if (send(sock, buf, strlen(buf)+1, 0) == -1)
			warn("send() failed");
		if (recv(sock, buf, sizeof(buf), 0) == -1)
			warn("recv() failed");
		puts(buf);
	}

	return 0;	
}
