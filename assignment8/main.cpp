// Keanu Aloua
// April 13, 2022
// Assignment 8
// Last Update: April 22, 2022

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "priority-queue.h"

int main() {

    // Keeps track of stocks
    std::vector<stockType> stocks;

    // Checks if stock bought
    std::unordered_map<std::string, bool> stocksBought;

    std::string stocksFile;
    std::string filename;
    int days;
    double balance = 0.0;

    // -- User input --
    std::cout << "Stocks file: ";
    std::cin >> stocksFile;
    std::cout << std::endl;

    std::cout << "Sim file: ";
    std::cin >> filename;
    std::cout << std::endl;

    std::cout << "Amount of days to simulate: ";
    std::cin >> days;
    std::cout << std::endl;

    std::cout << "Amount you wish to transfer into brokerage account: ";
    std::cin >> balance;
    std::cout << std::endl;

    // ---------------------------------
    // -- Reading through stocks file --
    // ---------------------------------

    std::string line;
    std::ifstream readStocks(stocksFile);

    while (getline(readStocks, line)) {
        std::string name, div;
        std::stringstream ss(line);
        double dividend;

        getline(ss, name, ',');
        ss >> div;

        dividend = strtod(div.c_str(), nullptr);

        // Creating stock object
        stockType stock;
        stock.name = name;
        stock.timesPurchased = 0;
        stock.dividend = dividend;
        stock.price = 0.0;

        stocks.push_back(stock);
        stocksBought[stock.name] = false;
    }

    // ------------------------------------
    // --  Reading file of stock prices  --
    // ------------------------------------

    std::ifstream readCSV(filename);
    std::string parse;
    double startPrice, endPrice;

    for (int i = 1; i <= days; i++) {
        
        std::cout << "Day " << i << " Current balance $ ";
        std::cout << std::fixed << std::setprecision(2) << balance << std::endl << std::endl;

        // ********************
        // *** START OF DAY ***
        // ********************

        // Reading the START day row
        getline(readCSV, line);
        std::stringstream ss(line);

        // Parses the START day row
        for (int j = 0; j < stocks.size(); j++) {
            getline(ss, parse, ',');
            startPrice = strtod(parse.c_str(), nullptr);

            stocks[j].price = startPrice;
        }

        // Inserting stocks into the priority queue
        priorityQ<stockType> queue; // From index 1
        for (int i = 0; i < stocks.size(); i++) {
            queue.insert(stocks[i]);
        }

        // Buying min availabe stocks
        double payed = 0.0;
        while (!queue.isEmpty()) {
            stockType cheapest = queue.getPriority();

            if (payed + cheapest.price <= balance) {
                std::cout << "Buying one share of " << cheapest.name << " valued at $ ";
                std::cout << std::fixed << std::setprecision(2) << cheapest.price << " per share" << std::endl;
                payed += cheapest.price;

                stocksBought[cheapest.name] = true;

                // Finds stock to increment times purchased
                for (int k = 0; k < stocks.size(); k++) {
                    if (cheapest.name == stocks[k].name) {
                        stocks[k].timesPurchased++;
                        break;
                    }
                }
            }

            queue.deletePriority();
        }

        std::cout << std::endl;

        // ******************
        // *** END OF DAY ***
        // ******************

        // Keeps track of end day prices of stocks
        std::vector<double> stocksEnd;
       
        // Read in END day row
        getline(readCSV, line);
        std::stringstream end(line);

        // Parses the END day row
        for (int e = 0; e < stocks.size(); e++) {
            getline(end, parse, ',');
            endPrice = strtod(parse.c_str(), nullptr);
            stocksEnd.push_back(endPrice);
        }

        // ***************************
        // *** COMPUTE GAINS/LOSES ***
        // ***************************

        double profit = 0.0, increase = 0.0;

        // Will compare the start prices with the end prices
        for (int m = 0; m < stocks.size(); m++) {

            // Checks if stocks were bought today
            if (stocksBought[stocks[m].name]) {
                increase += stocksEnd[m];

                // Setting back to false
                stocksBought[stocks[m].name] = false;
            }
        }

        profit = increase - payed;

        std::cout << "Profit made today $ ";
        std::cout << std::fixed << std::setprecision(2) << profit << std::endl;
        std::cout << std::endl;

        balance += profit;
    }

    // -------------------------
    // -- Computing Dividends --
    // -------------------------

    double dividends = 0.0, product = 0.0;

    for (int i = 0; i < stocks.size(); i++) {
        product = stocks[i].dividend * stocks[i].timesPurchased;
        dividends += product;
    }

    std::cout << "Balance after " << days << " days $ ";
    std::cout << std::fixed << std::setprecision(2) << balance << std::endl;

    std::cout << "Amount in dividends $ ";
    std::cout << std::fixed << std::setprecision(2) << dividends << std::endl;

    return 0;
}