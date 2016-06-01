//
// Created by Carrot on 16/5/31.
//

#include "../head/FunMysql.h"
#include <stdio.h>
#include <cstring>

void connect2mysql(){
    fprintf(stderr, "\nmysql version:%lu\n", mysql_get_client_version());
    MYSQL* mysql = mysql_init(NULL);

    if (!mysql){
        fprintf(stderr, "\nerror: %s",mysql_error(mysql));
        fprintf(stderr,"\nmysql_init faild\n");
        return;
    }

    mysql = mysql_real_connect(mysql, "127.0.0.1", "hxl","123456","db_im",0, NULL,0);

    if (mysql){
        printf("\nConnecting success!\n");
    } else {
        fprintf(stderr, "error: %s",mysql_error(mysql));
        printf("\nConnecting fail!\n");
    }
    mysql_close(mysql);
}
