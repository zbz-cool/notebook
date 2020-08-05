/*
https://github.com/p-ranav/argparse
*/
#include "argparse.hpp"

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program("program name");

    program.add_argument("square").help("display the square of a given integer");
    program.add_argument("--verbose").help("increase output verbosity").default_value(false);
    program.add_argument("--zbz").help("increase output verbosity").default_value(true).implicit_value(false);

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    auto input = program.get<std::string>("square");
    std::cout << (input) << std::endl;

    return 0;
}
