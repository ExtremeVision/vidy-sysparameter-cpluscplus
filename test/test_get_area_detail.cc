#include "vidy_sysparameter.h"

int main(int argc,char* argv[]){

  vidy::VSysParameter* sysparameter = new vidy::VSysParameter();
  if(!sysparameter->Init("http://i.extremevision.com.cn/v2/all-cameras?access-token=733ZO5TjbI2Byurga8EY_JMjbBcnxJr4",186)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
  }

  std::vector<vidy::AreaDetail> area_details;
  if(!sysparameter->GetAreaDetail(&area_details)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }

  sysparameter->PrintAreaDetail(area_details);

  //delete sysparameter;

  return 1; 
}


