#define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
#include<stdio.h>
#include<windows.h>

eCMD Menu() {

    while (true) {
        system("cls");
        printf("��� ���� ���� \"������� �������������� �������\"\n");
        printf("1. ��������� ������� �� �����\n");
        printf("2. ������� ������� � �������\n");
        printf("3. �������� ������ � �������\n");
        printf("4. ������������� �������\n");
        printf("5. �������� ������ \n");
        printf("6. ������� ������\n");
        printf("7. ����� �����\n");
        printf("8. �������� �������\n");
        printf("9. ��������� ������� � ����\n");
        printf("10 �������� ����� ������� �����\n");
        printf("0. �����\n");
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
            printf("������������ �������\n");
        }
    }
}