//
//  gamecalc.h


#ifndef GAMECALC_H
#define GAMECALC_H

#include <stdio.h>
#include "main.h"

// プロトタイプ宣言

void initField(char f[LEN][LEN]);
int setPos(int y, int x, char c, char f[LEN][LEN], int set);
int directCount(int y, int x, int dy, int dx, char c, char f[LEN][LEN], int set);
char *beInField(char field[LEN][LEN], int y, int x);
int blankCellCount(char f[LEN][LEN]);
void availableCellList(char f[LEN][LEN], CELL* list, char player);
int cpu(char f[LEN][LEN], char);
int human(char f[LEN][LEN], char);
F_INFO fieldStatus(char f[LEN][LEN]);

#endif // GAMECALC_H
