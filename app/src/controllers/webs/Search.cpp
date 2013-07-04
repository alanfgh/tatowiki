/**
* Tatoeba wiki  Wiki made with cppcmsskel
* Copyright (C) 2012 Allan SIMON <allan.simon@supinfo.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*
* @category Tatoeba wiki
* @package  Controllers
* @author   Allan SIMON <allan.simon@supinfo.com>
* @license  Affero General Public License
* @link     https://github.com/sysko/tatowiki@
*/

#include <cppcms/session_interface.h>
#include "Search.h"
#include "contents/Search.h"

#include "models/Search.h"
#include "generics/Config.h"
#include "generics/markdown.h"
//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

Search::Search(cppcms::service&serv) :
controllers::webs::Controller(serv)
{


    dispatcher().assign("/simple", &Search::simple, this);
    dispatcher().assign("/result", &Search::result, this);
    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete


    searchModel = new models::Search();
    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}

/**
*
*/
Search::~Search(){
    delete searchModel;
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
}

/**
 *
 */
void Search::simple() {

    contents::search::Simple c;
    init_content(c);


    render("search_simple", c);
}


/**
 *
 */
void Search::result() {

    contents::search::Result c;
    init_content(c);

    const std::string query = request().get("query");

    if (query.empty()) {
        go_back_to_previous_page();
        return;
    }

    const std::string slug = searchModel->title(query,c.lang);
    if (!slug.empty()) {
        redirect(
            tatowiki::Config::articles_url_from_lang_and_slug(
                c.lang,
                slug
            )
        );
        return;
    }

    c.markdown = mymarkdown;
    c.query = query;
    c.articles = searchModel->content(query,c.lang);


    render("search_result", c);
}

// %%%NEXT_ACTION_MARKER%%% , do not delete




}// End namespace webs
}// End namespace controllers