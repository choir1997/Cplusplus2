#include <iostream>
#include "QS.h"
#include "QSInterface.h"
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
    }


    QS<int> myArray;
    string inputLine;

    while (getline(in, inputLine)) {
        istringstream iss(inputLine);
        string commandLine;
        size_t arraySize;
        iss >> commandLine;
        out << commandLine;
        if (commandLine == "QuickSort") {
            try {
                iss >> arraySize;
                out << " " << arraySize;
                if (!myArray.setArray(arraySize)) {
                    throw 89;
                }
                else {
                    out << " OK";
                }
            } catch (int x) {
                out << " Error";
            }
        }
        else if (commandLine == "Capacity") {
            out << " " << myArray.capacity();
        }
        else if (commandLine == "Clear") {
            if (myArray.clear()) {
                out << " OK";
            }
        }
        else if (commandLine == "AddToArray") {
            int arrayItem;
            int itemCount = 0;
            while (iss >> arrayItem) {
                if (itemCount == 0) {
                    out << "  " << arrayItem;
                }
                else {
                    out << "," << arrayItem;
                }
                itemCount++;
                myArray.addElement(arrayItem);
            }
            out << " OK";
        }
        else if (commandLine == "PrintArray") {
            out << " " << myArray.toString();
        }
        else if (commandLine == "Size") {
            out << " " << myArray.size();
        }
        else if (commandLine == "MedianOfThree") {
            int leftValue;
            int rightValue;
            iss >> leftValue >> rightValue;
            out << leftValue << "," << rightValue;
            out << " = " << myArray.medianOfThree(leftValue, rightValue);
        }
        else if (commandLine == "Partition") {
            int leftValue;
            int rightValue;
            int pivotIndex;
            iss >> leftValue >> rightValue >> pivotIndex;
            out << leftValue << "," << rightValue << "," << pivotIndex;
            out << " = " << myArray.partition(leftValue, rightValue, pivotIndex);
        }
        else if (commandLine == "SortAll") {
            if (myArray.sortAll()) {
                out << " OK";
            }
            else {
                out << " Error";
            }
        }
        else if (commandLine == "Sort") {
            int sortLeft;
            int sortRight;
            iss >> sortLeft >> sortRight;
            out << " " << sortLeft << "," << sortRight;
            if (myArray.sort(sortLeft, sortRight)) {
                out << " OK";
            }
            else {
                out << " Error";
            }
        }
        else if (commandLine == "Stats") {
            out << " " << myArray.statsArrayComparison();
            out << "," << myArray.statsArrayExchange();
        }
        out << endl;
    }
    return 0;
}
