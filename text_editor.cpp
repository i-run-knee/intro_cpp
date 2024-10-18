#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void displayMenu() {
    std::cout << "\nSimple Text Editor Menu:\n";
    std::cout << "1. Create a new file\n";
    std::cout << "2. Open an existing file\n";
    std::cout << "3. Save the current document\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

void createFile(std::vector<std::string>& lines) {
    std::cout << "Creating a new file. Type your text (type 'END' to finish):\n";
    std::string line;
    lines.clear(); // Clear previous content

    while (true) {
        std::getline(std::cin, line);
        if (line == "END") break;
        lines.push_back(line);
    }
}

void openFile(std::vector<std::string>& lines) {
    std::string filename;
    std::cout << "Enter the filename to open: ";
    std::cin >> filename;
    std::cin.ignore(); // Clear the input buffer

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file.\n";
        return;
    }

    lines.clear();
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    std::cout << "File opened successfully.\n";
}

void saveFile(const std::vector<std::string>& lines) {
    std::string filename;
    std::cout << "Enter the filename to save: ";
    std::cin >> filename;
    std::cin.ignore(); // Clear the input buffer

    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error creating file.\n";
        return;
    }

    for (const auto& line : lines) {
        file << line << '\n';
    }
    file.close();
    std::cout << "File saved successfully.\n";
}

int main() {
    std::vector<std::string> lines;
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1:
                createFile(lines);
                break;
            case 2:
                openFile(lines);
                if (!lines.empty()) {
                    std::cout << "File contents:\n";
                    for (const auto& line : lines) {
                        std::cout << line << '\n';
                    }
                }
                break;
            case 3:
                saveFile(lines);
                break;
            case 4:
                std::cout << "Exiting the editor. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    }
}
