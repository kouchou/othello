//
//  gamecalc.c

#include "main.h"
#include "gamecalc.h"

#include <stdlib.h>
#include <stdio.h>

/* フィールドの初期化 */
void initField(char f[LEN][LEN]) {
  int x, y;

  for(y = 0; y < LEN; y++) {
    for(x = 0; x < LEN; x++) {
      f[y][x] = ' ';
    }
  }

  // 初期位置
  f[3][3] = f[4][4] = WHITE;
  f[4][3] = f[3][4] = BLACK;
}

/* 指定座標に指定文字が置けるかチェックする */
// 仮引数のsetは1なら実際にコマを置く、0なら置かない
int setPos(int Y, int X, char c, char f[LEN][LEN], int set) {
  int count = 0;

  //上方向
  count += directCount(Y, X, -1, 0, c, f, set);
  //下方向
  count += directCount(Y, X, 1, 0, c, f, set);
  //左方向
  count += directCount(Y, X, 0, -1, c, f, set);
  //右方向
  count += directCount(Y, X, 0, 1, c, f, set);
  //左上方向
  count += directCount(Y, X, -1, -1, c, f, set);
  //右上方向
  count += directCount(Y, X, 1, -1, c, f, set);
  //左下方向
  count += directCount(Y, X, -1, 1, c, f, set);
  //右下方向
  count += directCount(Y, X, 1, 1, c, f, set);

  // setが1(セットする設定)で
  // countも1以上なら実際にマスをプレイヤーのコマで埋める
  if(set && count) f[Y][X] = c;

  return count; // 置けないときは0が帰る
}

/* 指定方向へのカウント */
int directCount(int y, int x, int dy, int dx, char c, char f[LEN][LEN], int set) {
  int i;
  int count = 0;
  char *p;

  x += dx;
  y += dy;

  // cと同じ文字を探す
  // pに、指定したマスのポインタを渡す（なければNULL）
  // pがNULLでなく、そのpにある値が指定した文字と同じでない間ループする
  // pがNULL(範囲外)だったり、自分の石だと終了
  while((p = beInField(f, y, x)) && (*p != c)) {
    if(*p == ' ') {
      count = 0;
      break;
    } else {
      count++;
    }
    x += dx;
    y += dy;
  }

  //フィールドの端まで達したとき
  // p は NULL
  //同じ文字が見つかったとき
  // p は cに等しい

  // pがNULLになっているということは、フィールドの端まで相手の駒で埋まっているということなのでひっくり返せない
  if(p == NULL) count = 0;

  // 裏返し処理
  if(set && count > 0) {
    // まず1回戻る
    x -= dx;
    y -= dy;
    for(i = 0; i < count; i++) {
      f[y][x] = c;
      x -= dx;
      y -= dy;
    }
  }

  return count;
}

/* 座標がフィールド内かどうか判定する関数 */
char *beInField(char field[LEN][LEN], int y, int x) {
  // フィールド内ならポインタを返す
  if(x >= 0 && x < LEN && y >= 0 && y < LEN) return &field[y][x];

  // フィールド外ならNULL
  return NULL;
}

/* 空白セルのカウント */
int blankCellCount(char f[LEN][LEN]) {
  int x, y;
  int blcnt = 0;

  for(y = 0; y < LEN; y++) {
    for(x = 0; x < LEN; x++) {
      if(f[y][x] == ' ') {
        blcnt++;
      }
    }
  }

  return blcnt;
}

/* 空白セルのリスト */
// listはCELL型のポインタ
// 空白セル数分のメモリは確保されている
void availableCellList(char f[LEN][LEN], CELL* list, char player) {
  int x, y;
  int blcnt = 0; // listの順番をカウント

  // 盤面を1セルずつ見ていく
  for(y = 0; y < LEN; y++) {
    for(x = 0; x < LEN; x++) {
      // 空白のセルがあったら
      if(f[y][x] == ' ') {
        blcnt++;
        // セルの情報を格納
        list[blcnt - 1].x = x;
        list[blcnt - 1].y = y;
        list[blcnt - 1].p_cell = &f[y][x]; // 実際のセルへのポインタ
        list[blcnt - 1].count = setPos(y, x, player, f, 0); // おけない時は0が返ってくる
      }
    }
  }

}

/* コンピュータの手番 */
int cpu(char f[LEN][LEN], char player) {
  CELL* bl;
  int bc;
  int better = 0;
  CELL better_cell;
  int i;

  bc = blankCellCount(f); // 空白セル数

  // mallocはメモリを確保するための命令
  // 引数で指定するバイト数分のメモリが確保され、確保したメモリ領域へのポインタを返す。
  // (CELL*)malloc()のところは書き方 CELL*用に、メモリを確保する
  // sizeof()で、引数が何バイトなのか返してくる
  bl = (CELL*)malloc(sizeof(CELL) * bc); //bc(空白セルの数)分確保する
  if(bl == NULL) {
    printf("malloc Error!\n");
    return -1;
  }

  availableCellList(f, bl, player); // 取得

  /* ここから */

  // availableCellListで取得したCELLを一つずつ見ていく
  for(i = 0; i < bc; i++) {
    // countが一番多いセルを探す
    if(bl[i].count > better) {
      better = bl[i].count; // とりあえず最後の最善手で
      better_cell = bl[i]; // セルのコピーを作成？
    }
  }

  // 置ける所があれば
  if(better > 0) {
    // 実際に置く
    setPos(better_cell.y, better_cell.x, player, f, 1);
  }

  /* ここまで */
  free(bl);

  // 置けるところがない場合はbetterに0が入っているはず
  return better;
}

/* 人間の手番 */
int human(char f[LEN][LEN], char player) {
  CELL* bl;
  int bc; // 空白のセル数をカウント
  int better = 0;
  CELL better_cell;
  int i;
  int x, y;
  int check;

  bc = blankCellCount(f); // 空白セル数

  bl = (CELL*)malloc(sizeof(CELL) * bc); //1つ分あらかじめ確保
  if(bl == NULL) {
    printf("malloc Error!\n");
    return -1;
  }

  availableCellList(f, bl, player); // 取得

  /* ここから */

  for(i = 0; i < bc; i++) {
    if(bl[i].count > better) {
      better = bl[i].count; // とりあえず最後の最善手で
      better_cell = bl[i];
    }
  }

  // 置ける所があれば
  if(better > 0) {
    do {
      // ユーザ入力を受け取る
      printf("please input: ");
      scanf("%d %d", &x, &y);

      // 実際に置く
      // 選択したマスに置けない場合は0が返ってくる
      check = setPos(y, x, player, f, 1);
    } while(check == 0);
  }

  /* ここまで */
  free(bl);

  return better;

}

/* フィールドに置かれているオブジェクトの数を調べる */
F_INFO fieldStatus(char f[LEN][LEN]) {
  F_INFO info = {0, 0, 0};
  int x, y;

  for(y = 0; y < LEN; y++) {
    for(x = 0; x < LEN; x++) {
      switch(f[y][x]) {
        case WHITE:
          info.white++;
          break;
        case BLACK:
          info.black++;
          break;
        case BLANK:
          info.blank++;
          break;
      }
    }
  }

  return info;
}
