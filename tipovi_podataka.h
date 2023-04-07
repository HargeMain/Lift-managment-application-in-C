typedef struct korisnik {
  char email[N];
  char password[N];
  char ime_lifta[N];
} korisnik;

typedef struct nosila {
  char ime[N];
  int br_sprat;
  int br_aktivacija;
  int br_koristenja;
  int status_servis;
  int status_block;
} nosila;

typedef struct korisnik_lift {
  korisnik user;
  nosila lift;
} korisnik_lift;