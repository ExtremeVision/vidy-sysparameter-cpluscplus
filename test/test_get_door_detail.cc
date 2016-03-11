#include "vidy_sysparameter.h"

int main(int argc,char* argv[]){

  vidy::VSysParameter* sysparameter = new vidy::VSysParameter();
  if(!sysparameter->Init("http://i.extremevision.com.cn/v2/all-cameras?access-token=733ZO5TjbI2Byurga8EY_JMjbBcnxJr4",184)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
  }

  std::vector<vidy::DoorDetail> door_details;
  if(!sysparameter->GetDoorDetail(&door_details)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    sysparameter->PrintDoorDetail(door_details);
  }
  delete sysparameter;

  return 1; 
}


