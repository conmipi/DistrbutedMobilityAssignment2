#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

#define THREADS 8

string toRemove[13] = {".",",","?","!"," a "," an "," the "," and "," or "," but ","(",")",":"};


void processLine(string line, map<string,int>* words){

  string word;
  std::map<string,int>::iterator it;


         for(int i =0; i<13; i++){
              size_t start = 0;
              string from = toRemove[i];
              while((start = line.find(from,start)) != std::string::npos){
                    line.replace(start,from.length()," ");
              }
          }

         
          stringstream stream(line);

          while(stream >> word){
                it = words->find(word);
            if( it == words->end()){
                words->emplace(word,1);
            }else{
                it->second++;
            }
          
          }
    
}

int main()
  {

    auto start = std::chrono::high_resolution_clock::now();
    std::map<string,int> words[THREADS];
    string lines[THREADS];
    std::thread busyBoys[THREADS];
    for(int i = 0; i<THREADS; i++){

        lines[i] = "";
        words[i] = {};

    }

  string line;
  ifstream myfile( "./data_elonmusk.csv");
  int id = 0;
  if (myfile) 
    {
    while (getline(myfile, line))  
      {

          for(int i = 0; i<4; i++){
              getline( myfile, line, '"');
          }
            
            
           lines[id] += " "+ line;
           id++;
           id%=THREADS;



      }
      for(int i = 0; i< THREADS; i++){
        busyBoys[i] = std::thread(processLine,lines[i],words+i);
      }
      for(int i = 0; i< THREADS; i++){
          if(busyBoys[i].joinable()){
          busyBoys[i].join();
          }
      }

    std::map<string,int> realList;
    std::map<string, int>::iterator it2;

      for (int i=0; i < THREADS; i++){

          for (auto const& it : words[i]){
              if ((it2=realList.find(it.first))!= realList.end()){
                it2->second += it.second;
              }
              else{
                realList.emplace(it.first,it.second);
              }
          }
      }  

      for(auto& x:realList){

            
            cout << x.first << " " << x.second << std::endl;

      }


    myfile.close();
    }
  
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end -start;
    std::cout << "Time:" << duration.count() << std::endl;

  return 0;
  }

