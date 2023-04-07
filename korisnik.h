void activateLift(korisnik *glavni) {
    FILE *fp, *fp2;
    nosila lift;
    int foundl;
    int broj_lifts;
    int postoji = 0;

    printf("Unesite ime nosila koje zelite aktivirati: ");
    scanf("%s", lift.ime);
    fp = fopen("nosila1.dat", "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fseek(fp,0,SEEK_END);
    broj_lifts = ftell(fp)/sizeof(nosila);
    rewind(fp);
    foundl = 0;
    for(int i = 0; i < broj_lifts; i++) {
        fread(&lift, sizeof(nosila), 1, fp);
        if (strcmp(lift.ime, lift.ime) == 0) {
            if(lift.status_block==1){
                printf("Lift nije u funkciji\n");
                break;
            }
            foundl =1;
            break;
        }
    }
    if (!foundl) {
        printf("Nosilo s tim imenom nije pronađeno!\n");
        sleep(5);
        fclose(fp);
        return;
    }

    fp2 = fopen("korisnik.dat", "r+");
    if (fp2 == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    korisnik_lift k_lift;
    while(fread(&k_lift, sizeof(korisnik_lift), 1, fp2)){
        if(strcmp(k_lift.user.email,glavni->email)==0 && strcmp(k_lift.lift.ime,lift.ime)==0){
            postoji=1;
            break;
        }
    }
    if(postoji==1){
        printf("Nosilo %s već aktivirano za korisnika %s\n",lift.ime,glavni->email);
        sleep(5);
        return;
    }
    rewind(fp2);
    fseek(fp2, 0, SEEK_END);
    k_lift.user = *glavni;
    k_lift.lift = lift;
    fwrite(&k_lift, sizeof(korisnik_lift), 1, fp2);
    printf("Nosilo %s uspješno aktivirano za korisnika %s\n",lift.ime,glavni->email);
    sleep(5);

    fclose(fp);
    fclose(fp2);
}

void lift_aktivacija(korisnik glavni) {
FILE *fp, *fp2;
int foundx = 0;
korisnik user;
nosila lift;
char d;
int destinacija, trenutni_sprat;
fp = fopen("korisnik.dat", "rb");
if (fp == NULL) {
    printf("Error opening user file!\n");
    sleep(5);
    exit(1);
}


while (fread(&user, sizeof(korisnik), 1, fp)) {
    if (strcmp(user.email, glavni.email) == 0 && strcmp(user.password, glavni.password) == 0) {
      foundx = 1;
      break;
    }
}

if(!foundx) {
    printf("Ne postoji lift sa tim imenom u fajlu\n");
    sleep(5);
}
else {
    fp2 = fopen("nosila1.dat", "rb+");
    if (fp2 == NULL) {
        printf("Error opening lift file!\n");
        exit(1);
    }
    while (fread(&lift, sizeof(nosila), 1, fp2)) {
        if (strcmp(user.ime_lifta, lift.ime) == 0) {
            break;
        }
    }

    if (lift.status_servis == 1 && lift.status_block == 1) {
        printf("Lift je u servisnom stanju ili je blokiran!\n");
        sleep(5);
    }
    else {
        lift.br_koristenja++;
        if (lift.br_koristenja > lift.br_aktivacija) {
            lift.status_servis= 1;
            lift.status_block = 1;
            printf("Lift je prekoracen i blokiran i ostace takav sve dok se ne popravi!\n");
            sleep(2);
        }
        else {
            do{
                cls();
                printf("Pritisnite d pozovete lift...\n");
                scanf("%c",&d);
            }while(d!='d');
            do{
            cls();
            printf("Pritisni g za gore,d za dole\n");
            scanf("%c",&d);
            }while(d!='g' && d!='d');

            do{
                printf("%d\n", lift.br_sprat);
                printf("Unesite zeljeni sprat: ");
                scanf("%d",&destinacija);
                }while(destinacija>lift.br_sprat);
                if(d=='g'){
                    trenutni_sprat=0;

                    while (trenutni_sprat <= destinacija ) {
                     printf("|||\n");
                    printf("Sprat: %d\n", trenutni_sprat + 1);
                  trenutni_sprat++;
                   sleep(2);
}

                printf("\a");
                }else{
                trenutni_sprat=destinacija;
                destinacija=0;
                while(trenutni_sprat>destinacija){
                    printf("|||\n");
                    printf("Sprat:%d\n",trenutni_sprat-1);
                    trenutni_sprat--;
                    sleep(2);
                }
                 printf("\a");

                }

cls();
fseek(fp2, -sizeof(nosila), SEEK_CUR);
fwrite(&lift, sizeof(nosila), 1, fp2);
printf("Lift uspjesno aktiviran\n");
sleep(5);
}
}
fclose(fp2);
}
fclose(fp);
cls();
}

int check_user(char *email, char *password, korisnik *glavni) {
    FILE *fp = fopen("korisnik.dat", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    int found = 0;
    korisnik f_user;
    int n = 0;
    fseek(fp, 0, SEEK_END);
    int s = ftell(fp);
    rewind(fp);
    n = s / sizeof(korisnik);
    for (int i = 0; i < n; i++) {
        fread(&f_user, sizeof(korisnik), 1, fp);
        if (strcmp(email, f_user.email) == 0 && strcmp(password, f_user.password) == 0) {
            found = 1;
            strcpy(glavni->email,email);
            strcpy(glavni->password,password);
            break;
        }
    }
    fclose(fp);
    return found;
}
