#include "vidy_sysparameter.h"

int main(int argc,char* argv[]){

  vidy::VSysParameter* sysparameter = new vidy::VSysParameter();
  if(!sysparameter->Init("http://i.extremevision.com.cn/v2/all-cameras?access-token=733ZO5TjbI2Byurga8EY_JMjbBcnxJr4",186)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
  }
  //get value.
  std::string value;
  if(!sysparameter->GetPara("type",&value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<value<<std::endl;
  }  

  //get door line.
  std::vector<vidy::DoorDetail> door_details;
  if(!sysparameter->GetDoorDetail(&door_details)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    sysparameter->PrintDoorDetail(door_details);
  }
 
  //get pathways.
  std::vector<vidy::PathDetail> path_details;
  if(!sysparameter->GetPathDetail(&path_details)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    sysparameter->PrintPathDetail(path_details);
  }

  //get areas.
  std::vector<vidy::AreaDetail> area_details;
  if(!sysparameter->GetAreaDetail(&area_details)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    sysparameter->PrintAreaDetail(area_details);
  }

  delete sysparameter;

  return 1; 
}


