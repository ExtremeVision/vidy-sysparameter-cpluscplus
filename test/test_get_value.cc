#include "vidy_sysparameter.h"

int main(int argc,char* argv[]){

  vidy::VSysParameter* sysparameter = new vidy::VSysParameter();
  if(!sysparameter->Init("http://i.extremevision.com.cn/v2/all-cameras?access-token=733ZO5TjbI2Byurga8EY_JMjbBcnxJr4",186)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
  }

  // test get value by key name.
  std::string _value;
  std::cout<<"============ Test Get Value ==============="<<std::endl;
  if(!sysparameter->GetPara("model",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("floor",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("type",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("device_id",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("region",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("stream_addr",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("lan_addr",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("wan_addr",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("site_id",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }
  if(!sysparameter->GetPara("enter",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }

  std::cout<<"============== Test Print Result =================="<<std::endl;
  sysparameter->PrintValue("counter_count");
  sysparameter->PrintValue("exit");
  sysparameter->PrintValue("age");
  sysparameter->PrintValue("sex");
  sysparameter->PrintValue("path");

  std::cout<<"============= Test Get Value with No Key Name ====="<<std::endl;
  if(!sysparameter->GetPara("NoKeyName",&_value)){
    std::cout<<sysparameter->GetLastError()<<std::endl;
    return 0;
  }else{
    std::cout<<_value<<std::endl;
  }

  return 1;

}
