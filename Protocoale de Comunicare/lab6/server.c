/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	int fd;

	// se verifica numarul de argumente
	// daca nu sunt toate se trateaza situatia
	if (argc!=3)
		usage(argv[0]);
	
	// se creaza un socket care incearca conexiunea cu internetul
	struct sockaddr_in from_station ;
	char buf[BUFLEN];

	/*Deschidere socket*/
	int socket_descriptor = socket(PF_INET, SOCK_DGRAM, 0);
	
	/*Setare struct sockaddr_in pentru a asculta pe portul respectiv */
	from_station.sin_family = AF_INET;
	from_station.sin_port = htons(atoi(argv[1]));
	from_station.sin_addr.s_addr = INADDR_ANY;
	
	/* Legare proprietati de socket */
	bind(socket_descriptor, (struct sockaddr*) &from_station, sizeof(struct sockaddr_in));
	
	/* Deschidere fisier pentru scriere */
	DIE((fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1,"open file");
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din socket
	*		pune in fisier
	*/
	socklen_t len;
	int buf_len;
	while ((buf_len = recvfrom(socket_descriptor, buf, BUFLEN, 0, (struct sockaddr*) &from_station, &len)) != -1) {
		write(fd, buf, buf_len);
		memset(buf, 0, BUFLEN);
	}

	/*Inchidere socket*/	
	close(socket_descriptor);
	
	/*Inchidere fisier*/
	close(fd);

	return 0;
}
