cmake_minimum_required(VERSION 3.12)
project(armai CXX)


# Adding userver dependency
find_package(userver COMPONENTS core postgresql QUIET)
if(NOT userver_FOUND)  # Fallback to subdirectory usage
    # Enable userver libraries that are needed in this project
    set(USERVER_FEATURE_POSTGRESQL ON CACHE BOOL "" FORCE)

    # Compatibility mode: some systems don't support these features
    set(USERVER_FEATURE_CRYPTOPP_BLAKE2 OFF CACHE BOOL "" FORCE)
    set(USERVER_FEATURE_GRPC_CHANNELZ OFF CACHE BOOL "" FORCE)
    set(USERVER_FEATURE_REDIS_HI_MALLOC ON CACHE BOOL "" FORCE)

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/userver)
        message(STATUS "Using userver framework from third_party/userver")
        add_subdirectory(third_party/userver)
    else()
        message(FATAL_ERROR "Either install the userver or provide a path to it")
    endif()
endif()

userver_setup_environment()


# Common sources
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
)
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")
add_library(${PROJECT_NAME}_objs OBJECT ${PROJECT_SOURCES})
# add_library(${PROJECT_NAME}_objs OBJECT
#     src/hello.hpp
#     src/hello.cpp


#     src/application/handlers/appendHandlers.hpp
#     src/application/handlers/appendHandlers.cpp
#     src/application/handlers/users/register/view.hpp
#     src/application/handlers/users/register/view.cpp
#     src/application/handlers/users/auth/view.hpp
#     src/application/handlers/users/auth/view.cpp
#     src/application/handlers/users/logout/view.hpp
#     src/application/handlers/users/logout/view.cpp
#     src/application/handlers/users/me/view.hpp
#     src/application/handlers/users/me/view.cpp
#     src/application/handlers/users/id/view.hpp
#     src/application/handlers/users/id/view.cpp

#     src/application/utils/auth.hpp
#     src/application/utils/auth.cpp
    
#     src/application/dto/users/userRegisterCommand.hpp
#     src/application/dto/users/userAuthCommand.hpp

#     src/application/mappers/users/request/userRegisterCommand.hpp
#     src/application/mappers/users/request/userRegisterCommand.cpp
#     src/application/mappers/users/request/userAuthCommand.hpp
#     src/application/mappers/users/request/userAuthCommand.cpp
#     src/application/mappers/users/json/user.hpp
#     src/application/mappers/users/json/user.cpp
#     src/application/mappers/users/json/userQuery.hpp
#     src/application/mappers/users/json/userQuery.cpp
#     src/application/mappers/users/userDomainQuery.hpp
#     src/application/mappers/users/userDomainQuery.cpp

    
#     src/infrastructure/repositories/users/userRepository.hpp
#     src/infrastructure/repositories/users/userRepository.cpp
#     src/infrastructure/repositories/users/userRepositoryPostgres.hpp
#     src/infrastructure/repositories/users/userRepositoryPostgres.cpp
    
#     src/infrastructure/components/repositories/appendRepositories.hpp
#     src/infrastructure/components/repositories/appendRepositories.cpp
#     src/infrastructure/components/repositories/userRepositoryComponent.hpp
#     src/infrastructure/components/repositories/userRepositoryComponent.cpp
    
#     src/infrastructure/queries/users/usersRead.hpp
#     src/infrastructure/queries/users/usersCreate.hpp

#     src/infrastructure/mappers/users/parameterStore/usersCreate.hpp
#     src/infrastructure/mappers/users/parameterStore/usersCreate.cpp
#     src/infrastructure/mappers/postgres/sex.hpp


#     src/domain/users/user.hpp
#     src/domain/users/users.hpp

#     src/domain/utils/auth.hpp
#     src/domain/utils/auth.cpp
#     src/domain/utils/jwt.hpp
#     src/domain/utils/jwt.cpp
# )
target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver::postgresql)


# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
# add_executable(${PROJECT_NAME}_unittest
#     src/hello_test.cpp
# )
# target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs userver::utest)
# add_google_tests(${PROJECT_NAME}_unittest)


# Benchmarks
# add_executable(${PROJECT_NAME}_benchmark
#     src/hello_benchmark.cpp
# )
# target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME}_objs userver::ubench)
# add_google_benchmark_tests(${PROJECT_NAME}_benchmark)

# Functional testing
userver_testsuite_add_simple()

# Install
include(GNUInstallDirs)

if(DEFINED ENV{PREFIX})
  message(STATUS "Set install prefix: $ENV{PREFIX}")
  file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
  set(CMAKE_INSTALL_PREFIX "${PREFIX_PATH}")
endif()

file(GLOB CONFIGS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.yaml ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})

# jwt-cpp
add_subdirectory(third_party/jwt-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE jwt-cpp)
include_directories(third_party/jwt-cpp/include)

# picojson
# add_subdirectory(third_party/picojson)
# target_link_libraries(${PROJECT_NAME} PRIVATE picojson)
# include_directories(third_party/picojson)

# include src
include_directories(src)
