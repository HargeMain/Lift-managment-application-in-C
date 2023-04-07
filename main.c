#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define N 50
#include "tipovi_podataka.h"
#include "classic.h"
#include "admin.h"
#include "korisnik.h"


void main() {
  int k;
  korisnik user;
  korisnik f_user;
  nosila lift;
  char ime_lift[N];
  korisnik glavni;
  korisnik admin=p_admin();
  while (1) {
    cls();
    printf("\033[41;93m");
    printf("*****DOBRODOSLI NA APLIKACIJU ZA KONTROLU LIFTA*****\n\n\n");
    printf("1.Log in\t2.Exit\n");
    scanf("%d", &k);
    if (k == 2) {
      break;
    } else if (k != 1) {
      printf("Pogresna opcija\nVrati se na pocetak\n");
      continue;
    }
    cls();
    unos(user.email, user.password);
    if (strcmp(user.email, admin.email) == 0 && strcmp(user.password, admin.password) == 0) {
      do {
        mreset(user.email, user.password);
        printf("***Admin***\n\nDobrodosli\n\nOdaberite 1 od 6 opcija\n\n");
        printf("1.Kreiranje novog korisnika\n2.Kreiranje novog nosila\n3.Trenutni broj koristenja nosila\n4.Nosila spremna za servisiranje\n5.Blokirana nosila\n6.Exit\n\n");
        scanf("%d", &k);
        cls();
        switch (k) {
          case 1:
           create_user(f_user);
            break;
          case 2:
            create_lift(lift);
            break;
          case 3:
              search_lift(ime_lift);
            break;
          case 4:
            ready_for_service();
            break;
          case 5:
        block_nosila();
            break;
          case 6:
            break;
          default:
            printf("Unos nepostojece opcije\nPokusajte ponovo\n");
            sleep(5);
            cls();
        }
      } while (k != 6);
    } else {
        int found = check_user(user.email, user.password,&glavni);
      if (found) {
        do {
          printf("***Korisnik***\n\nDobrodosli\n\nOdaberite 1 od 3 opcija\n\n");
          printf("1.Aktiviranje nosila\n2.Paljenje\n3.Exit\n\n");
          scanf("%d", &k);
          cls();
          switch (k) {
case 1:
    activateLift(&glavni);

break;
case 2:
lift_aktivacija(glavni);
break;
case 3:
break;


}
        }while (k != 3);
      }else {
        printf("Pogresni podaci\nPokusajte ponovo\n");
        sleep(5);
        cls();
      }
    }
  }
}
