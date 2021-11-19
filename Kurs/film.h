#pragma once

struct Film {
    float cost = 0;
    int year = 0;
    int copies = 0;
    char name[128] = { 0 };
    char director[64] = { 0 };
    void show();
    void input(char*);
    void clean();
    Film(Film&);
    Film() {};
};