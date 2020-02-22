//
//  Database.cpp
//  crud
//
//  Created by Leonid on 3/13/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#include "Database.hpp"

v_int32 Database::getMaxId(){
  bsoncxx::builder::stream::document sort_doc{};
  sort_doc << "id" << -1 ;

  mongocxx::options::find opts;
  opts.sort(sort_doc.view()).limit(1);

  auto cursor = m_collection.find({}, opts);
  return std::distance(cursor.begin(), cursor.end());
}

UserDto::ObjectWrapper Database::createUser(const UserDto::ObjectWrapper& userDto){
  auto mongoStyle = m_mongomapper->writeAsDocument(userDto);
  auto result = m_collection.insert_one(mongoStyle.view());

  auto resultUser = UserDto::ObjectWrapper();

  if(result) {
    OATPP_LOGD(TAG, "Inserted  (%llu) with id %s", 
                    userDto->id->getValue(), 
                    result->inserted_id().get_oid().value.to_string().c_str());

    auto insertedStyle = getUserById(userDto->id);                            
    return  resultUser = userDto;
  }

  return resultUser;
}

UserDto::ObjectWrapper Database::updateUser(const UserDto::ObjectWrapper& userDto){
  auto foundUser = getUserById(userDto->id);
  auto resultUser = UserDto::ObjectWrapper();
              
  if(foundUser->id->getValue() == userDto->id->getValue()) {    
    auto mongoStyle = m_mongomapper->writeAsDocument(userDto);
    auto mongoFound = m_mongomapper->writeAsDocument(foundUser);
    auto result =   m_collection.replace_one(mongoFound.view(), mongoStyle.view());

    if(result->modified_count() > 0) {
          OATPP_LOGD(TAG, "Update user with id: (%llu) ",  userDto->id->getValue());
          resultUser = userDto;
    }
  }

  return resultUser;
}

UserDto::ObjectWrapper Database::getUserById(v_int32 id){
    auto user = UserDto::ObjectWrapper();    
    auto result = m_collection.find_one({document{} << "id" << id << finalize});
    
    if(result) {
        auto docView = result->view();
        user = m_mongomapper->readFromDocument<UserDto::ObjectWrapper>(docView);

        OATPP_LOGD(TAG, "Found style with id %d", user->id->getValue()); 
    }

    return user;
}

oatpp::data::mapping::type::List<UserDto::ObjectWrapper>::ObjectWrapper Database::getUsers(){
  auto cursor = m_collection.find({});
  auto listDocs = oatpp::data::mapping::type::List<UserDto::ObjectWrapper>::createShared();

  for(auto doc : cursor) {        
      listDocs->pushBack(m_mongomapper->readFromDocument<UserDto::ObjectWrapper>(doc));
  }

  return listDocs;
}

bool Database::deleteUser(v_int32 id){
  auto result = m_collection.delete_one(document{} << "id" << id << finalize);

  if(result) {
      return true;
  }

  return false;
}
