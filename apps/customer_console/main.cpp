#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include "customer/customer_archive.hpp"
#include "customer/customer_formatter.hpp"

namespace 
{
    void clearInputLine() 
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string readNonEmptyLine(const std::string& prompt) 
    {
        while (true) 
        {
            std::cout << prompt;
            std::string line;
            std::getline(std::cin, line);
            if (!line.empty()) 
            {
                return line;
            }
            std::cout << "Input must not be empty.\n";
        }
    }
    int readIntAtLeast(const std::string& prompt, int min_value) 
    {
        while (true) 
        {
            std::cout << prompt;
            int value = 0;
            if (std::cin >> value) 
            {
                clearInputLine();
                if (value >= min_value) 
                {
                    return value;
                }
            } 
            else 
            {
                std::cin.clear();
                clearInputLine();
            }
            std::cout << "Please enter an integer >= " << min_value << ".\n";
        }
    }
    customer::Color readColor() 
    {
        while (true) 
        {
            std::cout << "Favorite color (1=Blue, 2=Green, 3=Violet, 4=Red, 5=Yellow, 6=Turquoise, 7=White): ";
            int c = 0;
            if (std::cin >> c) 
            {
                clearInputLine();
                if (c >= COLOR_BLUE && c <= COLOR_WHITE) 
                {
                    return static_cast<customer::Color>(c);
                }
            } 
            else 
            {
                std::cin.clear();
                clearInputLine();
            }
            std::cout << "Please enter a value between 1 and 7.\n";
        }
    }
    void printMenu() 
    {
        std::cout << "\n=== Customer Console ===\n"
                  << "1) Add customer\n"
                  << "2) Print customer by id\n"
                  << "3) Print all customers\n"
                  << "0) Exit\n";
    }
}

int main() 
{
    try 
    {
        auto archive = std::make_shared<customer::CustomerArchive>();
        customer::CustomerFormatter formatter(archive);
        while (true) 
        {
            printMenu();
            const int choice = readIntAtLeast("Select: ", 0);

            if (choice == 0) 
            {
                return 0;
            }
            if (choice == 1) 
            {
                customer::Customer c;
                c.id = readIntAtLeast("Id: ", 1);
                c.first_name = readNonEmptyLine("First name: ");
                c.last_name = readNonEmptyLine("Last name: ");
                c.zip_code = readNonEmptyLine("ZIP code: ");
                c.city = readNonEmptyLine("City: ");
                c.favorite_color = readColor();
                if (!c.isComplete()) 
                {
                    std::cout << "Customer data is incomplete. Not stored.\n";
                    continue;
                }
                if (!customer::fitsLegacy(c)) 
                {
                    std::cout << "One or more fields are too long (legacy size constraints). Not stored.\n";
                    continue;
                }
                const bool ok = archive->addCustomer(c);
                if (!ok) 
                {
                    std::cout << "Customer could not be stored (duplicate id or invalid data).\n";
                } 
                else 
                {
                    std::cout << "Customer stored.\n";
                }
            } 
            else if (choice == 2) 
            {
                const int id = readIntAtLeast("Id: ", 1);
                std::cout << formatter.formatById(id) << "\n";
            } 
            else if (choice == 3) 
            {
                const auto all = archive->getAll();
                if (all.empty()) 
                {
                    std::cout << "(no customers)\n";
                    continue;
                }
                for (const auto& c : all) 
                {
                    std::cout << formatter.formatById(c.id) << "\n";
                }
            } 
            else 
            {
                std::cout << "Unknown selection.\n";
            }
        }
    } 
    catch (const std::exception& ex) 
    {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }
}
