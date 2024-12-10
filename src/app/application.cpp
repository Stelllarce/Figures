#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include "../figurelib/input_type_factory.hpp"

/**
 * @brief Prints figures to stdout
 */
void print_to_out(const std::vector<std::unique_ptr<Figure>>& figures) {
    for (const auto& fig : figures) {
        std::cout << fig->to_str() << '\n';
    }
}

/**
 * @brief Saves figures to a file
 */
void print_to_file(const std::vector<std::unique_ptr<Figure>>& figures) {
    std::string file_path;
    std::cout << "Enter the file path: ";
    std::cin >> file_path;
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cout << "File not found. Please try again\n";
        return;
    }
    for (const auto& fig : figures) {
        file << fig->to_str() << '\n';
    }
    file.close();
}

/**
 * @brief Shows perimeters of figures to stdout
 */
void show_perimeters(const std::vector<std::unique_ptr<Figure>>& figures) {
    for (const auto& fig : figures) {
        std::cout << fig->perimeter() << '\n';
    }
}

/**
 * @brief Clones figures and prints them to stdout
 */
void clone_figures(std::vector<std::unique_ptr<Figure>>& figures) {
    std::vector<std::unique_ptr<Figure>> clones;
    for (const auto& fig : figures) {
        clones.push_back(fig->clone());
    }
    std::cout << "Figures cloned successfully\n";
    for (const auto& fig: clones) {
        std::cout << fig->to_str() << '\n';
    }
}

/**
 * @brief Lists figures to stdout
 */
void list_figures(const std::vector<std::unique_ptr<Figure>>& figures) {
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << i << ": " << figures[i]->to_str() << '\n';
    }
}

/**
 * @brief Deletes a figure from the list
 */
void delete_figure(std::vector<std::unique_ptr<Figure>>& figures) {
    size_t index;
    std::cout << "Enter the index of the figure to delete: ";
    std::cin >> index;
    if (index < figures.size()) {
        figures.erase(figures.begin() + index);
        std::cout << "Figure deleted successfully\n";
    } else {
        std::cout << "Invalid index\n";
    }
}

/**
 * @brief Reads figures from the input stream
 */
void read_figures(std::vector<std::unique_ptr<Figure>>& figures, std::unique_ptr<FigureFactory>& factory, int figure_count) {
    for (int i = 0; i < figure_count; i++) {
        try {
            std::unique_ptr<Figure> fig = factory->create_figure();
            std::cout << fig->to_str() << " read successfully" << '\n';
            figures.push_back(std::move(fig));
        } catch (std::ios_base::failure &ioe) {
            std::cout << ioe.what() << '\n';
            return;
        } catch (std::runtime_error &e) {
            std::cerr << "Invalid figure\n";
            std::cout << e.what() << '\n';
            continue;
        } catch (std::invalid_argument &e) {
            std::cerr << "Invalid figure\n";
            std::cout << e.what() << '\n';
            continue;
        }
    }
}

void format_input(std::string& input, const int figure_count) {
    std::string line;
    if (input == "stream") {
        for (unsigned i = 0; i < figure_count; ++i) {
            std::getline(std::cin, line);
            input += line + '\n';
        }
        input.pop_back(); // remove trailing newline
    } else if (input == "file") {
        std::cin >> line;
        input += ' ' + line;
    }
}

void init() {
    std::cout << "Program active" << '\n';
    std::string input;
    InputTypeFactory input_factory;
    std::unique_ptr<FigureFactory> factory;
    std::vector<std::unique_ptr<Figure>> figures;
    std::ifstream file;
    int figure_count;   
    while (true) {
        // TODO: handle input not being a number
        do {
            std::cout << "Enter the number of figures: ";
            std::cin >> figure_count;
        } while (figure_count <= 0);

        std::cout << "If the used method is either stdin or file then type:\n"
                        "for case stdin: stream <figure1>\n<figure2> ...\n"
                        "for case file: file <file_path>\n";
        std::cout << "Enter the preferred input method (random, stream, file), followed by " << figure_count << " figures: ";
        std::cin >> input;

        // Format the string to pass to the factory
        format_input(input, figure_count);

        try {
            factory = input_factory.create_factory(input);
        } catch(const std::invalid_argument& e) {
            std::cerr << e.what() << '\n';
            std::cout << "Restarting..\n";
            continue;
        }
        break;
    }
    
    read_figures(figures, factory, figure_count);

    std::map<std::string, std::function<void(std::vector<std::unique_ptr<Figure>>&)> > operations = {
        {"printo", print_to_out},
        {"printf", print_to_file},
        {"perimeter", show_perimeters},
        {"clone", clone_figures},
        {"list", list_figures},
        {"delete", delete_figure}
    };

    std::string operation;
    while (true) {
        std::cout << "Enter the operation (printo, printf, perimeter, clone, list, delete, exit): ";
        std::cin >> operation;
        if (operation == "exit") {
            std::cout << "Exiting program" << std::endl;
            break;
        } else if (operations.find(operation) != operations.end()) {
            operations[operation](figures);
        } else {
            std::cout << "Invalid operation" << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    init();
    return 0;
}