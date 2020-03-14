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

// functia ce intoarce paritatea textului
int xor(char buf[1024], int n) {
  int res = 0;
  for (int i = 0; i < n; i++) {
    char res_element = 0;
    for (int j = 0; j < 8; j++) {
      res_element ^= ((1<<j) & 1);
    }
    res ^= res_element;    
  }
  return res;
}

int main(int argc,char** argv){
  init(HOST,PORT);
    msg msg;
    pkt pkt;
    int open_sursa;
    int read_sursa;

    // se citeste din linia de comanda fisierul sursa
    open_sursa = open("sursa", O_RDONLY);

    for (int i = 0; i < 20; ++i) {
        // se citeste de la inceput textul
        lseek(open_sursa, 0, SEEK_SET);

        // se initializeaza mesajul
        memset(&msg, 0, sizeof(msg));
        read_sursa = read(open_sursa, pkt.payload, MAX_LEN);
      
        if (read_sursa < 0) {
            perror("Unable to read from input file\n");
        } else {
          // se obtine maritatea apeland functia xor si in mesaj introducem marimea textului
          msg.len = read_sursa;
          pkt.parity = xor(pkt.payload, msg.len);

          // se coiaza textul din sursa din pachet in mesaj
          memcpy(msg.payload, pkt.payload, MAX_LEN);

          // se trimite mesajul
          printf("[send] Sending payload: %s\n", msg.payload);
          send_message(&msg);

          // se printeaza ce s-a primit de la recv
          recv_message(&msg);
          printf("[send] Recieved response: %s\n", msg.payload);
        }
    }

    close(open_sursa);
    printf("Gata\n");

    return 0;
}
