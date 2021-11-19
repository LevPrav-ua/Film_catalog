#define _CRT_SECURE_NO_WARNINGS
#include"film.h"
#include<stdio.h>
#include<cstring>
#include<stdlib.h>

Film::Film(Film& film) {
    if (&film == NULL) return;
    this->copies = film.copies;
    this->year = film.year;
    this->cost = film.cost;
    strcpy(this->name, film.name);
    strcpy(this->director, film.director);
}
void Film::input(char* str) {
    int i, j;
    for (i = 0; str[i] != ','; i++);
    memcpy(name, str, i);
    name[i++] = '\0';
    for (j = i; str[j] != ','; j++);
    memcpy(director, str + i, j - i);
    director[j++] = '\0';
    sscanf(str + j, "%d, %d, %f", &year, &copies, &cost);
}
void Film::show() {
    printf("|     %-20.20s |         %-15.20s|  %-4d |     %-6d |  %-10.2f |",
        name, director, year, copies, cost);
}
void Film::clean() {
    memset(name, 0, 128);
    memset(director, 0, 64);
    cost = year = copies = 0;
}

