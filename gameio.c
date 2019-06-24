//
//  gameio.c


#include "main.h"
#include "gameio.h"

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <stdio.h>

/* 起動時の画面表示 */
void startup(char field[][LEN]) {
  printf("Welcome to Othello Game!!\n\n");
  printField(field);

  printf("You are WHITE('O') piece.\n\n");

  printf("Please some key press. Game will start.\n");
  getchar();
}

char setColor(void) {
  char color;
  color = '0';
  do {
    printf("set your color (w or b): ");
    scanf("%c", &color);
  } while(!(color == 'w' || color == 'b'));

  return (color == 'w') ? WHITE : BLACK;
}

/* それぞれのコマの数の表示 */
void viewStatus(F_INFO info) {
  printf("\tCount: Black('X'): %d\t", info.black);
  printf("White('O'): %d\n\n", info.white);
}

/* 一定時間待機させる関数 */
void uWait(int sec) {
  // Visual C++コンパイラへの対応
#ifdef _MSC_VER
  Sleep(sec * 1000);
#else
  //sleep(sec);
#endif
}

/* 画面クリア関数 */
void cls() {
  // Windows環境への対応（Visual C++）
#ifdef _MSC_VER
  system("cls");
#else
  // エスケープシーケンスの"ESC[2J"は画面クリア
  printf("\n\x1b[2J\n");
#endif
}

/* フィールドの描画 */
void printField(char f[LEN][LEN]) {
  int x, y;

  for(x = 0; x < LEN; x++) printf(x ? "  %d " : "     %d ", x);
  printf("\n");
  printf("   +---+---+---+---+---+---+---+---+\n");

  for(y = 0; y < LEN; y++) {
    printf(" %d |", y);
    for(x = 0; x < LEN; x++) {
      printf(x ? " %c |" : " %c |", f[y][x]);
    }
    printf("\n");
    printf("   +---+---+---+---+---+---+---+---+\n");
  }
  printf("\n");
}
