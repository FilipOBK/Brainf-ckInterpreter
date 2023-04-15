#include <iostream>
#include <string>
#include <fstream>
#include <vector>

template <typename T>
void printVec(std::vector<T>& vec){
    if(vec.size() == 0) return;
    std::cout << "[ ";
    for(size_t i = 0; i < vec.size() - 1; i++){
        std::cout << vec[i] << ", ";
    }
    std::cout << vec.back() << " ]";
}

int main(){

    int strip[30000];
    int index = (30000 / 2);

    std::vector<int> loopStarts, loopEnds;
    
    std::ifstream code("code.txt");
    if(code.fail()){
        std::cout << "Error reading code file\n";
        code.close();
        return 1;
    }

    std::ifstream in("input.txt");
    if(in.fail()){
        std::cout << "Error reading input\n";
        in.close();
        return 1;
    }

    std::ofstream out;
    out.open("output.txt");
    if(out.fail()){
        std::cout << "Could create output doc\n";
        out.close();
        return 1;
    }

    std::string input;
    std::string temp;
    while(code >> temp){
        input.append(temp);
    }
    
    for(size_t i = 0; i < input.length(); i++)
    {
        switch(input[i])
        {
            case '>':
            {
                index++;
                break;
            }
            case '<':
            {
                index--;
                break;
            }
            case '+':
            {
                strip[index]++;
                break;
            }
            case '-':
            {
                strip[index]--;
                break;
            }
            case '.':
            {
                out << (char)(strip[index]);
                break;
            }
            case ',':
            {
                if(in){
                    strip[index] = in.get();
                }
                break;
            }
            case '[':
            {
                if(strip[index] != 0){
                    if(loopStarts.size() == 0 || i != loopStarts.back()){
                        loopStarts.push_back(i);
                    }
                }
                if(strip[index] == 0){
                    if(loopEnds.size() != 0){
                        i = loopEnds.back();
                        loopEnds.pop_back();
                    } else {
                        int numOpen = 1;
                        while(numOpen > 0){
                            i++;
                            if(input[i] == ']') numOpen--;
                            if(input[i] == '[') numOpen++;
                        }
                    }
                }
                break;
            }
            case ']':
            {
                if(strip[index] == 0){
                    loopStarts.pop_back();
                }
                if(strip[index] != 0){
                    if(loopStarts.size() != 0){
                        i = loopStarts.back() - 1;
                    }
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
    
    code.close();
    out.close();
    in.close();
    return 0;
}