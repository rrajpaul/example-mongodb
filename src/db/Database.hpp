//
//  Database.hpp
//  crud
//
//  Created by Leonid on 3/13/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include "../dto/UserDto.hpp"
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <string>
#include "oatpp/core/Types.hpp"
#include "oatpp-mongocxxmapper/ObjectMapper.hpp"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::finalize;

const std::string TAG = "Mongodb example ";
const std::string DB_HOST = "localhost:27017";
const std::string DB_USER = "userAdmin";
const std::string DB_PASSWORD = "oatpp-example_1";
const std::string DB_NAME = "oatpp_example";
const std::string COLLECTION_NAME = "user_example";

/**
 *  Simple MongoDB Database.
 *  For demo purposes only :)
 */
class Database {
private:
  std::shared_ptr<oatpp::parser::mongocxx::mapping::ObjectMapper> m_mongomapper;
  mongocxx::client m_client;
  mongocxx::database m_db;
	mongocxx::collection m_collection;
  v_int32 getMaxId();
public:  
  Database() {
      std::string connString;
      connString =  "mongodb://" + DB_USER + ":" + DB_PASSWORD + "@" + DB_HOST;
      m_client = mongocxx::client{mongocxx::uri{connString}};
      m_db = m_client[DB_NAME];
      m_collection = m_db[COLLECTION_NAME];

      m_mongomapper =  oatpp::parser::mongocxx::mapping::ObjectMapper::createShared();
  }
  
  UserDto::ObjectWrapper createUser(const UserDto::ObjectWrapper& userDto);
  UserDto::ObjectWrapper updateUser(const UserDto::ObjectWrapper& userDto);
  UserDto::ObjectWrapper getUserById(v_int32 id);
  oatpp::data::mapping::type::List<UserDto::ObjectWrapper>::ObjectWrapper getUsers();
  bool deleteUser(v_int32 id);
  
};

#endif /* Database_hpp */
