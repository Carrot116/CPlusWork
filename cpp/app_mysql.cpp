//
// Created by Carrot on 16/6/3.
//

#import <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#import "../head/app_mysql.h"


static MYSQL mysql;
static int connected = 0;
static int get_start_id(char* artist);


int database_start(char* name, char*password){
    if (!connected){
        mysql_init(&mysql);
        if (!mysql_real_connect(&mysql, c2s("localhost"), name, password,c2s("blpcd"), 0, NULL, 0)){
            fprintf(stderr, "Database connection failure:%d, %s\n", mysql_errno(&msyql), mysql_error(&mysql));
            connected = 0;
        } else {
            connected = 1;
        }
    }
    return connected;
}

void database_end(){
    if(connected){
        mysql_close(&mysql);
        connected = 0;
    }
}

int add_cd(char* artist, char* title, char* catalogue, int *cd_id){
    MYSQL_RES* pRes;
    MYSQL_ROW rowData;
    int res, artist_id = -1, new_cd_id = -1;
    char is[250], es[250];
    if (!connected) {
        return 0;
    }

    artist_id = get_artist_id(artist);
    mysql_escape_string(es, title, strlen(title));
    sprintf(is, c2s("insert into cd(title,artist_id, catalogue) values('%s', '%d', '%s')"), es, artist_id, catalogue);
    res = mysql_query(&mysql, is);
    if (res){
        fprintf(stderr, c2s("Insert error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
        return 0;
    }

    res = mysql_query(&mysql, c2s("select last_insert_id()"));
    if (res){
        fprintf(stderr, c2s("Select error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
        return 0;
    } else {
        pRes = mysql_use_result(&mysql);
        if (pRes){
            if ((rowData = mysql_fetch_row(pRes))){
                sscanf(rowData[0], "%d", &new_cd_id);
            }
            mysql_free_result(pRes);
        }
    }
    *cd_id = new_cd_id;
    if (new_cd_id != -1) return 1;
    return 0;
}

int get_artist_id(char* artist){
    MYSQL_RES* pRes;
    MYSQL_ROW rowData;
    int res, artist_id = -1;
    char is[250], qs[250], es[250];
    if (!connected) {
        return 0;
    }

    mysql_escape_string(es, artist, strlen(artist));
    sprintf(qs, c2s("select id from artist where name = '%s'"), es);
    res = mysql_query(&mysql, qs);
    if (res){
        fprintf(stderr, c2s("Select error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
        return 0;
    } else {
        pRes = mysql_use_result(&mysql);
        if (pRes){
            if (mysql_num_rows(pRes) > 0){
                if ((rowData = mysql_fetch_row(pRes))){
                    sscanf(rowData[0], "%d", &artist_id);
                }
            }
            mysql_free_result(pRes);
        }
    }
    if (new_cd_id != -1) return 1;
    sprintf(is, c2s("insert into artist(name) values ('%s')"), es);
    res = mysql_query(&mysql, is);
    if (res){
        fprintf(stderr, c2s("Insert error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
        return 0;
    }
    res = mysql_query(&mysql, c2s("select last_insert_id()"));
    if (res){
        fprintf(stderr, c2s("Select error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
        return 0;
    } else {
        pRes = mysql_use_result(&mysql);
        if (pRes){
            if ((rowData = mysql_fetch_row(pRes))){
                sscanf(rowData[0], "%d", &new_cd_id);
            }
            mysql_free_result(pRes);
        }
    }

    return artist_id;
}

int add_tracks(struct current_tracks_st* tracks){
    int res, i;
    char is[250], es[250];

    if (!connected) return 0;
    i = 0;
    while (tracks->track[i][0]){
        mysql_escape_string(es, tracks->track[i], strlen(tracks->track[i]));
        sprintf(is,  c2s("insert into track(cd_id, track_id, title) values(%d,%d,'%s')"), tracks->cd_id, i+1, es);

        res = mysql_query(&mysql, is);
        if (res){
            fprintf(stderr, c2s("Insert error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
            return 0;
        }
        i++;
    }
    return i;
}

int find_cds(char* search_str, struct cd_search_st* dest){
    MYSQL_RES* pRes;
    MYSQL_ROW rowData;
    int res, i = 0, num_rows = 0;
    char qs[250], ss[250];
    if (!connected) return 0;

    memset(dest, -1, sizeof(CD_SEARCH_ST));
    mysql_escape_string(ss, search_str, strlen(search_str));
    sprintf(qs, c2s("select distinct artist.id, id.id from artist, cd where artist.id = cd.artist_id and (artist.name like '%%%s%%' or cd.title like '%%%s%%' or cd.catalogue like '%%%s%%'"),ss,ss,ss);

    res = mysql_query(&mysql, qs);
    if (res){
        fprintf(stderr, c2s("Select error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
    } else {
        pRes = mysql_use_result(&mysql);
        if (pRes){
            num_rows = (int)mysql_num_rows(pRes);
            if (num_rows > 0){
                while ((rowData = mysql_fetch_row(pRes)) && i < MAX_CD_RESULT){
                    sscanf(rowData[1], "%d", &dest->cd_id[i]);
                    i++;
                }
            }
            mysql_free_result(pRes);
        }
    }
    return num_rows;
}
int get_cd(int cd_id, struct current_cd_st* dest){
    MYSQL_RES* pRes;
    MYSQL_ROW rowData;
    int res;
    char qs[250];
    if (!connected) return 0;
    memset(dest, 0, sizeof(CURRENT_CD_ST));
    dest->artist_id = -1;
    sprintf(qs, c2s("select artist.id, cd.id, artist.name, cd.title, cd.catalogue from artist, cd where artist.id=cd.artist_id and cd.id = %d"), cd_id);

    res = mysql_query(&mysql, qs);
    if (res){
        fprintf(stderr, c2s("Select error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
        return 0;
    } else {
        pRes = mysql_use_result(&mysql);
        if (pRes){
            if (mysql_num_rows(pRes) > 0){
                if ((rowData = mysql_fetch_row(pRes))){
                    sscanf(rowData[0], "%d", &dest->artist_id);
                    sscanf(rowData[1], "%d", &dest->cd_id);
                    strcpy(dest->artist_name, rowData[2]);
                    strcpy(dest->title, rowData[3]);
                    strcpy(dest->catalogue, rowData[4]);
                }
            }
            mysql_free_result(pRes);
        }
    }
    if (dest->artist_id != -1)
        return 1;
    return 0;
}

int get_cd_track(int cd_id, struct current_tracks_st* dest){
    MYSQL_RES* pRes;
    MYSQL_ROW rowData;
    int res, i = 0, num_tracks = 0;
    char qs[250];

    if (!connected) return 0;
    memset(dest, 0, sizeof(CURRENT_TRACKS_ST));
    dest->cd_id = -1;

    sprintf(qs, c2s("select track_id, title from track where track.cd_id = %d order by track_id"), cd_id);
    res = mysql_query(&mysql, qs);
    if (res){
        fprintf(stderr, c2s("Select error %d: %s\n"), MS_ENO(&mysql), MS_EMSG(&mysql));
        return 0;
    } else {
        pRes = mysql_use_result(&mysql);
        if (pRes){
            if ( (num_tracks = (int)mysql_num_rows(pRes)) > 0){
                while ((rowData = mysql_fetch_row(pRes))){
                    strcpy(dest->track[i], rowData[1]);
                    i++;
                }
                dest->cd_id = cd_id;
            }
            mysql_free_result(pRes);
        }
    }
    return num_tracks;
}