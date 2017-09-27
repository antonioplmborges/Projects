#include <string>
#include <queue>
#include <map>
#include <set>
#include "inverter.h"
#include <iterator>
#include <algorithm>
#include <sstream>



using namespace std;

string build_inverted_index(string filename){
    
    map<string, set<int> > invertedIndex;
    stringstream output;    //stores the output string
    string file_string;    //name of the files
    string str;
    int count= 0;       //file counter
    string word;        //buffer
    
    //file input variables
    ifstream myReadInputs;
    ifstream  myReadFile;
    
    myReadInputs.open(filename);
    if (myReadInputs.is_open()) {
        while(!myReadInputs.eof()) // To get you all the lines.
        {
            
            getline(myReadInputs,file_string); // Saves the line in file_string.
            //cout<<file_string<<endl; DEBUG
        
            myReadFile.open(file_string);//open files inside arg[1]
            if (myReadFile.is_open()) {
                while(!myReadFile.eof()) // To get you all the lines.
                {
                    
                    getline(myReadFile,str);//gets line and stores on string
                    
                    if(str.size()==0) break;//if file is empty break
   
                    
                    //for(auto pos = str.begin(); pos != str.end();pos++)
                    for (unsigned pos = 0; pos < str.size(); pos++)
                    {
                        //cout<<str.at(pos)<<endl; DEBUG
                        //if there's a alpha char at the end of the string capture the word
                        if (isalpha(str.back()) && pos==str.size()-1 ){
                            word   += str.back();
                            invertedIndex[word].insert(count);//insert in map
                            word.clear();//clear buffer
                        }
                        //if char is not alpha or if it's a empty char
                        else if(  !(isalpha(str.at(pos))) || str.at(pos) == ' ')
                        {
                            if(word!= "")
                            invertedIndex[word].insert(count);
                            
                            //cout<<word<<endl; DEBUG
                            word.clear();
                            continue;

                        }
                        else {//if char is alpha
                            word += str.at(pos);//append char to buffer
                            continue;//keeps on iterating thru the string
                        }
                
                    }//for
        
                }//while
                
                count++;                //increment file counter
                word.clear();           //clear buffer
                myReadFile.close();     //close file
                myReadFile.clear();     //clear ifstream
                continue;
                
                
            }else{//if file doesnt open
                myReadFile.clear();      //clear ifstream
                continue;
            }
        
        }
        myReadInputs.close();//closes the input file
        
        
        for(auto map_it = invertedIndex.begin(); map_it != invertedIndex.end(); map_it++){
            //cout<<(*map_it).first<<": ";
            output<<(*map_it).first<<":";
            
            
            for(auto set_it = map_it->second.begin(); set_it != map_it->second.end(); ++set_it)
                //cout << *set_it <<" ";
                output<<" "<<*set_it;
            
            output<<"\n";
        }
        
        return output.str();//return string  with map farmatted
        
    } return ""; //if argv[1] doesnt open
}




