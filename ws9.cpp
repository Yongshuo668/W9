#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

typedef vector<int> Records;

class RecordsManager {
private:
    fstream _file;
    string _filename;

public:
    RecordsManager(string filename) : _filename(filename) {}

    void read(Records &records) {
        _file.open(_filename, ios::in);

        if (!_file.is_open()) {
            throw runtime_error("File cannot be opened");
        }

        try {
            string line;
            while (getline(_file, line)) {
                size_t pos;
                int value = stoi(line, &pos);
                if (pos != line.size()) {
                    throw invalid_argument("Invalid integer format: " + line);
                }
                records.push_back(value);
            }
        } catch (const invalid_argument &e) {
            _file.close();
            cout << "invalid_argument error: " << e.what() << endl;
            throw;
        } catch (const out_of_range &e) {
            _file.close();
            cout << "out_of_range error: " << e.what() << endl;
            throw;
        } catch (...) {
            _file.close();
            throw;
        }

        _file.close();
    }
};

int main(int argc, char* argv[]) {
    Records myRecords;

    string filename = "records.txt";
    if (argc > 1) filename = argv[1];

    RecordsManager recordM(filename); 

    try {
        recordM.read(myRecords);
    } catch (const invalid_argument &e) {
        cout << "Caught in main: invalid_argument - " << e.what() << endl;
        return 1;
    } catch (const out_of_range &e) {
        cout << "Caught in main: out_of_range - " << e.what() << endl;
        return 1;
    } catch (const runtime_error &e) {
        cout << "runtime_error error: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "Caught unknown exception" << endl;
        return 1;
    }

    int sum = 0;
    for (int value : myRecords) {
        sum += value;
    }
    cout << "Sum: " << sum << endl;

    return 0;
}
    