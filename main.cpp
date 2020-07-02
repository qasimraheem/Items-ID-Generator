#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Data {
    int sid = 0;
    int quantity = 0;
    string type = "";

    void print() {
        cout << "sid:" << sid << endl;
        cout << "quantity:" << quantity << endl;
        cout << "type:" << type << endl;
    };
};

vector<string> createID(vector<Data> data) {
    vector<string> ID;
    for (auto x: data) {
        for (int i = 0; i < x.quantity; i++) {
            string id;
            id = x.type.substr(0, 3);
            id += "-" + to_string(x.sid);
            id += "-" + to_string(i + 1);

            ID.push_back(id);
        }
    }
    return ID;
}

int main() {
    vector<Data> data;
    string fileName="list1.csv";

    fstream file;
    file.open(fileName, ios::in);

    Data tempData;
    if (file.is_open()) {

        string line;
        int i = 0;
        while (file.good()) {
            getline(file, line);

            stringstream s(line);
            string tamparray[6], word;
            int k = 0;
            while (getline(s, word, ',')) {
                tamparray[k] = word;
                k++;
            }
            if (i > 0) {
                tempData.sid = stoi(tamparray[0]);
                tempData.quantity = stoi(tamparray[2]);
                tempData.type = tamparray[5];
                data.push_back(tempData);
            }
            i++;
        }
        file.close();
    }
    for (int j = 0; j < 51; ++j) {
        data[j].print();
    }
    vector<string> ID = createID(data);

    ofstream newfile;
    newfile.open("ID.csv");
    if (newfile.is_open()) {
        if (newfile.good()) {
            for (auto x:ID) {
                newfile << x << "\n";
            }
        }
    }
    return 0;
}