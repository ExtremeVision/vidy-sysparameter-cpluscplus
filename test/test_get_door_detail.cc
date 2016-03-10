#include "vidy_sysparameter.h"

int main(int argc,char* argv[]){

  vidy::VSysParameter* sysparameter = new vidy::VSysParameter();
  if(!sysparameter->Init("http://i.extremevision.com.cn/v2/all-cameras?access-token=733ZO5TjbI2Byurga8EY_JMjbBcnxJr4",184)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
  }

  vidy::DoorDetail door_detail;
  if(!sysparameter->GetDoorDetail(&door_detail)){
    sysparameter->GetLastError();
    return 0;
  }

  sysparameter->PrintDoorDetail(door_detail);

  delete sysparameter;

  return 1; 
}


