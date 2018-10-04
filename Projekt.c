#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"spis.h"

int liczba_kandydatow = 0; 	//poczatkowa liczba kandydatow - pamietac o zwiekszaniu przy dodawaniu
int liczba_okregow = 0; 	//poczatkowa liczba okregow wyborczych

int main(){
	int wybor, i, identyfikator;
	okr okreg[OKREGI_L];
	kand kandydat[KANDYDACI_L];

	wczytaj_kandydatow(okreg, kandydat);

	while(1){
		printf("KANDYDACI I OKREGI WYBORCZE\n\n");
        printf("1   Wyswietl liste\n");
        printf("2   Modyfikuj liste\n");
        printf("3   Sortuj liste kandydatow\n");
        printf("4   Wyjscie\n");

		wybor = wczytaj_liczbe("\nPolecenie: ");

        if(wybor == 1){
            while(1){
                printf("\nWyswietl liste:\n");
                printf("1   kandydatow\n");
                printf("2   okregow wyborczych\n");
                printf("3   wyjscie\n");
                wybor = wczytaj_liczbe("\n[Wyswietl liste] Polecenie: ");

                if(wybor == 1)
                    wyswietl_kandydatow(kandydat, liczba_kandydatow);
                else if(wybor == 2)
                    wyswietl_okregi(okreg, liczba_okregow);
                else if(wybor == 3)
                    break;
                else
                    printf("\nBLAD: nie zdefiniowano dzialania dla %d.\n", wybor);
            }
        }
		else if(wybor == 2){
            while(1){
                printf("\nModyfikuj liste:\n");
                printf("1   kandydatow\n");
                printf("2   okregow wyborczych\n");
                printf("3   wyjscie\n");
                wybor = wczytaj_liczbe("\n[Modyfikuj liste] Polecenie: ");

                if(wybor == 1){
                    while(1){
                        printf("\nModyfikuj liste kandydatow:\n");
                        printf("1   usun\n");
                        printf("2   dodaj\n");
                        printf("3   zmien\n");
                        printf("4   wyjscie\n");
                        wybor = wczytaj_liczbe("\n[Modyfikuj liste kandydatow] Polecenie: ");

                        if(wybor == 1){ // i jest pozycja kandydata na liscie kandydatow
							printf("UWAGA: Wczytywanych jest tylko 6 pierwszych liczb.\n");
                            identyfikator = wczytaj_liczbe("\nPodaj identyfikator kandydata: ");
                            if((i = sprawdz_identyfikator(kandydat, identyfikator)) == -1)
                                printf("\nBLAD: nie ma kandydata o podanym identyfikatorze\n");
                            else
							usun_kandydata(kandydat, &i, okreg);
                        }
                        else if(wybor == 2){
                            dodaj_kandydata(kandydat, okreg);
                            wyswietl_kandydatow(&kandydat[liczba_kandydatow - 1], 1);
                        }
                        else if(wybor == 3){
                            identyfikator = wczytaj_liczbe("\nPodaj identyfikator kandydata, ktorego chcesz zmodyfikowac: ");
                            if((i = sprawdz_identyfikator(kandydat, identyfikator)) == -1)
                                printf("\nBLAD: nie ma kandydata o podanym identyfikatorze\n");
                            else
                                zmien_kandydata(&kandydat[i], okreg);
                        }
                        else if(wybor == 4)
                            break;
                    }
                }
                else if(wybor == 2){
                    while(1){
                        printf("\nModyfikuj liste okregow wyborczych:\n");
                        printf("1   usun\n");
                        printf("2   dodaj\n");
                        printf("3   zmien\n");
                        printf("4   wyjscie\n");
                        wybor = wczytaj_liczbe("\n[Modyfikuj liste okregow wyborczych] Polecenie: ");

                        if(wybor == 1){
                            usun_okreg(okreg, kandydat);
                        }
                        else if(wybor == 2){
                            dodaj_okreg(kandydat, okreg);
                            printf("\nDodano nowy okreg: %s\n", (okreg+liczba_okregow - 1)->nazwa);
                        }
                        else if(wybor == 3){
                            zmien_okreg(okreg);
                        }
                        else if(wybor == 4)
                            break;
                    }
                }
                else if(wybor == 3)
                    break;
                else
                    printf("\nBLAD: nie zdefiniowano dzialania dla %d.\n", wybor);
            }
		}

	else if(wybor == 3){
          	qsort(kandydat, liczba_kandydatow, sizeof(kand), porownanie);
            	printf("Lista kandydatow zostala posortowana alfabetycznie wedlug naswisk kandydatow.\n\n");
	}
        else if(wybor == 4)
			break;
	else
		printf("\nBLAD: nie zdefiniowano dzialania dla %d.\n\n", wybor);

	}

	zapisz(okreg);

	return 0;
}
