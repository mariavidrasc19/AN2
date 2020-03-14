#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

// functia ce intoarce paritatea textului
int xor(char buf[1024], int n) {
  int res = 1;
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
    msg r_msg;
    pkt r_pkt;
    int bit_corect = 0;

    for (int i = 0; i < 20; ++i) {
        // se seteaza mesajul de primire un buffer de 0-uri
        memset(r_msg.payload, 0, MAX_LEN);
        
        // se primeste mesajul si se transcrie pe mesaj
        if (recv_message(&r_msg) < 0) {
            perror("Unable to recieve message");
            return -1;
        }

        // de asemenea se citeste mesajul in pachet pentru a avea dimensiunea textului 
        // dimensiunea lui r_pkt.payload.len
        memcpy(r_pkt.payload, r_msg.payload, MAX_LEN);

        // se printeaza mesajul primit
        printf("[recv] Got msg with payload: %s\n", r_pkt.payload);

        // se appeleaza functia xor pt a obtine paritatea corecta
        bit_corect = xor(r_pkt.payload, strlen(r_pkt.payload));

        // se reumple mesajul cu 0-uri
        memset(r_msg.payload, 0, MAX_LEN);
        
        // se verifica daca paritatea primita e corecta pt a verifica corectitudinea mesajului
        if (r_pkt.parity != bit_corect) {
            printf("[recv] Error detected\n");
            sprintf(r_msg.payload, "NACK");

        } else {
            printf("[recv] Message is correct\n");
            sprintf(r_msg.payload, "ACK");
        }

        // se trimite ACK de verificare al mesajului primit 
        send_message(&r_msg);
    }

    return 0;
}

