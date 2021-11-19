#define _CRT_SECURE_NO_WARNINGS
#include"catalog.h"
#include<stdlib.h>
#include<stdio.h>
#include<cstring>

filmNode::~filmNode() {
    delete film;
}
filmNode::filmNode() {
    film = new Film();
}
filmNode::filmNode(filmNode& f_node) {
    film = new Film(*f_node.film);
}

Catalog::~Catalog() {
    filmNode* tmp = head, * dlt;
    while (tmp != NULL) {
        dlt = tmp->next;
        delete tmp;
        tmp = dlt;
    }
}
void Catalog::readFile() {
    printf("Введите имя файла, который хотите читать:\n");
    char fileName[64];
    fflush(stdin);
    scanf("%s", fileName);
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("Файл пуст\n");
        return;
    }
    fseek(file, 0, SEEK_SET);

    filmNode* tmp;
    if (head == NULL) {
        head = new filmNode();
        char str[128] = { 0 };
        fgets(str, 127, file);

        head->film->input(str);
        tmp = head;
        len++;
    }
    else {
        tmp = head;
        while (tmp->next != NULL) tmp = tmp->next;
    }

    while (!feof(file))
    {
        char str[128] = { 0 };
        fgets(str, 127, file);
        if (str[0] == '\0') break;
        tmp->next = new filmNode();
        tmp->next->film->input(str);
        tmp = tmp->next;
        len++;
    }

    fclose(file);
    printf("Каталон заполнен !\n\n");
}
void Catalog::show() {
    if (head == NULL) {
        printf("Каталог пуст\n");
        return;
    }
    filmNode* tmp = head;
    int i = 1;
    printf("------------------------------------------------------------------------------------------\n");
    printf("№ |    НАЗВАНИЕ  ФИЛЬМА      |        РЕЖИССЁР        |  ГОД  |КОЛ-ВО КОПИЙ|     ЦЕНА    |\n");
    printf("------------------------------------------------------------------------------------------\n");
    while (tmp != NULL) {
        printf("%d ", i++);
        tmp->film->show();
        printf("\n");
        tmp = tmp->next;
    }
    printf("------------------------------------------------------------------------------------------\n");
    printf("                                                      | Ср.ГОД|  Ср.КОПИЙ  |   Ср.ЦЕНА   |\n");
    printf("                                                      ------------------------------------\n");
    printf("                                                      |  %-4d |   %-6.2f  |   %-10.2f|\n",
            getAverYear(), getAverCopies(), getAverCost());
    printf("                                                      ------------------------------------\n");
}
void Catalog::addFilm() {
    filmNode* tmp;
    if (len == 0) {
        head = new filmNode();
        tmp = head;
    }
    else {
        tmp = head;
        while (tmp->next != NULL) tmp = tmp->next;
        tmp->next = new filmNode();
        tmp = tmp->next;
    }
    printf("Введите НАЗВАНИЕ ФИЛЬМА, ИМЯ РЕЖИССЁРА, ГОД ВЫПУСКА, КОЛ-ВО КОПИЙ, ЦЕНУ\n");
    char str[128] = { 0 };
    while (char c = getchar() != '\n' && c != EOF);
    gets_s(str, 127); //gets была недоступна в VS
    tmp->film->input(str);
    len++;
}
void Catalog::edit() {
    show();
    if (head == NULL) return;
    bool in = true;
    int num;
    filmNode* tmp = head;
    while (in) {
        printf("Введите номер записи, которую хотите редактировать:\n");
        fflush(stdin);
        num = 0;
        scanf("%d", &num);
        if (num<1 || num > len) {
            printf("Неверный номер записи\n");
            continue;
        }
        in = false;
    }
    while (--num) tmp = tmp->next;
    tmp->film->clean();
    printf("Введите НАЗВАНИЕ ФИЛЬМА, ИМЯ РЕЖИССЁРА, ГОД ВЫПУСКА, КОЛ-ВО КОПИЙ, ЦЕНУ\n");
    char str[128] = { 0 };
    while (char c = getchar() != '\n' && c != EOF);
    gets_s(str, 127); //gets была недоступна в VS
    tmp->film->input(str);
    printf("Данные успешно изменены \n");
}
void Catalog::deleteFilm() {
    show();
    printf("Введите номер записи, которую хотите удалить:\n");
    fflush(stdin);
    int num = 0;
    scanf("%d", &num);
    if (num < 1 || num > len) {
        printf("Неверный номер записи\n");
        return;
    }
    --num;
    filmNode* tmp = head;
    if (num == 0) {
        filmNode* next = tmp->next;
        delete tmp;
        head = next;
        len--;
        return;
    }
    while (--num) tmp = tmp->next;
    filmNode* next = tmp->next->next;
    delete tmp->next;
    tmp->next = next;
    len--;
}
void Catalog::find(Film** films, int len = 1) {
    if (head == NULL) {
        printf("Каталог пуст! \n");
        return;
    }
    printf("Введите название фильма, который хотите найти: \n");
    fflush(stdin);
    char name[128];
    while (char c = getchar() != '\n' && c != EOF);
    gets_s(name, 127);
    int i = 0;
    for (filmNode* tmp = head; tmp != NULL && i < len; tmp = tmp->next) {
        if (strcmp(tmp->film->name, name) == 0) {
            films[i] = tmp->film;
            i++;
        }
    }
}
void Catalog::writeFile() {
    if (head == NULL) {
        printf("Каталог пуст\n");
        return;
    }
    printf("Введите имя файла, куда хотите поместить каталог\n");
    char fileName[64];
    scanf("%s", fileName);
    FILE* file;
    printf("Вы хотите дополнить или переписать файл ? (1/2)\n");
    int ans;
    scanf("%d", &ans);
    if (ans == 2)
        file = fopen(fileName, "w+");
    else
        file = fopen(fileName, "a+");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    filmNode* tmp = head;
    while (tmp != NULL) {
        char buf[256];
        sprintf(buf, "%s, %s, %d, %d, %.2f\n", tmp->film->name, tmp->film->director,
            tmp->film->year,
            tmp->film->copies, tmp->film->cost);
        fputs(buf, file);
        tmp = tmp->next;
    }
    fclose(file);
    printf("Запись прошла успешно\n");
}

int Catalog::getAverYear() {
    if (head == NULL) return 0;
    int i = 0, sum = 0;
    for (filmNode* tmp = head; tmp != NULL; tmp = tmp->next, i++) {
        sum += tmp->film->year;
    }
    return sum/i;
}

float Catalog::getAverCopies() {
    if (head == NULL) return 0;
    int i = 0, sum = 0;
    for (filmNode* tmp = head ; tmp != NULL; tmp = tmp->next, i++) {
        sum += tmp->film->copies;
    }
    return float(sum)/float(i);
}

float Catalog::getAverCost() {
    if (head == NULL) return 0;
    float i = 0, sum = 0;
    for (filmNode* tmp = head; tmp != NULL; tmp = tmp->next, i++) {
        sum += tmp->film->cost;
    }
    return sum/i;
}

Film* Catalog::mostExpFilm() {
    if (head == NULL) {
        printf("Каталог пуст\n");
        return NULL;
    }
    filmNode* max = head;
    for (filmNode* tmp = head->next; tmp != NULL; tmp = tmp->next) {
        if (tmp->film->cost > max->film->cost)
            max = tmp;
    }
    return max->film;
}

