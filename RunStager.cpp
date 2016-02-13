#include <iostream>
#include <fstream>
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"
#include "TFile.h"

namespace bpo = boost::program_options;

namespace RunStager{

  void stageRun(const std::string& targetPath){
    
    auto file = TFile::Open(targetPath.c_str());
    if(file == nullptr) std::cerr<<"Error: "<<targetPath<<" cannot be opened"<<std::endl;
    
  }
  
  void stageRunList(const boost::filesystem::path& runListPath, const std::string& dataPattern, const std::string& fileExtension){
    
    std::ifstream inputStream(runListPath.string());
    
    std::string runNumber;
    while(inputStream>>runNumber) stageRun(dataPattern+runNumber+fileExtension);
    
  }

}

int main(int argc, char* argv[]){
  
  boost::filesystem::path runListPath;
  std::string dataPattern, fileExtension;
  
  bpo::options_description optionDescription("RunStager usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("run-list,r", bpo::value<boost::filesystem::path>(&runListPath)->required(), "Path of the run list to stage")
  ("data-pattern,p", bpo::value<std::string>(&dataPattern)->required(), "Storage pattern of the data to prefix the run numbers")
  ("file-extension,e", bpo::value<std::string>(&fileExtension)->default_value(".root"), "Extension of the run files");

  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("run-list", 1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help") || argc == 1){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& e){
    
    std::cerr<<e.what()<<std::endl;
    return 1;
    
  }
  
  if(!boost::filesystem::is_regular_file(runListPath)){
    
    std::cerr<<"Error: "<<runListPath<<" is not a regular file"<<std::endl;
    return 1;
    
  }
  else{
    
    RunStager::stageRunList(runListPath, dataPattern, fileExtension);
    
  }
  
}