// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "catch.hpp"
#include "helpers.hpp"

#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/result/update.hpp>

TEST_CASE("update", "[update][result]") {
    mongocxx::instance::current();

    bsoncxx::builder::stream::document build;
    build << "_id" << bsoncxx::oid{} << "nMatched" << bsoncxx::types::b_int32{2} << "nModified"
          << bsoncxx::types::b_int32{1};

    mongocxx::result::bulk_write b(bsoncxx::document::value(build.view()));

    mongocxx::result::update update(std::move(b));

    SECTION("returns correct matched and modified count") {
        REQUIRE(update.matched_count() == 2);
        REQUIRE(update.modified_count() == 1);
    }
}
