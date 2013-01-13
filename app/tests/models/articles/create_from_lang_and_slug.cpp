#include <iostream>
#include "models/Articles.h"
#include "test.h"

#define TEST_NAME "models_create_from_lang_and_slug_test"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"

#define TEST_ARTICLE_LANG "fr"
#define TEST_ARTICLE_SLUG "page_principale"
#define TEST_ARTICLE_TITLE "Page Principale"
#define TEST_ARTICLE_CONTENT u8"Juste pour voir si ça marche"



int main() {


    bool noTestFailed = true;
    models::Articles articlesModels(TEST_NAME ".db");

    TEST_RESULT_SHOULD_WORK(
        "Try load the database ... " ,
        articlesModels.import_sql_file(DB_SQL_FILE_PATH),
        noTestFailed
    );
    
    // we should be able to add an article ...

    std::cout << "Try to add an article ... " ;

    int result = articlesModels.create_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG,
        TEST_ARTICLE_TITLE,
        TEST_ARTICLE_CONTENT
    );
    if (result == 1) {
        std::cout << " [ok]" << std::endl;
    } else {
        std::cout << " [fail]" << std::endl;
        noTestFailed = false;
    }
    
    
 
    if (noTestFailed) {
        return 0;
    } else {
        return 1;
    }



}
