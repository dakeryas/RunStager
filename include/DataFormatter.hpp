#ifndef RUN_STAGER_DATA_FORMATTER_H
#define RUN_STAGER_DATA_FORMATTER_H

#include <regex>

namespace RunStager{

  class DataFormatter{
  
    std::vector<std::string> tokenziedPattern;
    
  public:
    DataFormatter(std::string pattern, std::string runNumberRegexString);
    std::string getTargetPath(const std::string& runNumber) const;
  
  };
  
}

#endif