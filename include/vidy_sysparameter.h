//Copyright(c) 2016 Extreme Vision Ltd. All rights reserved.
//File:vidy_sysparameter.h
//Version:1.0
//Author: Yun Luo(lauren.luo@extremevision.mo)
//Description: Get parameters from system.
//Note. "Init()" function should be used first, then other functions can be easily applied.

#ifndef VIDY_SYSPARAMETER_H_
#define VIDY_SYSPARAMETER_H_

#include <string>
#include <vector>
#include <iostream>

#include "vidy_sysparameter_define.h"

#include "cJSON/cJSON.h"

namespace vidy{

class VSysParameter{

public:

  VSysParameter();

  ~VSysParameter();

  VSysParameter(std::string url,int cid){
    this->Init(url,cid);
  }

  //@param url: API address, different region may have different url.
  //@param cid: camera id in system.
  //@return 1: init success.
  //@return 0: init failed.
  int Init(std::string url,int cid);

  //@param key_name: key name in JSON string.
  //@return value: value in JSON string.
  //@return 1: get value success.
  //@return 0: get value failed.
  //Description: This function can only get one value.
  int GetPara(std::string key_name,std::string* value);

  //@param frame_width,frame_height:
  //@return doorline: door line details in JSON that resized by frame size.
  //@return 1: get door line success.
  //@return 0: get door line failed.
  //note. only one door line situation.
  int GetDoorDetail(std::vector<DoorDetail>* door_details,int frame_width=NORMAL_WIDTH,int frame_height=NORMAL_HEIGHT);

  //@param frame_width,frame_height: width and height of frame, default values are 720(frame_height) and 1280(frame_width).
  //@return path_details: pathway details in JSON  that resized by frame size.
  //@return 1: get path details success.
  //@return 0: get path details failed.
  int GetPathDetail(std::vector<PathDetail>* path_details,int frame_width=NORMAL_WIDTH,int frame_height=NORMAL_HEIGHT);

  //@param frame_width,frame_height: width and height of frame, default values are 720(frame_height) and 1280(frame_width).
  //@return area_details: area details in JSON  that resized by frame size.
  //@return 1: get area details success.
  //@return 0: get area details failed.
  int GetAreaDetail(std::vector<AreaDetail>* area_details,int frame_width=NORMAL_WIDTH,int frame_height=NORMAL_HEIGHT);

  //@param frame_width,frame_height: width and height of frame, default values area 720(frame_height) and 1280(frame_width).
  //@return entrance_areas: combine both doorline and area that in the same cb_type as a entrance area.
  //@return 1: get entrance area success.
  //@return 0: get entrance area failed.
  int GetEntranceArea(std::vector<EntranceArea>* entrance_areas,int frame_width=NORMAL_WIDTH,int frame_height=NORMAL_HEIGHT);

  //return: get last error description.
  inline std::string GetLastError(){
    return last_error_string;
  }

  //print value.
  inline void PrintValue(std::string key_name){
    std::string value;
    if(this->GetPara(key_name,&value)){
      std::cout<<"Key:"<<key_name<<" Value:"<<value<<std::endl;
    }else{
      std::cout<<key_name<<": parse error."<<std::endl;
    }
  }

  //print result of function GetDoorDetail.
  void PrintDoorDetail(std::vector<DoorDetail>& door_details);
  
  //print result of function GetPathDetail.
  void PrintPathDetail(std::vector<PathDetail>& path_details);

  //print result of function GetAreaDetail.
  void PrintAreaDetail(std::vector<AreaDetail>& area_details);

  //print result of function GetEntranceArea.
  void PrintEntranceArea(std::vector<EntranceArea>& entrance_areas);

protected:
  //@param doorline_detail_string: "detail" of door line json.
  //@return door_detail: door detail points.
  //@return 0: failed.
  //@return 1: success.
  int GetDoorDetailPoints(int frame_width,int frame_height,std::string doorline_detail_string,Doorline* door_detail);

  //@param pathway_detail_string: "detail" of one pathway json.
  //@return path_detail: path detail points.
  //@return 0: failed.
  //@return 1: success.
  int GetPathDetailPoints(int frame_width,int frame_height,std::string pathway_detail_string,Pathway* path_detail);

  //@param area_detail_string: "detail" of one area json.
  //@return area_detail: area detail points.
  //@return 0: failed.
  //@return 1: success.
  int GetAreaDetailPoints(int frame_width,int frame_height,std::string area_detail_string,Area* area_detail);


private:
  cJSON* pJson;
  std::string last_error_string;

}; // class VSysParameter

} // namepace vidy

#endif // VIDY_SYSPARAMETER_H_


