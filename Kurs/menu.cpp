#define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
#include<stdio.h>
#include<windows.h>

eCMD Menu() {

    while (true) {
        system("cls");
        printf("Это Меню СУБД \"Каталог худоежственных фильмов\"\n");
        printf("1. Заполнить каталог из файла\n");
        printf("2. Вывести каталог в консоль\n");
        printf("3. Добавить запись в каталог\n");
        printf("4. Отсортировать каталог\n");
        printf("5. Изменить запись \n");
        printf("6. Удалить запись\n");
        printf("7. Найти фильм\n");
        printf("8. Очистить каталог\n");
        printf("9. Сохранить каталог в файл\n");
        printf("10 Показать самый дорогой фильм\n");
        printf("0. Выход\n");
        int ans = 0;
        scanf("%d", &ans);
        switch (ans) {
        case 1:
            return CMD_READ;
        case 2:
            return CMD_SHOW;
        case 3:
            return CMD_ADD;
        case 4:
            return CMD_SORT;
        case 5:
            return CMD_EDIT;
        case 6:
            return CMD_DELETE;
        case 7:
            return CMD_FIND;
        case 8:
            return CMD_CLEAN;
        case 9:
            return CMD_SAVE;
        case 10:
            return CMD_MEF;
        case 0:
            return CMD_EXIT;
        default:
            printf("Неправильная команда\n");
        }
    }
}