#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

int procitaj_datoteku(char* naziv_datoteke);
Student* alociraj_i_procitaj_studente(int brojStudenata, char* naziv_datoteke);


typedef struct Student{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}Student;

int main(){

    int br=0;
    char ime_datoteke[MAX_LINE]={0};
    Student* student=NULL;

    printf("Upisite naziv datoteke");
    scanf(" %s",ime_datoteke);

    br=procitaj_broj_studenata_u_datoteci(ime_datoteke);
    printf("Broj studenata je: %d",br);


    student=alociraj_i_procitaj_studente(br,ime_datoteke);
    
    for(int i=0; i<br;i++){

        printf(" %s\t%s\t%lf\n",student[i].ime, student[i].prezime, student[i].bodovi);
    }

    return 0;
}


int procitaj_broj_studenata_u_datoteci(char* naziv_datoteke){
    int brojac=0;
    FILE* datoteka=NULL;
    char buffer[MAX_LINE]={0};

    datoteka=fopen(naziv_datoteke, "r");
    if(!datoteka){
        printf("Greska, datoteka ne postoji");
        return -1;
    }

    while( !feof(datoteka)){

        fgets(buffer,MAX_LINE,datoteka);
        brojac++;
    }

    fclose(datoteka);

    return brojac;
}

Student* alociraj_i_procitaj_studente(int brojStudenata, char* naziv_datoteke){

    int brojac=0;
    FILE* datoteka=NULL; 
    Student* studenti=NULL;

    studenti= (Student*)malloc(brojStudenata*sizeof(Student));
    datoteka=fopen(naziv_datoteke,"r");

    while( !feof(datoteka)){

        fscanf(datoteka," %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, studenti[brojac].bodovi);
        brojac++;
    }

    fclose(datoteka);

    return studenti;
}

