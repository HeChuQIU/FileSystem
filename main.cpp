#include <iostream>
#include <sstream>

#include <vector>
#include <string>
#include <iterator>

#include "CLI/CLI.hpp"

std::pair<int, char **> parseStringToArgv(const std::string &str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

    int argc = tokens.size(); // NOLINT(*-narrowing-conversions)
    char **argv = new char *[argc];

    for (int i = 0; i < argc; ++i) {
        argv[i] = new char[tokens[i].size() + 1];
        std::strcpy(argv[i], tokens[i].c_str());
    }

    return {argc, argv};
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

int main(int argc, char **argv) {
    CLI::App app;

    auto recursion_flag = app.add_flag("--recursion", "Recursion call flag");

    auto echo_command = app.add_subcommand("echo", "Prints arguments");
    std::string message;
    echo_command->add_option("message", message, "Message to print")->required();
    echo_command->callback([&]() { std::cout << "ECHO: " << message << std::endl; });

    auto split_command = app.add_subcommand("split", "Splits a string");
    std::string str;
    char delimiter;
    split_command->add_option("str", str, "String to split")->required();
    split_command->add_option("--de", delimiter, "Delimiter to split by")->required();
    split_command->callback([&]() {
        auto tokens = split(str, delimiter);

        std::cout << "SPLIT: ";
        for (const auto &token: tokens) {
            std::cout << token << " ";
        }
        std::cout << std::endl;
    });

    auto exit_command = app.add_subcommand("exit", "Exits the program");
    exit_command->callback([&]() {
        std::cout << "EXIT" << std::endl;
        exit(0);
    });

    CLI11_PARSE(app, argc, argv)

    bool recursion = recursion_flag->count() > 0;

    auto subs = app.get_subcommands();

    if (recursion && argc == 2) {
        std::cout << "No command provided" << std::endl;
        return 0;
    }

    if (!subs.empty()) {
        std::cout << "Subcommands: " << std::endl;
        for (const auto &sub: subs) {
            std::cout << "  " << sub->get_name() << ": " << sub->get_description() << std::endl;
        }
        return 0;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        std::ostringstream command;

        std::cout << "Enter Command: " << std::endl;
        std::string input;
        std::getline(std::cin, input);

        command << std::string(argv[0]) << " --recursion " << input;

        auto [new_argc, new_argv] = parseStringToArgv(command.str());

        main(new_argc, new_argv);
    }
#pragma clang diagnostic pop
}

#pragma clang diagnostic pop
