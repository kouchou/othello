//
//  gameio.h


#ifndef GAMEIO_H
#define GAMEIO_H

#include <stdio.h>

// プロトタイプ宣言
void startup(char field[][LEN]);
char setColor(void);
void printField(char f[LEN][LEN]);
void uWait(int sec);
void cls(void);
void viewStatus(F_INFO info);

#endif // GAMEIO_H
