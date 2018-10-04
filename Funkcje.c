#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"spis.h"

extern int liczba_kandydatow;
extern int liczba_okregow;

//wczytuje jeden wyraz(pierwszy), dlugosc wczytywanego wyrazu jest ograniczona
char *wczytaj(char *wyraz, int ile){
	char * wynik;
	char * koniec;

	wynik = fgets(wyraz, ile, stdin);
	if(wyraz != NULL){
		koniec = strchr(wyraz, '\n');
		if(koniec != NULL)
			*koniec = '\0';
		else
			while(getchar() != '\n');
	}

	if(wyraz != NULL){
		koniec = strchr(wyraz, ' ');
		if(koniec != NULL)
			*koniec = '\0';
	}
	return wynik;
}

//wczytuje liczbe dodatnia wyswietlajac jednoczesnie tekst (maksymalna wczytywana liczba - szesciocyfrowa)
int wczytaj_liczbe(char tekst[]){               
    	char liczba[ID_DL+1];
    	int i;
    	int wynik = 0, pozycja = 1;
    	printf("%s", tekst);
        wczytaj(liczba, ID_DL+1);

	for(i = 0 ; i < strlen(liczba) ; i++)
		pozycja *= 10;

	for(i = 0 ; i < strlen(liczba) ; i++){
        	if((liczba[i] - '\0') >= 0 && (liczba[i] - '0') <=9)
          	 	wynik += (liczba[i] - '0')*(pozycja/= 10);
        	else
            		return -1;
	}
	return wynik;
}

//sprawdza, czy kandydat o podanym identyfikatorze znajduje sie na liscie
int sprawdz_identyfikator(kand* kandydat, int identyfikator){
	int i;
	for(i = 0 ; i < liczba_kandydatow ; i++){
		if(identyfikator == kandydat[i].identyfikator)
		break;
	}
	if(i == liczba_kandydatow)
		return -1;      				//zwraca -1, jesli na liscie nie ma kandydata o zadanym identyfikatorze
	return i;       					//zwraca pozycje kandydata na liscie, jesli kandydat na niej jest
}

//drukuje wyraz, dobiera odpowiednia liczbe odstepow (zalezna od n i dlugosci wyrazu)
void wydrukuj(char wyraz[], int n){ 
	int i;
	printf("%s", wyraz);
	for(i = 0 ; i < (n-strlen(wyraz)) ; i++)
		printf(" ");
}

//wyswietla liste kandydatow, ktorej dlugosc wynosi liczba_kandydatow
void wyswietl_kandydatow(kand* kandydat, int liczba_kandydatow){        
	int i;
	wydrukuj("\nIMIE", IMIE_DL + 1);			//+1, bo jeden znak dochodzi na przejscie do nowego wiersza
	wydrukuj("NAZWISKO", NAZWISKO_DL);
	wydrukuj("PLEC", PLEC_SZ);
	wydrukuj("PARTIA", PARTIA_DL);
	wydrukuj("IDENTYFIKATOR", ID_SZ);
	printf("\n");
	for(i = 0 ; i < liczba_kandydatow ; i++){
		wydrukuj(kandydat->imie, IMIE_DL);
		wydrukuj(kandydat->nazwisko, NAZWISKO_DL);
		printf("%c         ", kandydat->plec);
		wydrukuj(kandydat->partia, PARTIA_DL);
		printf("%d\n", kandydat->identyfikator);
		kandydat++;
	}
}

