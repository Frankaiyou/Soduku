#include <time.h>
#include <random>
#ifndef SODUKU_H
#define SODUKU_H

#endif // SODUKU_H
class Soduku {
    int map[9][9];
    int col[9][9];
    int row[9][9];
    int blo[9][9];
    int bac[9][9];
    void zero(int (*p)[9]) {
        for (int i = 0; i < 9; i += 1) for (int j = 0; j < 9; j += 1) p[i][j] = 0;
    }
    void filling(int *p, int po) {
        for (int* pos = p + po, i = 1; i <= 9; i += 1) {
            *pos = i;
            if (pos + 1 == p + 9) pos = p;
            else pos += 1;
        }
    }
    void clear() { zero(map), zero(col), zero(row), zero(blo); }
    void begin() {
        filling(map[0], 0); filling(map[1], 6); filling(map[2], 3);
        filling(map[3], 2); filling(map[4], 8); filling(map[5], 5);
        filling(map[6], 4); filling(map[7], 1); filling(map[8], 7);
    }
    void SwapRow(int a, int b) {
        for (int i = 0, tmp; i < 9; i += 1)
            tmp = map[a][i], map[a][i] = map[b][i], map[b][i] = tmp;
    }

    void hitRow() {
        for (int i = 0; i < 3; i += 1) {
            for (int j = 0; j < 10; j += 1) {
                int l = rand() % 3 + i * 3, r = rand() % 3 + i * 3;
                SwapRow(l, r);
            }
        }
    }
    void Swap(int a, int b) {
        for (int i = 0, tmp; i < 9; i += 1)
            tmp = map[i][a], map[i][a] = map[i][b], map[i][b] = tmp;
    }
    void hitCol() {
        for (int i = 0; i < 3; i += 1) {
            for (int j = 0; j < 10; j += 1) {
                int l = rand() % 3 + i * 3, r = rand() % 3 + i * 3;
                Swap(l, r);
            }
        }
    }
    void MakeBack() {
        for (int i = 0; i < 9; i += 1)
            for (int j = 0; j < 9; j += 1)
                bac[i][j] = map[i][j];
    }

    void remove(int siz) {
        for (int i = 0; i < siz; i += 1) {
            int r = rand() % 9, c = rand() % 9;
            map[r][c] = 0;
        }
    }


public:
    int GetYuan(int i, int j) {
        return bac[i][j];
    }
    Soduku() { }
    void init(int size) {
        srand(time(NULL) + 20011212);
        clear();
        begin();
        hitRow();
        hitCol();
        MakeBack();
        remove(size);
    }
    int Pos(int i, int j) { return map[i][j]; }
    int Set(int i, int j, int num) { map[i][j] = num; return true; }
};
