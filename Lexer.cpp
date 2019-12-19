
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Lexer.h"
using namespace std;

int main(int argc, char *argv[]) {
    try {
        //trying to create a lexer.
        vector<string> commandLex = lexFile(argv[1]);
        printVector(commandLex);
    } catch(const char* e) {
        cout<<e<<endl;
    }
}

//this function is responsible of tokenizing the txt file.
vector<string> lexFile(string str){
    string line;
    vector<string> strVector;
    fstream fp(str, ios::in);
    if (!fp) {
        throw "Error opening file.";
    }
    while (!fp.eof()) {
        //Get line from file.
        getline(fp, line);
        //split string into small parts of string and put it in a string vector.
        vector<string> newVector = splitLine(line);
        //merge two vectors.
        strVector.insert(strVector.end(),newVector.begin(),newVector.end());
    }
    return strVector;
}
//this method splits a line from text file into strings. returns a vector of those strings.
vector<string> splitLine(string st){
    vector<string> vec;
    string tempStr, condition;
    bool bracketsFlag = false, quotesFlag = false;
    //separating while/if.
    if (st.find("while") == 0|| st.find("if") == 0) {
        return conditionCheck(st);
    }
    //iterate through all chars in string (line in text file).
    for(int i=0;i<st.length();i++) {
        //c is the i'th char in string.
        char c = st[i];
        if (c == '=') {
            vec.push_back("=");
            //push remaining string (in line) into stack.
            vec.push_back(separateAfterEqual(st));
            //return vector;
            return vec;
        }
        //if current char is a part of an arrow, push arrow and further content.
        if (st.substr(i, 2) == "->" || st.substr(i, 2) == "<-") {
            vec.push_back(arrowDirection(st, i));
            //add sim to vector if is in line.
            if (st.find("sim") != st.npos) {
                vec.push_back("sim");
            }
            vec.push_back(separateAfterArrow(st));
            return vec;
        }
        //checks for an arrow or an equal sign with no space prior to it.
        if (c != ' ' && (arrowIsNext(st, i) || st.substr(i + 1, 1) == "=")) {
            tempStr.push_back(c);
            //separate equal\arrow sign when not separated by spaces, and put it in a vector.
            return noSpaceSign(st,tempStr, i);
            //if char is not a separation char, or if separation char is the first char.
        } else if ((c != ' ' && c != '(' && c != ')' && c != ',') || i == 0) {
            //using "quotes" flag for indication for referring a string to one string or multiple substrings.
            if (c == '"') {
                if (!quotesFlag) {
                    quotesFlag = true;
                } else {
                    quotesFlag = false;
                }
            }
            //remove tabs from string.
            if (c != '\t') {
                tempStr.push_back(c);
            }
            //put content in brackets in one string
        } else if (c == '(') {
            //if current temporary string is not empty, push to stack.
            if (tempStr != "") {
                vec.push_back(tempStr);
                tempStr = "";
            }
            bracketsFlag = true;
            //closing bracket,
        } else if (c == ')') {
            bracketsFlag = false;
        } else if (c == ' ' && bracketsFlag) {
            tempStr.push_back(c);
        } else if (!quotesFlag) {
            vec.push_back(tempStr);
            tempStr = "";
        } else {
            tempStr.push_back(c);
        }
    }
    //push last string (if wasn't already).
    if (tempStr !="") {
        vec.push_back(tempStr);
    }
    return vec;
}
//prints string vector.
void printVector(vector<string> vec) {
    for (auto const& i:vec) {
        cout<<i + "\n"<<flush;
    }
}
//takes a string, and returns a substring after '=' character.
string separateAfterEqual(string st) {
    bool reach = false;
    string newSt;
    for (char c : st) {
        if (reach && c != ' ') {
            newSt.push_back(c);
        }
        if (c == '=') {
            reach = true;
        }
    }
    return newSt;
}
//takes a string, and returns a substring after arrow substring.
string separateAfterArrow(string st) {
    bool reach = false;
    //prevents "sim" being removed more than once in a line.
    bool simFlag = false;
    string newSt;
    for (int i = 1; i <st.length() - 1;i++) {
        if (st.substr(i,3) == "sim" && (!simFlag)) {
            i += 4;
            simFlag = true;
        }
        char c = st[i];
        if (reach && c != ' ') {
            newSt.push_back(c);
        }
        if (st.substr(i-1, 2) == "->" || st.substr(i-1, 2) == "<-") {
            reach = true;
        }
    }
    return newSt;
}
//checks whether arrow is next in string or not.
bool arrowIsNext(string str, int count) {
    return str.substr(count+1, 2) == "<-" || str.substr(count+1, 2) == "->";
}
//checks arrow directions and returns the arrow.
string arrowDirection(string str, int count) {
    if (str.substr(count+1, 2) == "<-"){
        return "<-";
    }
    return "->";
}
//check while/if statements, and pushing them to stack accordingly.
vector<string> conditionCheck(string st){
    string condition;
    vector<string> vec;
    if (st.find("while") == 0) {
        condition = "while";
    } else {
        condition = "if";
    }
    vec.push_back(condition);
    st = st.substr(condition.length() + 1);
    st.erase(remove(st.begin(),st.end(), ' '), st.end());
    vec.push_back(st);
    vec.push_back("{");
    return vec;
}
//this method gets a string (line of txt file),
vector<string> noSpaceSign(string st, string tempStr,int index) {
    vector<string> vec;
    vec.push_back(tempStr);
    //if its an arrow, push it to vector.
    if (arrowIsNext(st, index)) {
        vec.push_back(arrowDirection(st, index));
        //add sim to vector if is in line.
        if (st.find("sim") != st.npos) {
            vec.push_back("sim");
        }
        //push remaining string (in line) into stack
        vec.push_back(separateAfterArrow(st));
        //otherwise its an equal sign. push to vector.
        return vec;
    } else {
        vec.push_back("=");
        string s1 = st.substr(index+1);
        //push remaining string (in line) into stack.
        vec.push_back(separateAfterEqual(st));
        return vec;
    }
}