//wyswietla liste okregow wraz z zapisanymi do nich kandydatami
void wyswietl_okregi(okr* okreg, int liczba_okregow){  
	int i, j;
	wydrukuj("\nNAZWA OKREGU", OKREG_DL + 1);		//+1, bo jeden znak dochodzi na przejscie do nowego wiersza
	wydrukuj("IMIE", IMIE_DL);
	wydrukuj("NAZWISKO", NAZWISKO_DL);
	wydrukuj("PLEC", PLEC_SZ);
	wydrukuj("PARTIA", PARTIA_DL);
	wydrukuj("IDENTYFIKATOR", ID_SZ);
	for(i = 0 ; i < liczba_okregow ; i++){
		printf("\n");
		wydrukuj(okreg->nazwa, OKREG_DL);
		for(j = 0 ; j < okreg->liczba ; j++){
			printf("\n");
			wydrukuj("", OKREG_DL);
			wydrukuj(okreg->kandydat[j]->imie, IMIE_DL);
			wydrukuj(okreg->kandydat[j]->nazwisko, NAZWISKO_DL);
			printf("%c         ", okreg->kandydat[j]->plec);
			wydrukuj(okreg->kandydat[j]->partia, PARTIA_DL);
			printf("%d", okreg->kandydat[j]->identyfikator);
		}
		okreg++;
	}
	printf("\n");
}

//usuwa kandydata i wykresla go z listy okregow
void usun_kandydata(kand* kandydat, int *pozycja, okr* okreg){
	int i, j;
	for(i = 0 ; i < liczba_okregow ; i++){
		for(j = 0 ; j < okreg->liczba ; j++){
			if(okreg->kandydat[j]->identyfikator == kandydat[(*pozycja)].identyfikator){
				(okreg->kandydat[j]) = (okreg->kandydat[--(okreg->liczba)]);
				i = liczba_okregow;
				break;
			}
		}
			okreg++;
	}

	kandydat[*pozycja] = kandydat[--liczba_kandydatow];

	printf("\nkandydat zostal usuniety\n");
}

//dodaje kandydata (identyfikator nie jest wybierany przez uzytkownika)
void dodaj_kandydata(kand* kandydat, okr*okreg){
	int  i, max, wybor;
	char plec[2];

	if(liczba_kandydatow == KANDYDACI_O*liczba_okregow){
        printf("\nBLAD: nie mozna dodac nowego kandydata z powodu zbyt malej liczby okregow\n");
        return;
	}

	max_id(kandydat, &max);
	kandydat += liczba_kandydatow;
	kandydat->identyfikator = max+1;

	while(1){						//wczytuje imie - do skutku
		printf("\nPodaj imie kandydata: ");
		if(wczytaj(kandydat->imie, IMIE_DL) != NULL && kandydat->imie[0] != '\0')
			break;
        printf("\nBLAD: nie podano imienia kandydata\n");
	}
	while(1){
		printf("\nPodaj nazwisko kandydata: ");
		if(wczytaj(kandydat->nazwisko, NAZWISKO_DL) != NULL && kandydat->nazwisko[0] !='\0')
			break;
		printf("\nBLAD: nie podano nazwiska kandydata\n");
	}
	while(1){
        printf("\nPodaj plec kandydata: ");
        if(wczytaj(plec, 2) != NULL && (plec[0] == 'k' || plec[0] == 'm')){
            kandydat->plec = plec[0];
            break;
        }
        printf("\nBLAD: podana plec nie zostala okreslona - wybierz m lub k\n");
	}
	while(1){
		printf("\nPodaj partie, do ktorej nalezy kandydat: ");
		if(wczytaj(kandydat->partia, PARTIA_DL) != NULL && kandydat->partia[0] != '\0')
			break;
		printf("\nBLAD: nie podano nazwy partii (nazwa partii nie moze znaczynac sie spacji)\n");
	}

    	for(i = 0 ; i < liczba_okregow ; i++)              	//wyswietlanie listy nazw okregow - konieczne do ponizszego wyboru
        	printf("%d. %s\n", i+1 , (okreg+i)->nazwa);

	while(1){
        wybor = wczytaj_liczbe("\nWybierz, do ktorego z powyzszych okregow kandydat ma zostac przydzielony: ");
        if(wybor > 0 && wybor <= liczba_okregow){
            if(KANDYDACI_O - ((okreg+wybor-1)->liczba) > 0){
                (okreg+wybor-1)->kandydat[((okreg+wybor-1)->liczba)++] = kandydat;
                break;
            }
            else
                printf("Do okregu przypisana jest juz maksymalna liczba kandydatow. Wybierz inny okreg.\n");
        }
        else
            printf("\nBLAD: wybierz jeden z podanych numerow reprezentujacy okrag\n");
    }

	++liczba_kandydatow;
}

