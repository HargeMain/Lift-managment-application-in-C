korisnik p_admin() {
    korisnik admin;
    FILE *fpx = fopen("admin.dat", "r");
    if (fpx == NULL) {
        printf("Error opening admin data file\n");
        exit(1);
    }
    fread(&admin, sizeof(korisnik), 1, fpx);
    fclose(fpx);
    return admin;
}
void create_user(korisnik f_user){
    FILE *fp;
    printf("Unesite email adresu novog korisnika: ");
    scanf("%s", f_user.email);
    printf("Unesite password novog korisnika: ");
    scanf("%s", f_user.password);
    fp = fopen("korisnik.dat", "a");
    if (fp == NULL) {
      printf("Error opening file!\n");
      exit(1);
    }
    fwrite(&f_user, sizeof(korisnik), 1, fp);
    fclose(fp);
    printf("Novi korisnik uspjesno kreiran!\n");
    cls();
}

void create_lift(nosila lift){
    int k;
    FILE *fp;
    printf("Unesite ime novog nosila: ");
    scanf("%s", lift.ime);
    printf("Unesite broj spratova za koje je nosilo namijenjeno: ");
    scanf("%d", &lift.br_sprat);
    printf("Unesite broj aktivacija nosila prije servisiranja: ");
    scanf("%d", &lift.br_aktivacija);
    lift.br_koristenja =0;
    lift.status_servis=0;
    lift.status_block=0;
    printf("Da li zelite da sacuvate ovaj lift?\n1.DA\n2.NE\n");
      scanf("%d",&k);
    if(k==1){
        fp = fopen("nosila1.dat", "a");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }

        fwrite(&lift, sizeof(nosila), 1, fp);
        fclose(fp);
    }
    printf("Novo nosilo uspjesno kreirano!\n");
    sleep(2);
    cls();
}

void search_lift(char *ime_lift){
    int k;
    nosila lift;
    int m=0;
    do{
        printf("Unesite ime lifta: ");
        scanf("%s", ime_lift);
        FILE *fp = fopen("nosila1.dat", "r");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
       for(int i=0; fread(&lift, sizeof(nosila), 1, fp); i++){
            if (strcmp(lift.ime, ime_lift) == 0) {
                printf("Ime nosila: %s\n", lift.ime);
                printf("Broj spratova: %d\n",lift.br_sprat);
                printf("Broj koristenja lifta je: %d\n",lift.br_koristenja);
                m = 1;
                break;
            }
        }
         if (m == 0) {
        printf("Lift sa imenom '%s' ne postoji u datoteci.\n", ime_lift);
    }
    fclose(fp);
    printf("Unesite 0 za nazad,ako zelite ponovo da pretrazite unesite bilo koji drugi broj\n");
    scanf("%d",&k);
    if(k!=0){
        cls();
    }
    }while(k!=0);
    cls();
}


void ready_for_service() {
    int k;
    int broj_sb = 0;
    int broj_resetovani = 0;
    nosila lift;
    do {
        FILE *fp = fopen("nosila1.dat", "r+");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        printf("Nosila spremna za servisiranje:\n");
        while (fread(&lift, sizeof(nosila), 1, fp)) {
            if (lift.status_servis == 1) {
                printf("Ime nosila: %s\n", lift.ime);
                broj_sb++;
            }
        }
        fclose(fp);
        if (broj_sb == 0) printf("Nema nosila koja su spremna za servis!\n");
        else {
            printf("Ukupno %d nosila spremno za servis\n\n", broj_sb);
            printf("Unesite 0 da resetujete nosila spremna za servis\n");
            scanf("%d", &k);
            if (k == 0) {
                FILE *fp = fopen("nosila1.dat", "r+");
                if (fp == NULL) {
                    printf("Error opening file!\n");
                    exit(1);
                }
                while (fread(&lift, sizeof(nosila), 1, fp)) {
                    if (lift.status_servis == 1) {
                        lift.status_servis = 0;
                        fseek(fp, -sizeof(nosila), SEEK_CUR);
                        fwrite(&lift, sizeof(nosila), 1, fp);
                        broj_resetovani++;
                    }
                }

                if(broj_resetovani>0) printf("Resetovano %d liftova\n", broj_resetovani);

                  while (fread(&lift, sizeof(nosila), 1, fp)) {
                   if (lift.status_servis == 0 && lift.status_block==0) {
                   lift.br_koristenja = 0;
                   fseek(fp, -sizeof(nosila), SEEK_CUR);
 fwrite(&lift, sizeof(nosila), 1, fp);
}
}
fclose(fp);
}
 }
    printf("Unesite 0 za nazad\n");
    scanf("%d", &k);

    if (k != 0) {
        cls();
    }
} while (k != 0);
cls();
}


void block_nosila() {
    int k;
    int broj_sb = 0;
    int broj_resetovani = 0;
    nosila lift;
    do {
        FILE *fp = fopen("nosila1.dat", "r+");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        printf("Nosila spremna za servisiranje:\n");
        while (fread(&lift, sizeof(nosila), 1, fp)) {
            if (lift.status_block == 1) {
                printf("Ime nosila: %s\n", lift.ime);
                broj_sb++;
            }
        }
        fclose(fp);
        if (broj_sb == 0) printf("Nema nosila koja su blokirana!\n");
        else {
            printf("Ukupno %d nosila koja su blokirana\n\n", broj_sb);
            printf("Unesite 0 da resetujete nosila koja su na servisu\n");
            scanf("%d", &k);
            if (k == 0) {
                FILE *fp = fopen("nosila1.dat", "r+");
                if (fp == NULL) {
                    printf("Error opening file!\n");
                    exit(1);
                }
                while (fread(&lift, sizeof(nosila), 1, fp)) {
                    if (lift.status_block == 1) {
                        lift.status_block = 0;
                        fseek(fp, -sizeof(nosila), SEEK_CUR);
                        fwrite(&lift, sizeof(nosila), 1, fp);
                        broj_resetovani++;
                    }
                }

                if(broj_resetovani>0) printf("Odblokirano je  %d liftova\n", broj_resetovani);

while (fread(&lift, sizeof(nosila), 1, fp)) {
if (lift.status_block == 0 && lift.status_servis==0) {
lift.br_koristenja = 0;
fseek(fp, -sizeof(nosila), SEEK_CUR);
fwrite(&lift, sizeof(nosila), 1, fp);
}
}
fclose(fp);
}
 }
    printf("Unesite 0 za nazad\n");
    scanf("%d", &k);

    if (k != 0) {
        cls();
    }
} while (k != 0);
cls();
}


