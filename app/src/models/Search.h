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
 * @category Tatoeba wiki
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     https://github.com/sysko/tatowiki@
 */

#ifndef TATOWIKI_SEARCH
#define TATOWIKI_SEARCH

#include <cppcms_skel/models/SqliteModel.h>
#include "results/Articles.h"
namespace models {


/**
 * @class Search @TODO add a description
 * @since 18 June 2013
 *
 */
class Search : public cppcmsskel::models::SqliteModel {

    private:
        std::string content_summary(const std::string &content);

    public:
        /**
         * @brief Constructor
         * @since 18 June 2013
         */
        Search();

        /**
         * @brief Perform a search in the articles' title
         *
         * @param query The query to perform
         * @param lang  The query will be performed only on articles
         *              int that language
         *
         * @since 4 July 2013
         */
        std::string title(
            const std::string &query,
            const std::string &lang
        );


        /**
         * @brief Perform a search in the articles' content
         *
         * @param query The query to perform
         * @param lang  The query will be performed only on articles
         *              int that language
         *
         * @since 4 July 2013
         */
        results::Articles content(
            const std::string &query,
            const std::string &lang
        );


};

} // end namespace models

#endif