//znajduje najwiekszy identyfikator na liscie kandydatow
void max_id(kand* kandydat, int *max){
	int i;
	*max = kandydat->identyfikator;
    for(i = 0 ; i < liczba_kandydatow-1 ; i++){
		kandydat++;
		if((kandydat->identyfikator) > *max)
			*max = kandydat->identyfikator;
	}
}

//pozwala modyfikowac danego kandydata
void zmien_kandydata(kand* kandydat, okr* okreg){
	int liczba;
	char plec[2];

	liczba = wczytaj_liczbe("\nCzy zmienic imie kandydata? [1 - tak   inna liczba - nie]\nWYBOR: ");
	if(liczba == 1){
		while(1){
			printf("\nPodaj imie kandydata: ");
			if(wczytaj(kandydat->imie, IMIE_DL) != NULL && kandydat->imie[0] != '\0')
				break;

			printf("\nBLAD: nie podano imienia kandydata\n");
		}
	}
	liczba = wczytaj_liczbe("\nCzy zmienic nazwisko kandydata? [1 - tak   inna liczba - nie]\nWYBOR: ");
	if(liczba == 1){
		while(1){
			printf("\nPodaj nazwisko kandydata: ");
			if(wczytaj(kandydat->nazwisko, NAZWISKO_DL) != NULL && kandydat->nazwisko[0])
				break;

			printf("\nBLAD: nie podano nazwiska kandydata\n");
		}
	}
	liczba = wczytaj_liczbe("\nCzy zmienic plec kandydata? [1 - tak   inna liczba - nie]\nWYBOR: ");
	if(liczba == 1){
		while(1){
			printf("\nPodaj plec kandydata: ");
			if(wczytaj(plec, 2) != NULL && (plec[0] == 'k' || plec[0] == 'm')){
                kandydat->plec = plec[0];
                break;
            }

			printf("\nBLAD: podana plec nie zostala okreslona - wybierz m lub k\n");
		}
	}
	liczba = wczytaj_liczbe("\nCzy zmienic partie, do ktorej nalezy kandydat? [1 - tak   inna liczba - nie]\nWYBOR: ");
	if(liczba == 1){
		while(1){
			printf("\nPodaj partie, do ktorej nalezy kandydat: ");
			if(wczytaj(kandydat->partia, PARTIA_DL) != NULL && kandydat->partia[0] != '\0')
				break;

			printf("\nBLAD: nie podano nazwy partii (nazwa partii nie moze znaczynac sie spacji)\n");
		}
	}
}

//usuwa okreg, przenosi kandydatow do innych okregow
void usun_okreg(okr* okreg, kand * kandydat){
    int wybor, i, zmiana;

    printf("\n");
    if(liczba_kandydatow > KANDYDACI_O*(liczba_okregow - 1)){
        printf("\nBLAD: nie mozna usunac zadnego okregu z powodu zbyt duzej liczby kandydatow\n");
        return;
    }

    for(i = 0 ; i < liczba_okregow ; i++)
        printf("%d. %s\n", i+1, (okreg+i)->nazwa);

    while(1){
        wybor = wczytaj_liczbe("\nPodaj numer okregu, ktory chcesz usunac: ");
        if(wybor > 0 && wybor <= liczba_okregow){
            wyswietl_okregi((okreg+wybor-1), 1);
            printf("\nWpisz numer okregu, do ktorego chcesz przeniesc danego kandydata\n");

            for(i = 0 ; i < (okreg+wybor-1)->liczba ; i++){
                printf("\nKandydat %d: %s %s\n", i+1, (okreg+wybor-1)->kandydat[i]->imie, (okreg+wybor-1)->kandydat[i]->nazwisko);
                if((zmiana = wczytaj_liczbe("Numer okregu: ")) == wybor){
                    printf("\nBLAD: wybrano okrag %d przeznaczony do usuniecia\n", zmiana);
                    i--;
                }
                else{
                    if(zmiana > 0 && zmiana <= liczba_okregow){
                        if((okreg+zmiana-1)->liczba < KANDYDACI_O)
                            ((okreg+zmiana-1)->kandydat[(okreg+zmiana-1)->liczba++]) = ((okreg+wybor-1)->kandydat[i]);
                        else{
                            printf("W okregu %d nie mozna umiescic juz wiecej kandydatow\n", zmiana);
                            i--;
                        }
                    }
                    else{
                        printf("\nBLAD: wybierz jeden z podanych numerow reprezentujacy okrag\n");
                        i--;
                    }
                }
            }

            okreg[wybor-1] = okreg[--liczba_okregow];
            break;
        }
        else
            printf("\nBLAD: wybierz jeden z podanych numerow reprezentujacy okrag\n");
    }
}

