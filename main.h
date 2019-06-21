//
//  main.h


// _MAIN_H_が定義されていなければ
// #ifndef ~ #endif までを実行
#ifndef _MAIN_H_
  #define _MAIN_H_

  // define定義
  #define LEN 8

  #define WHITE 'O' //白
  #define BLACK 'X' //黒
  #define BLANK ' ' //空白

  #define CPU BLACK //コンピュータ
  #define HUMAN WHITE //人間

  // セルの情報（取れる個数）
  typedef struct cell {
    int x;
    int y;
    char *p_cell;
    int count;
  } CELL;

  // フィールド情報構造体
  typedef struct finfo {
    int white;
    int black;
    int blank;
  } F_INFO;

#endif // _MAIN_H_
