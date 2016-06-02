//
// Created by Carrot on 16/6/1.
//

#include "../head/HXLMysql.h"

HXLMysql::HXLMysql() {
    _connecter = NULL;
}

HXLMysql::~HXLMysql() {
    disconnect();
}

bool HXLMysql::connect(string host, string user, string pwd, string db) {
    disconnect();
    _connecter =  mysql_init(NULL);

    bool bRes = false;
    if (_connecter){
       if (mysql_real_connect(_connecter, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), 0, NULL, 0)){
           bRes = true;
           _host = host;
           _user = user;
           _pwd = pwd;
           _dbName = db;
       }
    }
    return bRes;
}

int HXLMysql::query(string query) {
    if (!_connecter)
        return -1;
    return _connecter ? mysql_query(_connecter, query.c_str()) : -1;
}

my_ulonglong HXLMysql::affected_rows() {
    return mysql_affected_rows(_connecter);
}


void HXLMysql::disconnect(){
    if (_connecter)
        mysql_close(_connecter);
    _connecter = NULL;
}

void HXLMysql::test(){
    MYSQL* mysql = NULL;
    int res;
    mysql = mysql_init(NULL);
    if (mysql_real_connect(mysql, "localhost","hxl","123456","db_im", 0 , NULL, 0)) {
        printf("Connection success\n");
//        char* sql = "insert into children (fname, age) values ('Ann', 3)";;
        char* sql = (char*)"update children set age = 4 where fname='Ann'";
        res = mysql_query(mysql, sql);
        if (!res){
            printf("Inserted %lu rows\n", (unsigned long) mysql_affected_rows(mysql));
        } else {
            fprintf(stderr, "Insert error %d :%s", mysql_errno(mysql), mysql_error(mysql));
        }
        mysql_close(mysql);
    } else {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(mysql)){
            fprintf(stderr, "Insert error %d :%s", mysql_errno(mysql), mysql_error(mysql));
        }
    }
}

void HXLMysql::test_lastid(){
    MYSQL* mysql = NULL;
    MYSQL_RES *res_ptr;
    MYSQL_ROW sqlrow;
    int res;
    mysql = mysql_init(NULL);
    if (mysql_real_connect(mysql, "localhost","hxl","123456","db_im", 0 , NULL, 0)) {
        printf("Connection success\n");
        char* sql = (char*)"insert into children (fname, age) values ('Robert', 7)";;
//        char* sql = "update children set age = 4 where fname='Ann'";
        res = mysql_query(mysql, sql);
        if (!res){
            printf("Inserted %lu rows\n", (unsigned long) mysql_affected_rows(mysql));
        } else {
            fprintf(stderr, "Insert error %d :%s", mysql_errno(mysql), mysql_error(mysql));
        }

        sql = (char*)"select last_insert_id()";
        res = mysql_query(mysql, sql);
        if (res){
            printf("select error:%s\n", mysql_error(mysql));
        } else {
            res_ptr = mysql_use_result(mysql);
            if (res_ptr){
                while ((sqlrow = mysql_fetch_row(res_ptr))){
                    printf("We inserted childno %s\n", sqlrow[0]);
                }
                mysql_free_result(res_ptr);
            }
        }
        mysql_close(mysql);
    } else {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(mysql)){
            fprintf(stderr, "Insert error %d :%s", mysql_errno(mysql), mysql_error(mysql));
        }
    }
}

//MYSQL_RES* mysql_store_result(MYSQL* connection);
//my_ulonglong mysql_num_rows(MYSQL_RES* result);
//MYSQL_ROW mysql_fetch_row(MYSQL_RES* result);
//void mysql_data_seek(MYSQL_RES* result, my_ulonglong offset);
//MYSQL_ROW_OFFSET mysql_row_offset(MYSQL_RES* result, MYSQL_ROW_OFFSET offset);
//void mysql_free_result(MYSQL_RES* result);


