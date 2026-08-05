#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool isEmail(const string& word) {
    return word.find('@') != string::npos;
}

bool isUrl(const string& word) {
    return word.size() >= 7 && (word.substr(0, 7) == "http://" || 
           (word.size() >= 8 && word.substr(0, 8) == "https://"));
}

bool isBullet(const string& word) {
    if (word.empty()) return false;
    
    if (word == "*" || word == "-") return true;
    
    if (word.length() > 1) {
        char lastChar = word.back();
        if (lastChar == '.' || lastChar == ')') {
            string prefix = word.substr(0, word.length() - 1);
            if (!prefix.empty() && all_of(prefix.begin(), prefix.end(), ::isdigit)) {
                return true;
            }
        }
    }
    
    return false;
}

struct Config {
    int evenWidth;
    int oddWidth;
    bool hyphenate;
};

Config parseCommand(const string& cmd) {
    Config cfg;
    cfg.evenWidth = 75;
    cfg.oddWidth = 75;
    cfg.hyphenate = false;
    
    vector<string> tokens;
    istringstream iss(cmd);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "h") {
            cfg.hyphenate = true;
        } else if (tokens[i] == "-w") {
            if (i + 1 < tokens.size() && isdigit(tokens[i + 1][0])) {
                cfg.evenWidth = cfg.oddWidth = stoi(tokens[i + 1]);
            }
        } else if (tokens[i] == "-w-e") {
            if (i + 1 < tokens.size() && isdigit(tokens[i + 1][0])) {
                cfg.evenWidth = stoi(tokens[i + 1]);
            }
        } else if (tokens[i] == "-w-o") {
            if (i + 1 < tokens.size() && isdigit(tokens[i + 1][0])) {
                cfg.oddWidth = stoi(tokens[i + 1]);
            }
        }
    }
    
    return cfg;
}

vector<vector<string>> getParagraphs(const vector<string>& lines) {
    vector<vector<string>> paragraphs;
    vector<string> current;
    
    for (const string& line : lines) {
        istringstream iss(line);
        string word;
        vector<string> words;
        
        while (iss >> word) {
            words.push_back(word);
        }
        
        if (words.empty()) {
            if (!current.empty()) {
                paragraphs.push_back(current);
                current.clear();
            }
        } else {
            current.insert(current.end(), words.begin(), words.end());
        }
    }
    
    if (!current.empty()) {
        paragraphs.push_back(current);
    }
    
    return paragraphs;
}

vector<string> formatParagraph(vector<string> tokens, const Config& cfg) {
    vector<string> lines;
    string currentLine = "";
    int lineNum = 0;
    
    size_t i = 0;
    while (i < tokens.size()) {
        string word = tokens[i];
        int maxW = (lineNum % 2 == 0) ? cfg.evenWidth : cfg.oddWidth;
        
        // Check if it's a bullet
        if (isBullet(word)) {
            // Flush current line if not empty
            if (!currentLine.empty()) {
                lines.push_back(currentLine);
                currentLine = "";
                lineNum++;
                maxW = (lineNum % 2 == 0) ? cfg.evenWidth : cfg.oddWidth;
            }
            
            // Start new line with bullet
            currentLine = word;
            i++;
            continue;
        }
        
        int wordLen = word.length();
        bool special = isEmail(word) || isUrl(word);
        
        // Empty line - first word
        if (currentLine.empty()) {
            if (special || wordLen <= maxW) {
                currentLine = word;
                i++;
            } else if (cfg.hyphenate) {
                // Hyphenate on first position
                int space = maxW - 1; // Reserve for hyphen
                if (space > 0 && space < wordLen) {
                    currentLine = word.substr(0, space) + "-";
                    tokens[i] = word.substr(space);
                    lines.push_back(currentLine);
                    currentLine = "";
                    lineNum++;
                } else {
                    currentLine = word;
                    i++;
                }
            } else {
                currentLine = word;
                i++;
            }
            continue;
        }
        
        // Try to add word to current line
        int needed = currentLine.length() + 1 + wordLen;
        
        if (needed <= maxW) {
            // Fits!
            currentLine += " " + word;
            i++;
        } else {
            // Doesn't fit
            if (special) {
                // Move special to next line
                lines.push_back(currentLine);
                currentLine = "";
                lineNum++;
            } else if (cfg.hyphenate) {
                // Try hyphenation
                int available = maxW - currentLine.length() - 1 - 1; // space + hyphen
                
                if (available > 0 && available < wordLen) {
                    currentLine += " " + word.substr(0, available) + "-";
                    tokens[i] = word.substr(available);
                    lines.push_back(currentLine);
                    currentLine = "";
                    lineNum++;
                } else {
                    // Can't hyphenate, move to next line
                    lines.push_back(currentLine);
                    currentLine = "";
                    lineNum++;
                }
            } else {
                // No hyphenation, move to next line
                lines.push_back(currentLine);
                currentLine = "";
                lineNum++;
            }
        }
    }
    
    // Flush remaining
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }
    
    return lines;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    vector<string> lines;
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        lines.push_back(line);
    }
    
    string command;
    getline(cin, command);
    
    Config cfg = parseCommand(command);
    vector<vector<string>> paragraphs = getParagraphs(lines);
    
    vector<string> result;
    for (size_t p = 0; p < paragraphs.size(); p++) {
        vector<string> formatted = formatParagraph(paragraphs[p], cfg);
        result.insert(result.end(), formatted.begin(), formatted.end());
        
        // Add blank line after paragraph (except last)
        if (p < paragraphs.size() - 1) {
            result.push_back("");
        }
    }
    
    for (const string& line : result) {
        cout << line << endl;
    }
    
    return 0;
}