//porownuje dwie wartosci, funkcja potrzebna do sortowania listy kandydatow
int porownanie(const void *kandydat1, const void *kandydat2){
	kand _kandydat1 = *(kand*)kandydat1;
	kand _kandydat2 = *(kand*)kandydat2;

    if(strcmp(_kandydat1.nazwisko, _kandydat2.nazwisko) < 0)
        return -1;
    else if(strcmp(_kandydat1.nazwisko, _kandydat2.nazwisko) == 0)
        return 0;
    return 1;
}

//dodaje okreg
void dodaj_okreg(kand* kandydat, okr*okreg){
    if(liczba_okregow == OKREGI_L){
        printf("\nBLAD: maksymalna liczba okregow zostala juz osiagnieta\n");
        return;
    }
    while(1){
        printf("\nPodaj nazwe nowego okregu: ");
        if(wczytaj((okreg+liczba_okregow)->nazwa, OKREG_DL) != NULL && (okreg+liczba_okregow)->nazwa[0] != '\0'){
            (okreg+liczba_okregow++)->liczba = 0;
            break;
        }
        printf("\nBLAD: nie podano nazwy okregu (nazwa okregu nie moze znaczynac sie spacji)\n\n");
    }
}

//pozwala modyfkowac okreg
void zmien_okreg(okr* okreg){
    int wybor1, wybor2, i, identyfikator;

    while(1){
        wybor1 = wczytaj_liczbe("\nCzy zmienic nazwe okregu? [1 - tak    inna liczba - nie\nWYBOR: ");
        if(wybor1 == 1){
            printf("\n");
            for(i = 0 ; i < liczba_okregow ; i++)
                printf("%d. %s\n", i+1, (okreg+i)->nazwa);

            wybor2 = wczytaj_liczbe("\nPodaj numer okregu, ktorego nazwe chcesz zmienic.\nWYBOR: ");

            if(wybor2 > 0 && wybor2 <= liczba_okregow){
                printf("\nPodaj nazwe okregu: ");
                if(wczytaj((okreg+wybor2-1)->nazwa, OKREG_DL) == NULL && (okreg+wybor2-1)->nazwa[0] != '\0')
                    printf("\nBLAD: nie podano nazwy okregu\n");
            }
            else
                printf("BLAD: nie ma okregu o podanym numerze\n");
        }
        else
            break;
    }

    while(1){
        wybor1 = wczytaj_liczbe("\nCzy przeniesc kandydata do innego okregu? [1 - tak    inna liczba - nie\nWYBOR: ");
        if(wybor1 == 1){
            printf("\n");
            for(i = 0 ; i < liczba_okregow ; i++)
                printf("%d. %s\n", i+1, (okreg+i)->nazwa);

            wybor1 = wczytaj_liczbe("\nPodaj numer okregu z ktorego chcesz przeniesc kandydata: ");
            wyswietl_okregi(okreg+wybor1-1, 1);
            identyfikator = wczytaj_liczbe("\nPodaj identyfikator kandydata nalezacego do okregu o wybranej liczbie: ");
            for(i = 0 ; i < (okreg+wybor1-1)->liczba ; i++){
                if((okreg+wybor1-1)->kandydat[i]->identyfikator == identyfikator){
                    wybor2 = wczytaj_liczbe("\nPodaj numer okregu do ktorego chcesz przeniesc kandydata: ");
                    if(wybor2 == wybor1){
                        printf("\nBLAD: wybrano okreg, z ktorego kandydat ma zostac wypisany");
                        i--;
                    }
                    else if(wybor2 > 0 && wybor2 <= liczba_okregow){
                        if((okreg+wybor2-1)->liczba == KANDYDACI_O){
                            printf("\nBLAD: do danego okregu nie mozna przypisac juz wiecej kandydatow");
                            i--;
                        }
                        else{
                            (okreg+wybor2-1)->kandydat[(okreg+wybor2-1)->liczba++] = (okreg+wybor1-1)->kandydat[i];
                            (okreg+wybor1-1)->kandydat[i] = (okreg+wybor1-1)->kandydat[((okreg+wybor1-1)->liczba)-1];
                            (okreg+wybor1-1)->liczba--;
                            break;
                        }
                    }
                    else{
                        printf("\nBLAD: okreg o podanym numerze nie istnieje\n");
                        i--;
                    }
                }
                if( i == ((okreg+wybor1-1)->liczba - 1))
                    printf("\nBLAD: w okregu %d nie ma kandydata o identyfikatorze %d\n", wybor1, identyfikator);
            }
        }
        else
            break;
    }
}

