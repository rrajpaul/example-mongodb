//
// Created by Leonid on 2019-06-06.
//

#ifndef MyApiTestClient_hpp
#define MyApiTestClient_hpp

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class MyApiTestClient : public oatpp::web::client::ApiClient {

  API_CLIENT_INIT(MyApiTestClient)

  // API for createUser
  API_CALL("POST", "demo/api/users", createUser)

  // API for updateUser
  API_CALL("PUT", "demo/api/users/{userId}", updateUser)

  // API for getUserById
  API_CALL("GET", "demo/api/users/{userId}", getUserById)

  // API for getUsers
  API_CALL("GET", "demo/api/users", getUsers)

  // API for deleteUser
  API_CALL("DELETE", "demo/api/users/{userId}", deleteUser)

};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif // MyApiTestClient_hpp
