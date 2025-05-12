#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib> // for atoi
#include <iomanip> // for setprecision

using namespace std;

struct ResonanceData {
    string name;
    double fraction_goofit;
    double fraction_laura;
    double amp_goofit;
    double amp_laura;
    double phs_goofit;
    double phs_laura;
};

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    size_t start = 0;
    size_t end = s.find(delimiter);
    
    while (end != string::npos) {
        token = s.substr(start, end - start);
        tokens.push_back(token);
        start = end + 1;
        end = s.find(delimiter, start);
    }
    
    token = s.substr(start);
    tokens.push_back(token);
    
    return tokens;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " N" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    
    // Input file paths
    string diagonal_fractions_path = "/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/Laura_v" + to_string(N) + "/diagonal_fractions.txt";
    string fit_result_path = "/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/Laura_v" + to_string(N) + "/fit_result.txt";
    string laura_results_path = "/data1000/charmosinhos/Rian/Laura3/laura/Rian/Toy_MC_" + to_string(N) + "/Fit/Fit_results_" + to_string(N) + "_.txt";
    
    // Output file path
    //string output_path = "/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/Laura_v" + to_string(N) + "/fit_comparison.txt";
    string output_path = "/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/rho770_K892_Laura_v" + to_string(N) + "/fit_comparison.txt";

    
    vector<ResonanceData> resonances;
    
    // Step 1: Read diagonal_fractions.txt
    ifstream diagonal_file(diagonal_fractions_path);
    if (!diagonal_file.is_open()) {
        cerr << "Error opening diagonal_fractions.txt" << endl;
        return 1;
    }
    
    string line;
    while (getline(diagonal_file, line)) {
        vector<string> tokens = split(line, ' ');
        if (tokens.size() >= 2) {
            ResonanceData res;
            res.name = tokens[0];
            res.fraction_goofit = stod(tokens[1]);
            resonances.push_back(res);
        }
    }
    diagonal_file.close();
    
    // Step 2: Read fit_result.txt for AMP and PHS values
    ifstream fit_result_file(fit_result_path);
    if (!fit_result_file.is_open()) {
        cerr << "Error opening fit_result.txt" << endl;
        return 1;
    }
    
    while (getline(fit_result_file, line)) {
        vector<string> tokens = split(line, ' ');
        if (tokens.size() >= 2) {
            string key = tokens[0];
            for (auto& res : resonances) {
                if (key.find(res.name + "_AMP") != string::npos) {
                    res.amp_goofit = stod(tokens[1]);
                } else if (key.find(res.name + "_PHS") != string::npos) {
                    res.phs_goofit = stod(tokens[1]);
                }
            }
        }
    }
    fit_result_file.close();
    
    // Step 3: Read Laura's results file
    ifstream laura_file(laura_results_path);
    if (!laura_file.is_open()) {
        cerr << "Error opening Laura's results file" << endl;
        return 1;
    }
    
    int current_res = 0;
    while (getline(laura_file, line) && current_res < static_cast<int>(resonances.size())) {
        if (line.find("Amp:") != string::npos) {
            vector<string> tokens = split(line, ' ');
            if (tokens.size() >= 2) {
                resonances[current_res].amp_laura = stod(tokens[1]);
            }
        } else if (line.find("Phase:") != string::npos) {
            vector<string> tokens = split(line, ' ');
            if (tokens.size() >= 2) {
                resonances[current_res].phs_laura = stod(tokens[1]);
            }
        } else if (line.find("Fit Fraction:") != string::npos) {
            vector<string> tokens = split(line, ' ');
            if (tokens.size() >= 3) {
                // Multiply Laura's fraction by 100 to match GooFit's percentage
                resonances[current_res].fraction_laura = stod(tokens[2]) * 100.0;
                current_res++;
            }
        }
    }
    laura_file.close();
    
    // Step 4: Write output file
    ofstream output_file(output_path);
    if (!output_file.is_open()) {
        cerr << "Error creating output file" << endl;
        return 1;
    }
    
    // Set precision for all floating point output
    output_file << fixed << setprecision(6);
    
    // Write header with tabs
    output_file << "Resonance \t Frac_Goofit \t Frac_Laura \t Amp_Goofit \t Amp_Laura \t Phs_Goofit \t Phs_Laura" << endl;
    
    // Write data with tabs and consistent formatting
    for (const auto& res : resonances) {
        output_file << res.name << "\t\t "
                   << res.fraction_goofit << "\t\t "
                   << res.fraction_laura << "\t\t "
                   << res.amp_goofit << "\t\t "
                   << res.amp_laura << "\t "
                   << res.phs_goofit << "\t\t "
                   << res.phs_laura << endl;
    }
    
    output_file.close();
    
    cout << "Comparison file created successfully at: " << output_path << endl;
    
    return 0;
}