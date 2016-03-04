#include "DataFormatter.hpp"
#include <iostream>
namespace RunStager {
  
  DataFormatter::DataFormatter(std::string pattern, std::string runNumberRegexString){
    
    std::regex runNumberRegex{runNumberRegexString};

    tokenziedPattern.assign(std::sregex_token_iterator(pattern.begin(), pattern.end(), runNumberRegex, -1), std::sregex_token_iterator());
    if(tokenziedPattern.size() < 2) throw std::runtime_error("'"+runNumberRegexString + "' does not match '" + pattern + "' before its end");

  }
  
  std::string DataFormatter::getTargetPath(const std::string& runNumber) const{
    
    std::string targetPath;
    
    for(auto it = tokenziedPattern.begin(); it != tokenziedPattern.end() - 1; ++it) targetPath += *it + runNumber;
    targetPath += *(tokenziedPattern.end() - 1);
    
    return targetPath;

  }
  
}