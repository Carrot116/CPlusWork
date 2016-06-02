//
// Created by Carrot on 16/5/31.
//

#include "../head/FunMysql.h"
#include <stdio.h>
#include <cstring>

#include "../head/HXLMysql.h"

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
    HXLMysql::test_fetch_data3();
}

