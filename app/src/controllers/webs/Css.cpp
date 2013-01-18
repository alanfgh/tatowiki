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

#include <fstream>

#include <cppcms/session_interface.h>
#include <cppcms_skel/generics/Config.h>
#include "Css.h"


#include "contents/Css.h"

//%%%NEXT_INC_MODEL_CTRL_MARKER%%%


namespace controllers {
namespace webs {

Css::Css(cppcms::service& serv) :
    controllers::webs::Controller(serv)
{
    dispatcher().assign("/([a-z_0-9/\\.]+.css)[0-9]*", &Css::serve_file, this, 1);


    //%%%NEXT_ACTION_DISPATCHER_MARKER%%%, do not delete

    //%%%NEXT_NEW_MODEL_CTRL_MARKER%%%
}


void Css::serve_file(std::string cssFile) {
    std::string absolutePath = Config::get_inner_css_folder() + cssFile;
    std::ifstream file(
        absolutePath.c_str()
    );  
    if(!file.good()) {  
       response().status(404);
       response().out() << "404";
    }  
    else {  
        response().content_type("text/css");
        response().out() << file.rdbuf();  
    }  

    file.close();
}


/**
 *
 */
Css::~Css() {
    //%%%NEXT_DEL_MODEL_CTRL_MARKER%%%
}

// %%%NEXT_ACTION_MARKER%%% , do not delete




} // End namespace webs
} // End namespace controllers