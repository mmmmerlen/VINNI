/*
14. В базе хранятся сведения об изделии, состоящем из узлов, деталей,
стандартных изделий, материалов.

Пример входного файла in.txt

Детали         Клапан          КД01    5
Детали         Втулка          КД02    7
Стандартные    Гайка           М1      15

Определить количество записей по каждому разделу.

Пример выходного файла out.txt

Раздел спецификации    Количество
Детали                 2
Стандартные            1
*/
/** Задание Гусятинер Л.Б., КМПО, 2022 */
/** Решение Гусятинер Л.Б., КМПО, */
/** Для КТ-2 301 / 302 / 305 / 306 / 309 / 315 ИС-23 */
/** Этап 1 из 5. Чтение из файла в массив и эхо-печать */
// 12:57 - 13:11 (0 часов 14 минут)
/** Этап 2 из 5. Частичное выполнение задания. Без сортировки */
// 13:33 - 13:58 (0 часов 25 минут) Итого: 0 часов 39 минут
/** Этап 3 из 5. Функции. Сортировка. */
// 8:40 - 8:58 (0 часов 18 минут) Итого: 0 часов 57 минут

#include <stdio.h>
#include <string.h>
#include <locale.h>

#define AR_LEN 100

struct Section {
    char name[50];
    int count;
};

int lt(struct Section a, struct Section b);
// возвращает true, если a < b лексикографически

void swap(struct Section *pa, struct Section *pb);

void ar_sort(struct Section ar[], int n);
// выбором

void ar_print(struct Section ar[], int n);

int main(void) {
    setlocale(LC_ALL, "");

    struct Section ar[AR_LEN];
    struct Section section = {0, 0};

    FILE *f_in = fopen("in.txt", "r");

    int count = 0;
    int i;

    while (
        count < AR_LEN &&
        1 == fscanf(f_in, "%s %*s %*s %*d", section.name)
    ) {
        int section_idx = -1;

        for (i = 0; i < count; ++i) {
            if (strcmp(section.name, ar[i].name) == 0) {
                section_idx = i;
                break;
            }
        }

        if (section_idx == -1) {
            section_idx = count;
            section.count = 1;
            ++count;
        }
        else {
            section.count = ar[section_idx].count + 1;
        }

        ar[section_idx] = section;
    }

    fclose(f_in);

    ar_print(ar, count);

    ar_sort(ar, count);

    printf("\nsorted\n");

    ar_print(ar, count);

    return 0;
}

int lt(struct Section a, struct Section b) {
    // возвращает true, если a < b лексикографически
    return strcmp(a.name, b.name) < 0;
}

void swap(struct Section *pa, struct Section *pb) {
    struct Section temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void ar_sort(struct Section ar[], int n) {
    // выбором
    int i;

    for (i = 0; i < n - 1; ++i) {
        int imin = i;
        int j;

        for (j = i + 1; j < n; ++j) {
            if (lt(ar[j], ar[imin])) {
                imin = j;
            }
        }

        if (i != imin) {
            swap(&ar[i], &ar[imin]);
        }
    }
}

void ar_print(struct Section ar[], int n) {
    int i;

    for (i = 0; i < n; ++i) {
        printf("%s: %d\n", ar[i].name, ar[i].count);
    }
}