//wczytuje dane z pliku i na ich podstawie tworzy liste okregow i kandydatow
void wczytaj_kandydatow(okr *okreg, kand *kandydat){
	FILE *we;
	char wyraz[IMIE_DL];
	char znak;
	int linia = 0;

    	if((we=fopen("testy.txt", "r"))==NULL)
		printf("Nie wczytano zadnych danych. Lista okregow oraz lista kandydatow sa puste.\n");

	else{
		while(fscanf(we,"%s", wyraz) == 1){
			linia++;
			znak = getc(we);

			if(znak == '\n'){
				if(liczba_okregow < OKREGI_L)
					strcpy((okreg+liczba_okregow++)->nazwa, wyraz);
			}
			else if(liczba_okregow != 0 && liczba_kandydatow < KANDYDACI_L && (okreg+liczba_okregow-1)->liczba < KANDYDACI_O){
				strcpy((kandydat+liczba_kandydatow)->imie, wyraz);
				fscanf(we,"%s %c", (kandydat+liczba_kandydatow)->nazwisko, &(kandydat+liczba_kandydatow)->plec);
				fscanf(we,"%s %d", (kandydat+liczba_kandydatow)->partia, &(kandydat+liczba_kandydatow)->identyfikator);
				(okreg+liczba_okregow-1)->kandydat[((okreg+liczba_okregow-1)->liczba)++] = (kandydat+liczba_kandydatow);
				liczba_kandydatow++;
			}
			else{
				linia++;
				printf("\nBLAD: blad w lini %d wczytywanego pliku. Linia zostala pominieta.\n", linia);
			}
		}
		fclose(we);
	}
}

//zapisuje zmodyfikowane dane do pliku
int zapisz(okr *okreg){
	FILE *wy;
	int i, j;

	if ((wy=fopen("testy.txt", "w")) == NULL){
        	printf("Blad przy otwieraniu pliku\n");
        	return 1;
	}

	for(i = 0 ; i < liczba_okregow ; i++){
		fprintf(wy, "%s\n", okreg->nazwa);
		for(j = 0 ; j < okreg->liczba ; j++){
        		fprintf(wy,"%s ",okreg->kandydat[j]->imie);
        		fprintf(wy,"%s ",okreg->kandydat[j]->nazwisko);
        		fprintf(wy,"%c ",okreg->kandydat[j]->plec);
        		fprintf(wy,"%s ",okreg->kandydat[j]->partia);
        		fprintf(wy,"%d\n",okreg->kandydat[j]->identyfikator);
		}
		okreg++;
	}

	fclose(wy);
	return 0;
}
