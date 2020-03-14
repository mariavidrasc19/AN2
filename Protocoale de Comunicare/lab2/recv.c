#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){
  msg r;
  char buf[1];
  char name[1024];
  int marime_fisier;
  init(HOST,PORT);

  
  // se verifica primirea mesajului cu numele fisierului destinatie
  if (recv_message(&r)<0){
    perror("Ce-ai zis boss?");
    return -1;
  }
  printf("[recv] Vrei sa imi dai un fisier <%s>?\n", r.payload);
  sprintf(name, "%s", r.payload);

  // Send ACK / raspuns de la receptor
  sprintf(r.payload,"%s", "Mda bine da-mi-l.");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK sent\n");

  // se verifica primirea mesajului
  if (recv_message(&r)<0){
    perror("Ce-ai zis boss?");
    return -1;
  }
  printf("[recv] Deci tu vrei sa imi trimiti un fisier de <%d> octeti?\n", r.len);
  
  marime_fisier = r.len;
  
  // preluam fisierul
  int miner_destinatie = open(name, O_WRONLY, 0644);
  if (miner_destinatie < 0)
        perror("Nu pot deschide un fisier\n");

  // Send ACK / raspuns de la receptor
  sprintf(r.payload,"%s", "Na si un ACK");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK trimis\n");

  // se primeste textul byte cu byte
  while (marime_fisier > 0)
  {
    // se verifica primirea byte-ului
    if (recv_message(&r)<0){
      perror("Ce-ai zis boss?");
      return -1;
    } else {
      printf("[recv] Vezi ca am primit <%c>.\n", r.payload[0]);
    }

    sprintf(buf,"%s", r.payload);

    // se scrie in destinatie byte-ul primit
    int text_copiat = write(miner_destinatie, buf, sizeof(buf));
    if (text_copiat < 0) {
      perror("Nu s-a putut scrie in fisier");
      break;
    }

    // Send ACK / raspuns de la receptor
    sprintf(r.payload,"%s", "Na si un ACK");
    r.len = strlen(r.payload) + 1;
    send_message(&r);
    printf("[recv] ACK trimis\n");

    marime_fisier --;
  }
  

  return 0;
}
