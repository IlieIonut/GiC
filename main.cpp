#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
char cuvant_citit[100];

ifstream f("date.in");
struct tranzitie {
    char litera;
    char stare[20];
} tranz[20];

/**
*
* @param cuvant reprezinta cuvantul actual din gramatica
* @param pozitie reprezinta pozitia pe care se afla prima litera mare din cuvant
* @param subsir reprezinta cuvantul cu care inlocuiesc litera mare
*/
void inserare(char cuvant[100], int pozitie, char subsir[20]) {
    char sir[100];
    sir[0] = NULL;
    int i;
    if (pozitie == 0) {
        strcpy(sir, subsir);
        strcat(sir, cuvant + 1);
        strcpy(cuvant, sir);
    } else {
        for (i = 0; i < pozitie; i++)
            sir[i] = cuvant[i];
        sir[pozitie] = NULL;
        strcat(sir, subsir);
        strcat(sir, cuvant + pozitie + 1);
        strcpy(cuvant, sir);
    }
}

/**
*
* @param cuv reprezinta cuvantul actual pe care il tot schimb la fiecare pas
inlocuind litera mare cu starea pe care o detine
* @param lung_tranz reprezinta de cate ori pot merge intr-un cuvant din literele mari
* @param OK retine daca cuvantul introdus este sau nu acceptat
*/
void GIC(char cuvant[100], int lungime_tranzitii, int &OK) {
    int i, pozitie = -1;
    char litera_mare;
    char copie_cuvant[100];
    for (i = 0; i < strlen(cuvant); i++)
        if (cuvant[i] >= 'A' && cuvant[i] <= 'Z') {
            litera_mare = cuvant[i];
            pozitie = i;
            i = strlen(cuvant);
        }
    if (pozitie == -1 && strcmp(cuvant, cuvant_citit) == 0)
        OK = 1;
    else {
        for (i = 0; i < lungime_tranzitii; i++)
            if (tranz[i].litera == litera_mare && strlen(cuvant) <= strlen(cuvant_citit) + 1) {
                strcpy(copie_cuvant, cuvant);
                if (strcmp(tranz[i].stare, "|") != 0)
                    inserare(copie_cuvant, pozitie, tranz[i].stare);
                else strcpy(copie_cuvant + pozitie, copie_cuvant + pozitie + 1);
                GIC(copie_cuvant, lungime_tranzitii, OK);
            }
    }
}

int main() {
    int lungime_tranzitii;
    int i, OK = 0;
    f >> lungime_tranzitii;
    for (i = 0; i < lungime_tranzitii; i++) {
        f >> tranz[i].litera;
        f.get();
        f >> tranz[i].stare;
        f.get();
    }
    char cuvant[100];
    cuvant[0] = 'S';
    cuvant[1] = NULL;
    cout << "Introduceti cuvantul:" << endl;
    cin >> cuvant_citit;
    cout << endl;
    GIC(cuvant, lungime_tranzitii, OK);
    if (OK == 0)
        cout << "cuvant neacceptat";
    else
        cout << "cuvant acceptat";
    return 0;
}
