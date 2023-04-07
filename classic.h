void cls() {
  system("cls");
}

void reset(char *x) {
  memset(x, '\0', strlen(x));
}

void mreset(char *x, char *y) {
  reset(x);
  reset(y);
}

void unos(char *x, char *y) {
  printf("Unesite Email: ");
  scanf(" %s", x);
  system("cls");
  printf("Unesite Password: ");
  scanf(" %s", y);
  system("cls");
}
