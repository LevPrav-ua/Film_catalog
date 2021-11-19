#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<cstdio>
#include<windows.h>
#pragma hdrstop
#include"film.h"
#include"catalog.h"
#include"menu.h"

int check(const Catalog&, const Catalog&, int);
Catalog* sortedCatalog(const Catalog&, bool);
int compare(const Catalog&);

int check(const filmNode* left, const filmNode* right, int type = 0) {
    switch (type)
    {
    case 0:
        return strcmp(left->film->name, right->film->name);
    case 1:
        return strcmp(left->film->director, right->film->director);
    case 2:
        return (left->film->year > right->film->year) ? 1 : -1;
    case 3:
        return (left->film->copies > right->film->copies) ? 1 : -1;
    case 4:
        return (left->film->cost > right->film->cost) ? 1 : -1;
    default:
        break;
    }
    return 0;
}
Catalog* sortedCatalog(const Catalog& cat, bool order = true) {
    if (cat.head == NULL) return NULL;
    Catalog* sorted = new Catalog();
    filmNode* tmp = cat.head->next, *sort;
    sorted->head = new filmNode(*cat.head);
    sorted->len++;

    int type = -1;
    while (type < 0 || type >4) {
        printf("Сортировка\n0 - по названию; 1 - по имени режиссёра; 2 - по году премьеры; 3 - по кол-ву купленных копий; 4 - по стоимости \n");
        fflush(stdin);
        scanf("%d", &type);
    }

    while (tmp != NULL) {
        sort = sorted->head;
        if (check(tmp,sort, type) < 0) {
            sort = new filmNode(*tmp);
            sort->next = sorted->head;
            sorted->head = sort;
            sorted->len++;
            tmp = tmp->next;
            continue;
        }
        while (sort->next != NULL &&
            check(tmp, sort->next, type) >= 0)
            sort = sort->next;
        if (sort->next == NULL) {
            sort->next = new filmNode(*tmp);
        }
        else {
            filmNode* s_tmp = sort->next;
            sort->next = new filmNode(*tmp);
            sort->next->next = s_tmp;
        }
        sorted->len++;
        tmp = tmp->next;
    }
    if (order == false) {
        filmNode* new_head = NULL;
        for (filmNode* pos = sorted->head; pos != NULL;) {
            filmNode* save_node = pos->next;
            pos->next = new_head;
            new_head = pos;
            pos = save_node;
        }
        sorted->head = new_head;
    }
    return sorted;
}
int compare(const Catalog& cat) {
    if (cat.head == NULL) {
        printf("Каталог пуст\n");
        return 0;
    }

    bool in = true;
    FILE* file = NULL;
    while (in) {
        printf("Введите имя файла, с которым хотите сравнить каталог:\n");
        char fileName[64];
        fflush(stdin);
        scanf("%s", fileName);
        file = fopen(fileName, "r");
        if (file == NULL) {
            printf("Ошибка открытия файла\n");
            continue;
        }
        in = false;
    }
    filmNode* tmp = cat.head;
    int i, changes = 0;
    for(i = 0;!feof(file) && tmp != NULL;i++)
    {
        char buf[128];
        char str[128] = { 0 };
        fgets(str, 127, file);
        if (str[0] == '\0') break;
        sprintf(buf, "%s;%s;%d;%d;%.2f\n", tmp->film->name, tmp->film->director,
            tmp->film->year,
            tmp->film->copies, tmp->film->cost);
        if (strcmp(str, buf) != 0) changes++;
        tmp = tmp->next;
    }
    fclose(file);
    return changes + cat.len - i;
}

int main(int argc, char* argv[]) {
    system("chcp 1251");
    system("color 70");

    Catalog* cat = new Catalog();
    Film* films[10] = { NULL };
    Catalog* sorted;

    while (true) {
        eCMD cmd = Menu();
        switch (cmd)
        {
        case CMD_EXIT:
            printf("Проверим, есть ли у вас несохранённые данные? 1/0 \n");
            int in;
            fflush(stdin);
            scanf("%d", &in);
            if (in == 0) return 0;
            if (compare(*cat) > 0) {
                printf("У вас есть несохранённые изменения. Хотите сохранить?\n (1/0)\n");
                int ans;
                fflush(stdin);
                scanf("%d", &ans);
                if (ans == 1)
                    cat->writeFile();
            }
            delete cat;
            return 0;
        case CMD_READ:
            cat->readFile();
            break;
        case CMD_SHOW:
            cat->show();
            break;
        case CMD_ADD:
            cat->addFilm();
            break;
        case CMD_SORT:
        {
            printf("Хотите сортировать по возрастанию или по убываюнию?\n 1/2\n");
            int ans;
            bool order = true;
            scanf("%d", &ans);
            if (ans == 2)
                order = false;
            sorted = sortedCatalog(*cat, order);
            if (sorted == NULL)
                break;
            delete cat;
            cat = sorted;
            printf("Сортировка прошла успешно\n");
            break;
        }
        case CMD_EDIT:
            cat->edit();
            break;
        case CMD_DELETE:
            cat->deleteFilm();
            break;
        case CMD_FIND:
            cat->find(films,10);
            if (films[0] == NULL) {
                printf("Совпадений не найдено\n");
            }
            for (int i = 0; films[i] != NULL; i++) {
                films[i]->show();
                printf("\n");
            }
            break;
        case CMD_CLEAN:
            cat->~Catalog();
            cat = new Catalog();
            break;
        case CMD_SAVE:
            cat->writeFile();
            break;
        case CMD_MEF:
            Film* exp = cat->mostExpFilm();
            if (exp != NULL)
                exp->show();
            printf("\n");
            break;
        }
        system("pause");
    }
    return 0;
}