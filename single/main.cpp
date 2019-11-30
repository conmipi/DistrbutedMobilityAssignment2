#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <chrono>


using namespace std;



int main()
  {

    auto start = std::chrono::high_resolution_clock::now();
    std::map<string,int> words = {}; 

  string line;
  string word;
  std::map<string,int>::iterator it;
  ifstream myfile( "./data_elonmusk.csv");
  string toRemove[13] = {".",",","?","!"," a "," an "," the "," and "," or "," but ","(",")",":"};
  ofstream outputFile( "./singleOutput.txt");

  if (myfile) 
    {
    while (getline(myfile, line))  
      {

          for(int i = 0; i<4; i++){
              getline( myfile, line, '"');
          }

          for(int i =0; i<13; i++){
              size_t start = 0;
              string from = toRemove[i];
              while((start = line.find(from,start)) != std::string::npos){
                    line.replace(start,from.length()," ");
              }
          }

         
          stringstream stream(line);

          while(stream >> word){
                it = words.find(word);
            if( it == words.end()){
                words.emplace(word,1);
            }else{
                it->second++;
            }
          
          }



      }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end -start;
    std::cout << "Time:" << duration.count() << std::endl;
    outputFile << "Time:" << duration.count() << std::endl;
      myfile.close();

      for(auto& x:words){

            
            outputFile << x.first << " " << x.second << std::endl;
            

      }


   
    }



    myfile.close();


  return 0;
  }

