/********************************************************
************************* LIBRARIES *********************
*********************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

using namespace std;

/********************************************************
*********************** KONSTANTEN **********************
*********************************************************/

#define ANZAHL_PRALINEN 					3
#define ANZAHL_ZUTATEN 						7
#define ANZAHL_ZUTATEN_PRO_PRALINE		5

// Hier bitte Dateinamen entsprechend ändern
#define DATEI_ZUTATEN_NAME					"zutaten.txt"
#define DATEI_REZEPTE_NAME					"schoki.txt"

/********************************************************
*********************** DATENTYPEN **********************
*********************************************************/

// Datentyp für einzelne Zutaten
struct zutat_t {
	char 					name[20];
	float 				preis_pro_100gramm;
};

// Datentyp für Zutat innerhalb der Schokolade
struct schoko_zutat_t {
	int 					id;
	int 					menge_in_prozent;
	double 				rohstoffkosten;
};

// Datentyp für Kosten einer Schokoladentafel
struct kosten_t {
	// Rohstoffkosten für eine Tafel Schokolade
	double 				rohstoff_einheit;
	// Rohstoffkosten für eine Tafel * Anzahl der Tafeln
	double 				rohstoff_gesamt;
	int 					personal;
	int 					betrieb;
	int 					sonstige;
	// Gesamte Produktionskosten
	int 					gesamt;
};

// Datentyp für Pralinen
struct schokolade_t {
	char 					name[20];
	int 					gewicht;
	schoko_zutat_t 	zutat[ANZAHL_ZUTATEN_PRO_PRALINE];
	kosten_t				kosten;
};