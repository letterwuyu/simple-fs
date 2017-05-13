#include <cstdio>
#include <iostream>

#include <bsoncxx/array/view.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/v_noabi/bsoncxx/builder/stream/helpers.hpp>

using namespace std;

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
int main()
{

/*    mongocxx::instance inst{};
    mongocxx::client conn{ mongocxx::uri{} };
    auto collection = conn["DbName"]["CollectionName"];
    auto result = collection.find_one(document{} << "_id" << "Id" << finalize);
    auto doc = *result;
    auto view = doc.view();
    //似乎一个view只能一次使用view["abc"]
    //否则会crash
    //auto enableView = view["Enable"];
    //auto enable = enableView.get_bool().value;
    auto accountsView = view["Accounts"];
    auto accounts = accountsView.get_array().value;
    for (auto acc : accounts)
    {
        auto v = acc.get_value();
        auto tp = v.type();
        if (tp == bsoncxx::type::k_utf8)
        {           
            auto str = v.get_utf8().value.to_string();          
            cout << str << endl;
        }
    }
	
  //  return 0;
  */
mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
 
    bsoncxx::builder::stream::document document{};
 
    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";
 
    collection.insert_one(document.view());
    auto cursor = collection.find({});
	
/*	bsoncxx::builder::stream::document filter_builder;
        filter_builder << "hello"
                       << "world";
	collection.delete_one(filter_builder.view()); 
*/
	  bsoncxx::builder::stream::document filter_builder, update_builder;
        filter_builder << "hello"
                       << "world";
        update_builder << "$set" << open_document << "cuisine"
                       << "American (New)" << close_document << "$currentDate" << open_document
                       << "lastModified" << true << close_document;

        collection.update_one(filter_builder.view(), update_builder.view());

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
	}
}
