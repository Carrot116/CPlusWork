//
// Created by Carrot on 16/5/30.
//

#ifndef FIRSTDEMO_FUNHEAD_H
#define FIRSTDEMO_FUNHEAD_H

void GetUserInfo();
void GetHostInfo();

int getchoice(char* greet, char*choices[]);
void testMenu();

int getchoice_file(char* greet, char* choices[], FILE*in, FILE* out);
void testMenu2();
#endif //FIRSTDEMO_FUNHEAD_H