void HXLMysql::test_fetch_data(){
    MYSQL* mysql;
    MYSQL_RES* res_ptr;
    MYSQL_ROW sqlrow;

    int res;
    mysql = mysql_init(NULL);
    if (mysql_real_connect(mysql, "localhost","hxl","123456","db_im", 0 , NULL, 0)) {
        printf("Connection success\n");
        char* sql = (char*)"select fname, age from children where age >=5";
        res = mysql_query(mysql, sql);
        if (res){
            printf("select error: %s\n", mysql_error(mysql));
        } else {
            res_ptr = mysql_store_result(mysql);
            if (res_ptr){
                printf("Retrieved %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));
                while ((sqlrow = mysql_fetch_row(res_ptr))){
                    printf("Fetched Data...\n");
                };

                if (mysql_errno(mysql)){
                    fprintf(stderr, "Retrieved error:%s\n", mysql_error(mysql));
                }
                mysql_free_result(res_ptr);
            }
        }
        mysql_close(mysql);
    } else {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(mysql)){
            fprintf(stderr, "Insert error %d :%s", mysql_errno(mysql), mysql_error(mysql));
        }
    }
}


//MYSQL_RES* mysql_usr_result(MYSQL* connection);
void HXLMysql::test_fetch_data2(){
    MYSQL* mysql;
    MYSQL_RES* res_ptr;
    MYSQL_ROW sqlrow;

    int res;
    mysql = mysql_init(NULL);
    if (mysql_real_connect(mysql, "localhost","hxl","123456","db_im", 0 , NULL, 0)) {
        printf("Connection success\n");
        char* sql = (char*)"select fname, age from children where age >=5";
        res = mysql_query(mysql, sql);
        if (res){
            printf("select error: %s\n", mysql_error(mysql));
        } else {
            res_ptr = mysql_use_result(mysql);
            if (res_ptr){
                // mysql_use_result() 函数没有一次获取全部数据 mysql_num_rows()等函数不可用
//                printf("Retrieved %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));
                while ((sqlrow = mysql_fetch_row(res_ptr))){
                    printf("Fetched Data...\n");
                };

                if (mysql_errno(mysql)){
                    fprintf(stderr, "Retrieved error:%s\n", mysql_error(mysql));
                }
                mysql_free_result(res_ptr);
            }
        }
        mysql_close(mysql);
    } else {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(mysql)){
            fprintf(stderr, "Insert error %d :%s", mysql_errno(mysql), mysql_error(mysql));
        }
    }
}

//unsigned int mysql_fileld_count(MYSQL* connection);
void HXLMysql::display_row(MYSQL* mysql, MYSQL_ROW sqlrow){
    unsigned int field_count = 0;

    while (field_count < mysql_field_count(mysql)){
        printf("%s ", sqlrow[field_count]);
        field_count++;
    }
    printf("\n");
}

void HXLMysql::test_fetch_data3(){
    MYSQL* mysql;
    MYSQL_RES* res_ptr;
    MYSQL_ROW sqlrow;

    int res;
    mysql = mysql_init(NULL);
    if (mysql_real_connect(mysql, "localhost","hxl","123456","db_im", 0 , NULL, 0)) {
        printf("Connection success\n");
        char* sql = (char*)"select fname, age from children where age >=5";
        res = mysql_query(mysql, sql);
        if (res){
            printf("select error: %s\n", mysql_error(mysql));
        } else {
            res_ptr = mysql_use_result(mysql);
            if (res_ptr){
                while ((sqlrow = mysql_fetch_row(res_ptr))){
                    printf("Fetched Data...\n");
                    HXLMysql::display_row(mysql, sqlrow);
                };

                if (mysql_errno(mysql)){
                    fprintf(stderr, "Retrieved error:%s\n", mysql_error(mysql));
                }
                mysql_free_result(res_ptr);
            }
        }
        mysql_close(mysql);
    } else {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(mysql)){
            fprintf(stderr, "Insert error %d :%s", mysql_errno(mysql), mysql_error(mysql));
        }
    }
}