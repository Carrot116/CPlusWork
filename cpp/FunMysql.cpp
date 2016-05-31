//
// Created by Carrot on 16/5/31.
//

#include "../head/FunMysql.h"
#include <stdio.h>

void connect2mysql(){
    MYSQL* mysql = mysql_init(NULL);

    if (!mysql){
        fprintf(stderr, "error: %s",mysql_error(mysql));
        fprintf(stderr,"mysql_init faild\n");
        return;
    }

    mysql = mysql_real_connect(mysql, "192.168.1.105", "hxl","123456","db_im",0, NULL,0);

    if (!mysql){
        fprintf(stderr, "error: %s",mysql_error(mysql));
        printf("Connecting success!\n");
    } else {
        printf("Connecting fail!\n");
    }
}
