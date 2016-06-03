//
// Created by Carrot on 16/5/31.
//

#include "../head/FunMysql.h"
#include <stdio.h>
#include <cstring>

#include "../head/HXLMysql.h"
#include "../head/app_mysql.h"

void connect2mysql(){
    fprintf(stderr, "\nmysql version:%lu\n", mysql_get_client_version());
    MYSQL* mysql = mysql_init(NULL);

    if (!mysql){
        fprintf(stderr, "\nerror: %s",mysql_error(mysql));
        fprintf(stderr,"\nmysql_init fail\n");
        return;
    }

    if (mysql_real_connect(mysql, "localhost", "hxl","123456","db_im",0, NULL,0)){
        printf("\nConnecting success!\n");

        fprintf(stdout, "select :%d \n", mysql_query(mysql, "insert into t_user(name, age) values ('李四',23)"));
        fprintf(stdout, "affect :%llu rows\n", mysql_affected_rows(mysql));
    } else {
        fprintf(stderr, "error: %s",mysql_error(mysql));
        printf("\nConnecting fail!\n");
    }
    mysql_close(mysql);
}

void testWrapper(){
//    HXLMysql instance;
//    instance.connect("localhost", "hxl", "123456", "db_im");
//    fprintf(stdout, "select :%d \n", instance.query("insert into t_user(name, age) values ('赵云',23)"));
//    fprintf(stdout, "affect :%llu rows\n", instance.affected_rows());

//    HXLMysql::test();
//    HXLMysql::test_lastid();
//    HXLMysql::test_fetch_data();
//    HXLMysql::test_fetch_data2();
//    HXLMysql::test_fetch_data3();
//    HXLMysql::test_fetch_data4();
    testCD();
}

void testCD(){
    PCURRENT_CD_ST cd;
    PCURRENT_TRACKS_ST ct;
    PCD_SEARCH_ST cd_res;
    int cd_id;
    int res, i;

    database_start((char*)"hxl",(char*)"123456");
    res = add_cd(c2s("Mahler"),c2s("Symphony No 1"),c2s("4596102"),&cd_id);
    printf("Result of adding a cd was %d, cd_id is %d\n", res, cd_id);

    memset(ct,0, sizeof(CURRENT_TRACKS_ST));
    ct->cd_id = cd_id;
    strcpy(ct->track[0], c2s("Langsam Schleppend"));
    strcpy(ct->track[1], c2s("Kraftig bewegt"));
    strcpy(ct->track[2], c2s("Feierlich und gemessen"));
    strcpy(ct->track[3], c2s("Strumisch bewegt"));
    add_tracks(ct);


    res = find_cds(c2s("Symphony"),cd_res);
    printf("Found %d cds, first has ID %d\n", res, cd_res->cd_id[0]);

    res = get_cd(cd_res->cd_id[0], cd);
    printf("get_cd returned %d\n", res);

    memset(ct, 0, sizeof(CURRENT_TRACKS_ST));
    res = get_cd_track(cd_res->cd_id[0], ct);
    printf("get_cd_track returned %d\n", res);
    printf("Title: %s\n", cd->title);
    i = 0;
    while (i < res){
        printf("\ttrack %d is %s\n", i, ct->track[i]);
        i++;
    };

    res = delete_cd(cd_res->cd_id[0]);
    printf("Deleted_cd returned %d\n", res);
    database_end();
}
