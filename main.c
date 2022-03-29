#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "node.h"
//#pragma once

node *binary_tree;
// binary_tree - ссылка на корневую вершину
bool created = false;
bool PROG = true;
// created - переменная, отвечающая за состояние существования дерева
// PROGRAMM - переменная, отвечающая за жизненный процесс программы
int STATE = 0;
/*
 * STATE - переменная, отвечающая за состояние программы
 * STATE = 0 - menu
 * STATE = 1 - extrafunctions
 * STATE = 2 - quit
 */

/* сontinue_phase():
 *
 *  Функция считывает значение, чтобы приостановить программу перед переходом между обновлениями меню
 *
*/
void continue_phase() {
    int in;
    printf("Введите 1, чтобы продолжить: ");
    scanf("%d",&in);
    while(in != 1) {
    printf("Введено неправильное значение!\nПовторите попытку!\n");
    scanf("%d",&in);
    }
    system("clear");
}

/*  insert_node():
 *
 *      Функция вставки вершины в двоичное дерево
 *
 */

void insert_node() {
    int vert;
    printf("Введите новую вершину: ");
    scanf("%d", &vert);

    if(!created) {
        binary_tree = create_node(vert);
        if(binary_tree == NULL)
            printf("Вершина не создана!\n");
        else {
            created = true;
            printf("Создана вершина со значением %d\n", binary_tree->key);
        }
    }
    else {
        node *n = create_node(vert);
        if(n == NULL)
            printf("Вершина не создана!\n");
        else {
            insert(binary_tree, n);
            printf("Создана вершина со значением %d\n", n->key);
        }
    }
    continue_phase();
}

/*  delete_node():
 *
 *      Функция удаления вершины из двоичного дерева
 *
 */

void delete_node() {
    int val;
    printf("Введите значение, которое хотите удалить: ");
    scanf("%d",&val);
    binary_tree = delete(binary_tree,val);
    if(binary_tree == NULL) {
        printf("Дерево было удалено\n");
        created = false;
    }
    continue_phase();
}

/*  tree_output():
 *
 *  Функция вывода вершин двоичного дерева:
 *
 *  root
 *  |root->left
 *  ||(root->left)->left
 *  ||(root->left)->right
 *  |root->right
 *  ||(root->right)->left
 *  |||((root->right)->left)->left
 *
 */

void tree_output() {
    if(!created)
        printf("Дерево еще не создано!\n");
    else print_nodes(binary_tree, 0);
    continue_phase();
}

/*  destroy_tree():
 *
 *      Функция удаления дерева и очищения памяти
 *
 */

void destroy_tree() {
    if(!created)
        printf("Дерево было уничтожено.\n");
    else {
        destruction(binary_tree);
        created = false;
        printf("Дерево было уничтожено.\n");
    }
    if(PROG) continue_phase();
}

/*  is_BTree():
 *
 *      Функция проверяет, является ли бинарное дерево B-деревом
 *
 */

void is_BTree() {
    if(!created)
        printf("Данное дерево является B-деревом.\n");
    else if(BTree_check(binary_tree))
        printf("Данное дерево является B-деревом.\n");
    else
        printf("Данное дерево не является B-деревом.\n");
    continue_phase();
}

/*  tree_width();
 *
 *
 *
 */

void tree_width() {
    if(!created)
        printf("Ширина дерева: 0\n");
    else printf("Ширина дерева: %d\n", max_depth(binary_tree));
    continue_phase();
}

/*  num_of_vertix()
 *
 *      Функция выводит количество вершин в дереве
 *
 */

void num_of_vertix() {
    if(!created)
        printf("Количество вершин: 0\n");
    else printf("Количество вершин: %d\n", vertex_number(binary_tree));
    continue_phase();
}

/*  num_of_nonterminal():
 *
 *      Функция выводи количество нетерминантных вершин(т.е листьев)
 *
 */

void num_of_nonterminal() {
    if(!created)
        printf("Количество нетерминантных вершин: 0\n");
    else printf("Количество нетерминантных вершин: %d\n", non_terminal_number(binary_tree));
    continue_phase();
}

void val_of_the_deepest_leaf() {
    if(!created)
        printf("Значение самого глубокого листа: 0\n");
    else printf("Значение самого глубокого листа: %d\n", deepest_leaf_value(binary_tree));
    continue_phase();
}

bool extra_functions() {
    system("clear");
    int ans;
    printf("Выберите функцию:\n"
           "(1)Проверка на B-дерево\n"
           "(2)Ширина двоичного дерева\n"
           "(3)Количество вершин\n"
           "(4)Количество нетерминальных вершин\n"
           "(5)Значение самого глубокого листа\n"
           "(6)Назад в меню\n"
           "(0)Выход из приложения\n"
           "Введите команду: ");
    scanf("%d",&ans);

    switch (ans) {
        case 1:
            is_BTree();
            break;
        case 2:
            tree_width();
            break;
        case 3:
            num_of_vertix();
            break;
        case 4:
            num_of_nonterminal();
            break;
        case 5:
            val_of_the_deepest_leaf();
            break;
        case 6:
            STATE = 0;
            system("clear");
            break;
        case 0:
            STATE = 2;
            system("clear");
            break;
        default:
            printf("Ошибочное значение.\n");
            continue_phase();
            break;
    }
}

bool menu() {
    int ans;
    printf( "Menu:\n"
            "(1)Добавление вершины\n"
            "(2)Удаление вершины\n"
            "(3)Вывод дерева\n"
            "(4)Дополнительные функции\n"
            "(5)Удаление дерева\n"
            "(0)Выход из приложения\n"
            "Введите команду: ");

    scanf("%d",&ans);
    switch (ans) {
        case 1:
            insert_node();
            break;
        case 2:
            delete_node();
            break;
        case 3:
            tree_output();
            break;
        case 4:
            system("clear");
            STATE = 1;
            break;
        case 5:
            destroy_tree();
            break;
        case 0:
            system("clear");
            STATE = 2;
            break;
        default:
            printf("Ошибочное значение.\n");
            continue_phase();
            break;
    }
}

bool quit() {
    int ans;
    printf("Вы точно хотите выйти?\n"
           "[Да(1)/Нет(0)]\n");
    scanf("%d",&ans);
    if(ans != 1) {
        if(ans) printf("Введено неправильное значение\n");
        STATE = 0;
        continue_phase();
        return false;
    }
    return true;
}

int main() {
    system("clear");
    while (PROG) {
        if (STATE == 0) menu();
        else if (STATE == 1) extra_functions();
        else PROG = !quit();
    }
    destroy_tree(binary_tree);
    printf("Завершение программы.\n");
    return 0;
}
