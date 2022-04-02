#include <stdio.h>
#include <string.h>
#include "node.h"

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

int get_command(bool *st) {
    bool num = true;
    int size = 0;
    int capacity = 1;
    char *str = malloc(sizeof(char));
    char k;
    while(k = getchar()) {
        if(k == '\n')
            break;
        if(k < '0' || k > '9')
            num = false;
        str[size] = k;
        size++;
        if(size == capacity) {
            char *new_str = malloc(sizeof(char) * 2 * capacity);
            for(int i = 0;i < capacity;i++)
                new_str[i] = str[i];
            free(str);
            str = new_str;
            capacity *= 2;
        }
    }

    for(int i = 0;i < size;i++)
        printf("%c",str[i]);
    printf("\n");

    if(num && size < 9) {
        int ans = 0;
        for(int i = 0;i < size;i++)
            ans = (str[i] - '0') + ans * 10;
        free(str);
        *st = true;
        printf("%d\n",ans);
        return ans;
    }
    else {
        *st = false;
        free(str);
        return 0;
    }
}

void continue_phase() {
    printf("Введите 1, чтобы продолжить: ");
    bool st;
    int in = get_command(&st);
    while(in != 1) {
        printf("Введено неправильное значение!\nПовторите попытку!\n");
        in = get_command(&st);
    }
    system("clear");
}

void insert_node() {
    bool st;
    printf("Введите новую вершину: ");
    int new_node = get_command(&st);
    if(!st)
        printf("Введено неправильное значение!\n");
    else {
        if (!created) {
            binary_tree = create_node(new_node);
            if (binary_tree == NULL)
                printf("Вершина не создана!\n");
            else {
                created = true;
                printf("Создана вершина со значением %d\n", binary_tree->key);
            }
        } else {
            node *n = create_node(new_node);
            if (n == NULL)
                printf("Вершина не создана!\n");
            else {
                insert(binary_tree, n);
                printf("Создана вершина со значением %d\n", n->key);
            }
        }
    }
    continue_phase();
}

void delete_node() {
    int val;
    bool st;
    printf("Введите значение, которое хотите удалить: ");
    val = get_command(&st);
    if(!st)
        printf("Введено неправильное значение!\n");
    else {
        binary_tree = delete(binary_tree, val);
        if (binary_tree == NULL) {
            printf("Дерево было удалено\n");
            created = false;
        }
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
    else
        print_nodes(binary_tree, 0);
    continue_phase();
}

void destroy_tree() {
    if(!created)
        printf("Дерево было уничтожено.\n");
    else {
        destruction(binary_tree);
        created = false;
        printf("Дерево было уничтожено.\n");
    }
    if(PROG)
        continue_phase();
}

void is_BTree() {
    if(!created)
        printf("Данное дерево является B-деревом.\n");
    else if(BTree_check(binary_tree))
        printf("Данное дерево является B-деревом.\n");
    else
        printf("Данное дерево не является B-деревом.\n");
    continue_phase();
}

void tree_width() {
    if(!created)
        printf("Ширина дерева: 0\n");
    else
        printf("Ширина дерева: %d\n", max_depth(binary_tree));
    continue_phase();
}

void num_of_vertix() {
    if(!created)
        printf("Количество вершин: 0\n");
    else
        printf("Количество вершин: %d\n", vertex_number(binary_tree));
    continue_phase();
}

void num_of_nonterminal() {
    if(!created)
        printf("Количество нетерминантных вершин: 0\n");
    else
        printf("Количество нетерминантных вершин: %d\n", non_terminal_number(binary_tree));
    continue_phase();
}

void val_of_the_deepest_leaf() {
    if(!created)
        printf("Значение самого глубокого листа: 0\n");
    else
        printf("Значение самого глубокого листа: %d\n", deepest_leaf_value(binary_tree));
    continue_phase();
}

bool extra_functions() {
    system("clear");
    printf("Выберите функцию:\n"
           "(1)Проверка на B-дерево\n"
           "(2)Ширина двоичного дерева\n"
           "(3)Количество вершин\n"
           "(4)Количество нетерминальных вершин\n"
           "(5)Значение самого глубокого листа\n"
           "(6)Назад в меню\n"
           "(7)Выход из приложения\n"
           "Введите команду: ");
    bool st;
    int ans = get_command(&st);
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
        case 7:
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
    printf( "Menu:\n"
            "(1)Добавление вершины\n"
            "(2)Удаление вершины\n"
            "(3)Вывод дерева\n"
            "(4)Дополнительные функции\n"
            "(5)Удаление дерева\n"
            "(6)Выход из приложения\n"
            "Введите команду: ");

    bool st;
    int ans = get_command(&st);
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
        case 6:
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
    printf("Вы точно хотите выйти?\n"
           "[Да(1)/Нет(2)]\n");
    bool st;
    int ans = get_command(&st);
    if(ans != 1 || !st) {
        if(ans != 2)
            printf("Введено неправильное значение\n");
        STATE = 0;
        continue_phase();
        return false;
    }
    return true;
}

int main() {
    system("clear");
    while (PROG) {
        if(STATE == 0)
            menu();
        else if(STATE == 1)
            extra_functions();
        else
            PROG = !quit();
    }
    destroy_tree();
    printf("Завершение программы.\n");
    return 0;
}
