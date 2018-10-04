#define IMIE_DL 21 			//maksymalna dlugosc imienia powiekszona o 1
#define NAZWISKO_DL 21 			//maksymalna dlugosc nazwiska powiekszona o 1
#define PARTIA_DL 21 			//maksymalna dlugosc nazwy partii powiekszona o 1
#define OKREG_DL 21 			//maksymalna dlugosc nazwy okregu powiekszona o 1
#define OKREGI_L 20 			//maksymalna liczba okregow
#define KANDYDACI_O 10 			//maksymalna liczba kandydatow w okregu
#define KANDYDACI_L 100 		//maksymalna ilosc kandydatow ogolem
#define ID_SZ 15 			//szerokosc pola przy wyswietlaniu identyfikatora
#define ID_DL 6				//dlugosc identyfikatora
#define PLEC_SZ 10 			//szerokosc pola przy wyswietlaniu plci
#define IDENTYFIKATOR_STALA 100000	//stala uzywana przy tworzeniu identyfikatora

typedef struct{
	char imie[IMIE_DL];
	char nazwisko[NAZWISKO_DL];
	char plec;
	char partia[PARTIA_DL];
	int  identyfikator;
}kand;

typedef struct{
	char nazwa[OKREG_DL];
	int liczba;			//liczba kandydatow w okregu - pomocnicza
	kand *kandydat[KANDYDACI_O];
}okr;

char *wczytaj(char *wyraz, int ile);
int wczytaj_liczbe(char tekst[]);
int sprawdz_identyfikator(kand* kandydat, int identyfikator);
void wydrukuj(char wyraz[], int n);
void max_id(kand* kandydat, int *max);
int porownanie(const void *kandydat1, const void *kandydat2);
void wyswietl_kandydatow(kand* kandydat, int liczba_kandydatow);
void wyswietl_okregi(okr* okreg, int liczba_okregow);
void usun_kandydata(kand* kandydat, int *pozycja, okr* okreg);
void dodaj_kandydata(kand* kandydat, okr*okreg);
void zmien_kandydata(kand* kandydat, okr* okreg);
void usun_okreg(okr* okreg, kand * kandydat);
void dodaj_okreg(kand* kandydat, okr*okreg);
void zmien_okreg(okr* okreg);
void wczytaj_kandydatow(okr *okreg, kand *kandydat);
int zapisz(okr *okreg);

