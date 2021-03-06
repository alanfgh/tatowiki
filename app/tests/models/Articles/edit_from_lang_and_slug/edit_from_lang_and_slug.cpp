#include <iostream>
#include "models/Articles.h"
#include <cppcms_skel/generics/test.h>

#define TEST_NAME "models_edit_from_lang_and_slug_test"
#define DB_SQL_FILE_PATH  "../sql/sqlite3.sql"

#define TEST_ARTICLE_ID  1
#define TEST_ARTICLE_LANG "fr"
#define TEST_ARTICLE_SLUG "page_principale"
#define TEST_ARTICLE_TITLE "Page Principale"
#define TEST_ARTICLE_CONTENT u8"Juste pour voir si ça marche"

#define TEST_ARTICLE_NEW_TITLE "New Page Principale"
#define TEST_ARTICLE_NEW_CONTENT u8"New New New New New"


int main() {


    bool noTestFailed = true;
    models::Articles articlesModels(TEST_NAME ".db");

    CPPCMSSKEL_TEST_RESULT_WORK(
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
    if (result == TEST_ARTICLE_ID) {
        std::cout << " [ok]" << std::endl;
    } else {
        std::cout << " [fail]" << std::endl;
        noTestFailed = false;
    }

    // try to add the same article should fail

    std::cout << "Adding the same article twice should be forbidden ... " ;

    result = articlesModels.create_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG,
        TEST_ARTICLE_TITLE,
        TEST_ARTICLE_CONTENT
    );
    if (result == ARTICLE_CREATION_ERROR) {
        std::cout << " [ok]" << std::endl;
    } else {
        std::cout << " [fail]" << std::endl;
        noTestFailed = false;
    }

    // try to retrieve the article we have added
    
    
    // now we check if we can retrieve them

    std::cout << "We now test if we can get it back ... ";
    results::Article firstArticle = articlesModels.get_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG
    );
    if ( 
        (firstArticle.id != TEST_ARTICLE_ID) ||
        (firstArticle.lang.compare(TEST_ARTICLE_LANG) != 0) ||
        (firstArticle.slug.compare(TEST_ARTICLE_SLUG) != 0) ||
        (firstArticle.title.compare(TEST_ARTICLE_TITLE) != 0) ||
        (firstArticle.content.compare(TEST_ARTICLE_CONTENT) != 0)
    ) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }

    //now we try to edit the article
    std::cout << "We now test if we can edit it ... ";
    bool requestSuccess = articlesModels.edit_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG,
        TEST_ARTICLE_NEW_TITLE,
        TEST_ARTICLE_NEW_CONTENT
    );

    if(!requestSuccess) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }


    // if we try to get back the article, we shoud get the edited version
    std::cout << "The article should have been modfied ... ";
    results::Article editedArticle = articlesModels.get_from_lang_and_slug(
        TEST_ARTICLE_LANG,
        TEST_ARTICLE_SLUG
    );

    if(
        editedArticle.id != TEST_ARTICLE_ID ||
        editedArticle.content.compare(TEST_ARTICLE_NEW_CONTENT) != 0 ||
        editedArticle.title.compare(TEST_ARTICLE_NEW_TITLE) != 0
    ) {
        noTestFailed = false;
        std::cout << " [fail]" << std::endl; 
    
    } else {
        std::cout << " [ok]" << std::endl; 
    }



    
 
    if (noTestFailed) {
        return 0;
    } else {
        return 1;
    }



}
