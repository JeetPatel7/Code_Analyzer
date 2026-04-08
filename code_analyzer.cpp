#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <GL/glut.h>

using namespace std;

string outputText = "";


void drawText(float x, float y, string text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float y = 0.9;
    string line = "";

    for (char c : outputText) {
        if (c == '\n') {
            drawText(-0.95, y, line);
            y -= 0.05;
            line = "";
        } else {
            line += c;
        }
    }

    glFlush();
}



// File stats
void showStats(vector<string>& lines) {
    int total = lines.size(), blank = 0, comment = 0;

    for (string t : lines) {
        int s = 0;
        while (s < t.size() && t[s] == ' ') s++;
        t = t.substr(s);

        if (t.empty()) blank++;
        else if (t.size() >= 2 && t[0]=='/' && t[1]=='/') comment++;
    }

    stringstream ss;
    ss << "\n--- FILE STATS ---\n";
    ss << "Total lines   : " << total << "\n";
    ss << "Blank lines   : " << blank << "\n";
    ss << "Comment lines : " << comment << "\n";
    ss << "Code lines    : " << total - blank - comment << "\n";

    outputText += ss.str();
}

// Syntax check
void checkSyntax(vector<string>& lines) {
    int openBrace = 0, closeBrace = 0;

    stringstream ss;
    ss << "\n--- SYNTAX CHECK ---\n";

    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];

        for (char c : line) {
            if (c == '{') openBrace++;
            if (c == '}') closeBrace++;
        }

        if (line.find("cout") != string::npos ||
            line.find("cin")  != string::npos ||
            line.find("return") != string::npos) {

            if (!line.empty() && line.back() != ';') {
                ss << "Line " << i+1 << ": Possible missing semicolon.\n";
            }
        }
    }

    if (openBrace != closeBrace)
        ss << "ERROR: Mismatched braces! {=" << openBrace << ", }=" << closeBrace << "\n";
    else
        ss << "Braces are balanced.\n";

    outputText += ss.str();
}

// Style check
void checkStyle(vector<string>& lines) {
    stringstream ss;
    ss << "\n--- STYLE CHECK ---\n";

    bool found = false;

    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];

        if (line.length() > 80) {
            ss << "Line " << i+1 << ": Line too long (" << line.length() << " chars).\n";
            found = true;
        }

        if (line.find("goto") != string::npos) {
            ss << "Line " << i+1 << ": Avoid using 'goto'.\n";
            found = true;
        }
    }

    if (!found) ss << "No style issues found.\n";

    outputText += ss.str();
}

// Performance check
void checkPerformance(vector<string>& lines) {
    stringstream ss;
    ss << "\n--- PERFORMANCE TIPS ---\n";

    bool found = false;

    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];

        if (line.find("endl") != string::npos) {
            ss << "Line " << i+1 << ": Use '\\n' instead of endl.\n";
            found = true;
        }

        if (line.find("new ") != string::npos) {
            ss << "Line " << i+1 << ": Raw pointer used - free memory.\n";
            found = true;
        }
    }

    if (!found) ss << "No performance issues found.\n";

    outputText += ss.str();
}

// Loop counter
void countLoops(vector<string>& lines) {
    int forCount = 0, whileCount = 0;

    for (string line : lines) {
        if (line.find("for(") != string::npos || line.find("for (") != string::npos)
            forCount++;

        if (line.find("while(") != string::npos || line.find("while (") != string::npos)
            whileCount++;
    }

    stringstream ss;
    ss << "\n--- LOOP COUNT ---\n";
    ss << "Total 'for' loops   : " << forCount << "\n";
    ss << "Total 'while' loops : " << whileCount << "\n";

    outputText += ss.str();
}

// Function analysis
void checkMainFunction(vector<string>& lines) {
    stringstream ss;
    ss << "\n--- MAIN FUNCTION CHECK ---\n";

    bool foundMain = false;

    for (string line : lines) {
        if (line.find("main(") != string::npos || line.find("main (") != string::npos) {
            foundMain = true;
            break;
        }
    }

    if (foundMain)
        ss << "main() function found.\n";
    else
        ss << "WARNING: main() function is missing.\n";

    outputText += ss.str();
}

void countFunctions(vector<string>& lines) {
    int functionCount = 0;

    for (string line : lines) {
        if ((line.find("(") != string::npos) &&
            (line.find(")") != string::npos) &&
            (line.find("{") != string::npos)) {

            if (line.find("if") == string::npos &&
                line.find("for") == string::npos &&
                line.find("while") == string::npos &&
                line.find("switch") == string::npos) {
                functionCount++;
            }
        }
    }

    stringstream ss;
    ss << "\n--- FUNCTION COUNT ---\n";
    ss << "Total functions : " << functionCount << "\n";

    outputText += ss.str();
}


int main(int argc, char** argv) {
    string filename;

    cout << "Enter filename to analyze: ";
    cin >> filename;

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open file.\n";
        return 1;
    }

    vector<string> lines;
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    showStats(lines);
    checkSyntax(lines);
    checkStyle(lines);
    checkPerformance(lines);
    countLoops(lines);
    checkMainFunction(lines);
    countFunctions(lines);

    outputText += "\n--- ANALYSIS DONE ---\n";

    
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("C++ Code Analyzer GUI");

    glClearColor(0, 0, 0, 1); 
    glColor3f(1, 1, 1);       

    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
