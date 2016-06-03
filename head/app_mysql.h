//
// Created by Carrot on 16/6/3.
//

#ifndef FIRSTDEMO_APP_MYSQL_H_H
#define FIRSTDEMO_APP_MYSQL_H_H

#ifndef DDDDD
#define DDDDD
#define c2s(X) ((char*)#X)
#define MS_ENO(X) mysql_errno(X)
#define MS_EMSG(X) mysql_error(X)
#endif

typedef struct current_cd_st{
    int artist_id;
    int cd_id;
    char artist_name[100];
    char title[100];
    char catalogue[100];
}CURRENT_CD_ST,*PCURRENT_CD_ST;

typedef struct current_tracks_st{
    int cd_id;
    char track[20][100];
}CURRENT_TRACKS_ST, *PCURRENT_TRACKS_ST;

#define MAX_CD_RESULT 10
typedef struct cd_search_st{
    int cd_id[MAX_CD_RESULT];
}CD_SEARCH_ST, *PCD_SEARCH_ST;

int database_start(char* name, char*password);
void database_end();
int add_cd(char* artist, char* title, char* catalogue, int *cd_id);
int get_artist_id(char* artist);
int add_tracks(struct current_tracks_st* tracks);

int find_cds(char* search_str, struct cd_search_st* result);
int get_cd(int cd_id, struct current_cd_st* dest);
int get_cd_track(int cd_id, struct current_tracks_st* dest);
int delete_cd(int cd_id);
#endif //FIRSTDEMO_APP_MYSQL_H_H
