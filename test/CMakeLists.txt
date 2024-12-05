# Executable target for the unit tests
add_executable(unit-tests)

target_link_libraries(
    unit-tests
    PRIVATE
        figurelib
        Catch2::Catch2WithMain
)

target_sources(
    unit-tests
    PRIVATE
        "test-circle.cpp"
        "test-rectangle.cpp"
        "test-triangle.cpp"
        "test-string-figure-factory.cpp"
        # "test-factories.cpp"
)

# Automatically register all tests
catch_discover_tests(unit-tests)
