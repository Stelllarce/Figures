# Sample static library
add_library(figurelib STATIC)

set_target_properties(figurelib PROPERTIES OUTPUT_NAME "figlib")

target_sources(
    figurelib
    PRIVATE
        "figure.hpp"
        "triangle.hpp"
        "triangle.cpp"
        "circle.hpp"
        "circle.cpp"
        "string_convertible.hpp"
        "rectangle.hpp"
        "rectangle.cpp"
        "string_to_figure_converter.hpp"
        "string_to_figure_converter.cpp"
        "figure_factory.hpp"
        "random_figure_factory.hpp"
        "random_figure_factory.cpp"
        "stream_figure_factory.hpp"
        "stream_figure_factory.cpp"
        "input_type_factory.hpp"
        "input_type_factory.cpp"
        "abstract_factory.hpp"
)