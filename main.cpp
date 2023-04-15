#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(){

    int strip[30000];
    int index = (30000 / 2);

    std::vector<int> loopStarts;
    int loopEnd;
    
    std::ifstream in("inputDoc.txt");
    if(in.fail()){
        std::cout << "Error reading file\n";
        in.close();
        return 1;
    }

    std::ofstream out;
    out.open("outputDoc.txt");
    if(out.fail()){
        std::cout << "Could create output doc\n";
        out.close();
        return 1;
    }

    std::string input;
    std::string temp;
    while(in >> temp){
        input.append(temp);
    }
    
    for(size_t i = 0; i < input.length(); i++)
    {
        std::cout << index << ", ";
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

                break;
            }
            case '[':
            {
                if(strip[index] == 0){
                    if(loopEnd > i) i = loopEnd;
                    if(loopStarts.size() >= 1 && loopStarts.back() == i){
                        loopStarts.pop_back();
                    }
                }
                else
                {
                    if(loopStarts.size() == 0 || i != loopStarts.back()){
                        loopStarts.push_back(i);
                    }
                }
                break;
            }
            case ']':
            {
                if(strip[index] != 0){
                    loopEnd = i;
                    i = loopStarts.back() - 1;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
    
    in.close();
    out.close();
    return 0;
}