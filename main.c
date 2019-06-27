//
//  main.c


/// includeは.cファイルに書く
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include "main.h"
#include "gameio.h"
#include "gamecalc.h"

int main(int argc, char **argv) {
  char field[LEN][LEN];  // 8x8の文字型2次元配列
  //  int blcnt = 0;    // 空白セル数のカウント
  int available;    // パス，終了判定フラグ
  char player = WHITE;    // 人間のコマ
  F_INFO info;    // 盤面情報（コマ，空白の個数）
  int gameMode = 0; // ゲームモード選択

  // 盤面の初期化
  initField(field);

  // スタート画面の表示
  startup(field);

  gameMode = setGameMode();
  if (gameMode == 0) {
    // ユーザに先手後手を選んでもらう
    player = setColor();
  }
  
  cls();

  // ゲーム開始
  printf("GAME START!!\n");
  uWait(2);

  // 初期盤面の情報を入れる（初手を判別するため）
  info = fieldStatus(field);

  // ゲームループ
  if (gameMode == 0) {
    // 一人プレイの場合
    // availableが0ならループ終了
    do {
      cls();
      available = 0;

      // プレイヤーが後手で、かつ1つも石が置かれていない（初手）の時はスキップする処理が書きたかった
      // もう少しスマートなやり方がある気がする・・
      if (info.blank == (LEN * LEN - 4) && player == BLACK) {
        // スキップ
      } else {
        /* 人間の手番 */
        printf("Your('%c') turn:\n", player);
        printField(field);

        // availableがもともと0なので、human()の返り値も0なら0、違うならその返り値(-1とか)になる
        // 最後まで行けば、humanのbetter変数の値が返ってくる
        available |= human(field, player);

        cls();
        // C言語にbooleanは無く、0がfalse扱い、それ以外はtrue扱い
        // つまりココは、availableが0かどうかということ
        // 0でないなら、コマを打ったあとの盤面を表示、0ならパス
        if(available) {
          printf("Your('%c') turn:\n", player);
          printField(field);
        } else printf("\tYou: Pass!\n");
      }

      uWait(1);

      /* コンピュータの手番 */
      available |= cpu(field, player == WHITE ? BLACK:WHITE); // 3項演算子でプレイヤーの交代
      cls();
      if(available) {
        printf("CPU's turn:\n\n");
        printField(field);
      }  else printf("\tCPU: Pass!\n");

      info = fieldStatus(field);
      viewStatus(info);

      printf("\n");
      uWait(1);
    } while(available);
  } else if (gameMode == 1) {
    // 二人プレイのとき
    do {
      cls();
      available = 0;

      printf("Your('%c') turn:\n", player);
      printField(field);

      available |= human(field, player);

      cls();
      if(available) {
        printf("Your('%c') turn:\n", player);
        printField(field);
      } else printf("\tYou: Pass!\n");

      player = (player == WHITE) ? BLACK : WHITE;
    } while (available != 0);
  }


  // ゲーム終了処理
  cls();

  printf("GAME FINISHED!!\n");

  printField(field);

  info = fieldStatus(field);
  viewStatus(info);

  printf("\tResult: ");
  if(info.black == info.white) {
    printf("EVEN\n");
  } else if(info.black > info.white) {
    printf("BLACK WIN!!  WHITE FAILED\n");
  } else {
    printf("WHITE WIN!!  BLACK FAILED\n");
  }

  printf("Please some key press and enter. Game will end.\n");
  scanf(%c, &player);

  return 0;
}


