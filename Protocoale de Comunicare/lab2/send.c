#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000


int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;
  char buf[1];
  char text[1024];
  int size = 0;
  int copiere;
  int miner_sursa;

  //se trimite numele fisierului destinatie
  printf("[send] Hai ca-ti dau ceva misto.\n");

  sprintf(t.payload,"%s", "destinatie");

  // dimensiunea lui payload
  t.len = strlen(t.payload)+1;

  // se trimite primul mesaj
  send_message(&t);

  // se verifica raspunsul
  if (recv_message(&t)<0){
    perror("Mai esti pe acolo?");
    send_message(&t);
  }

  // se deschide fisierul sursa pt o analiza a marimiii sale
  miner_sursa = open("sursa", O_RDONLY, 0644);
  if (miner_sursa < 0) {
    perror("Nu s-a putut deschide fisierul");
  }

  // dimensiunea fisierului in curs de trimitere
  // masuram byte cu byte dimensiunea fisierului
    copiere = read(miner_sursa, text, sizeof(text));
    if (copiere < 0) {
      perror("Nu se poate citi fisierul");
    }
  for (int i = 0; i < 1024; i++)
  {
   if (text[i] == '\0') {
     break;
   }
    size ++;
  }
  t.len = size;

  // se trimite  dimensiunea si se verifica primirea
  send_message(&t);
  if (recv_message(&t)<0){
    perror("Receive error ...");
    send_message(&t);
  }
  else {
    printf("[send] Hai cu placere.");
  }

  // se pointeaza miner_sursa spre inceputul textului
  lseek(miner_sursa, 0, SEEK_SET);
  
  // se trimite textul din sursa byte cu byte
  while (size > 0) {
    // se verifica citirea corecta intr-un buffer de dimensiune 1 byte
    copiere = read(miner_sursa, buf, sizeof(buf));
    if (copiere < 0) {
      perror("Nu se poate citi fisierul.\n");
      break;
    }
    // se copiaza in payload si se trimite
    sprintf(t.payload,"%s", buf);
    send_message(&t);

    // verificare trimitere byte
    if (recv_message(&t)<0){
      perror("Receive error ...");
      return -1;
    }
    else {
      printf("[send] Asa imi raspunzi tu mie?  Auzi la el: '%s'\n", t.payload);
    }

    // se decrementeaza lungimea textului care a mai ramas de trimis
    size --;
  }
  printf("IA BAGA UN OCHI PE FISIERUL DESTINATIE\n");

  return 0;
}
