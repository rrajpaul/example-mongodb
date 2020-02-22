# Example-MongoDB [![Build Status](https://dev.azure.com/lganzzzo/lganzzzo/_apis/build/status/example-crud?branchName=master)](https://dev.azure.com/lganzzzo/lganzzzo/_build?definitionId=9?branchName=master)

Example project how-to create basic MongoDB CRUD endpoints and document them with Swagger-UI and OpenApi 3.0.0

See more:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)

## Overview

This project is using [oatpp](https://github.com/oatpp/oatpp) and [oatpp-swagger](https://github.com/oatpp/oatpp-swagger) modules.

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- src/
|   |
|   |- controller/                       // Folder containing UserController where all endpoints are declared
|   |- db/                               // Folder with database mock
|   |- dto/                              // DTOs are declared here
|   |- SwaggerComponent.hpp              // Swagger-UI config
|   |- AppComponent.hpp                  // Service config
|   |- App.cpp                           // main() is here
|
|- test/                                 // test folder
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.
```

---

### Build and Run

#### Using CMake

**Requires**

- `oatpp` and `oatpp-swagger` and `bsoncxx` and `mongocxx` modules installed. You may run `utility/install-oatpp-modules.sh` 
script to install required oatpp modules.

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./example-mongo-exe        # - run application.
```

#### In Docker

```
$ docker build -t example-mongodb .
$ docker run -p 8000:8000 -t example-mongodb
```

---

### Endpoints declaration

#### Create User

```c++
ENDPOINT_INFO(createUser) {
  info->summary = "Create new User";
  info->addConsumes<UserDto::ObjectWrapper>("application/json");
  info->addResponse<UserDto::ObjectWrapper>(Status::CODE_200, "application/json");
}
ENDPOINT("POST", "demo/api/Users", createUser,
         BODY_DTO(UserDto::ObjectWrapper, UserDto)) {
  return createDtoResponse(Status::CODE_200, m_database->createUser(UserDto));
}
```

#### Update User

```c++
ENDPOINT_INFO(putUser) {
  info->summary = "Update User by UserId";
  info->addConsumes<UserDto::ObjectWrapper>("application/json");
  info->addResponse<UserDto::ObjectWrapper>(Status::CODE_200, "application/json");
  info->addResponse<String>(Status::CODE_404, "text/plain");
}
ENDPOINT("PUT", "demo/api/Users/{UserId}", putUser,
         PATH(Int32, UserId),
         BODY_DTO(UserDto::ObjectWrapper, UserDto)) {
  UserDto->id = UserId;
  return createDtoResponse(Status::CODE_200, m_database->updateUser(UserDto));
}
```

#### Get one User

```c++
ENDPOINT_INFO(getUserById) {
  info->summary = "Get one User by UserId";
  info->addResponse<UserDto::ObjectWrapper>(Status::CODE_200, "application/json");
  info->addResponse<String>(Status::CODE_404, "text/plain");
}
ENDPOINT("GET", "demo/api/Users/{UserId}", getUserById,
         PATH(Int32, UserId)) {
  auto User = m_database->getUserById(UserId);
  OATPP_ASSERT_HTTP(User, Status::CODE_404, "User not found");
  return createDtoResponse(Status::CODE_200, User);
}
```

#### Get list of Users

```c++
ENDPOINT_INFO(getUsers) {
  info->summary = "get all stored Users";
  info->addResponse<List<UserDto::ObjectWrapper>::ObjectWrapper>(Status::CODE_200, "application/json");
}
ENDPOINT("GET", "demo/api/Users", getUsers) {
  return createDtoResponse(Status::CODE_200, m_database->getUsers());
}
```

#### Delete User
```c++
ENDPOINT_INFO(deleteUser) {
  info->summary = "Delete User by UserId";
  info->addResponse<String>(Status::CODE_200, "text/plain");
  info->addResponse<String>(Status::CODE_404, "text/plain");
}
ENDPOINT("DELETE", "demo/api/Users/{UserId}", deleteUser,
         PATH(Int32, UserId)) {
  bool success = m_database->deleteUser(UserId);
  OATPP_ASSERT_HTTP(success, Status::CODE_417, "User not deleted. Perhaps no such User in the Database");
  return createResponse(Status::CODE_200, "User successfully deleted");
}  
```
