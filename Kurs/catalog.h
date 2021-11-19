#pragma once
#include<stdlib.h>
#include"film.h"

struct filmNode {
    Film* film = NULL;
    filmNode* next = NULL;
    filmNode();
    filmNode(filmNode&);
    ~filmNode();
};

struct Catalog {
    filmNode* head = NULL;
    int len = 0;
    void readFile();
    void writeFile();
    void show();
    void addFilm();
    void edit();
    void deleteFilm();
    int getAverYear();
    float getAverCopies();
    float getAverCost();
    int check(int);
    void find(Film**, int);
    Film* mostExpFilm();
    ~Catalog();
};