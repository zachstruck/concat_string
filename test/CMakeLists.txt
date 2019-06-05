if(BUILD_TESTING)
    add_executable(tests
        concat_string_test.cpp
        main.cpp
    )

    find_package(Catch2 CONFIG REQUIRED)

    target_link_libraries(tests
        PRIVATE
            Catch2::Catch2
            libconcat_string
    )

    include(CTest)
    include(Catch)
    catch_discover_tests(tests)
endif(BUILD_TESTING)
