#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // For fork() and exec()
#include <sys/types.h>
#include <sys/wait.h>

void printPrompt() {
    std::cout << "simple-shell> ";
}

std::vector<std::string> parseInput(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    
    while (tokenStream >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

int main() {
    std::string input;

    while (true) {
        printPrompt();
        std::getline(std::cin, input);

        // Exit the shell if the user types "exit"
        if (input == "exit") {
            std::cout << "Exiting the shell. Goodbye!\n";
            break;
        }

        // Parse the input into command and arguments
        std::vector<std::string> args = parseInput(input);
        if (args.empty()) {
            continue; // Skip empty input
        }

        // Create a child process
        pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Failed to fork process.\n";
            continue;
        } else if (pid == 0) {
            // In child process
            char* argv[args.size() + 1];
            for (size_t i = 0; i < args.size(); ++i) {
                argv[i] = const_cast<char*>(args[i].c_str());
            }
            argv[args.size()] = nullptr; // Null-terminate the array

            // Execute the command
            if (execvp(argv[0], argv) == -1) {
                std::cerr << "Command not found: " << argv[0] << "\n";
                exit(1);
            }
        } else {
            // In parent process
            int status;
            waitpid(pid, &status, 0); // Wait for the child process to finish
        }
    }

    return 0;
}
