#include <cstdio>
#include <iostream>

#include <bsoncxx/array/view.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using namespace std;

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

int main()
{

    mongocxx::instance inst{};
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

    return 0;
}
