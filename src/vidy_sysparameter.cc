#include "vidy_sysparameter.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


namespace vidy{

VSysParameter::VSysParameter(){
  last_error_string = NO_ERROR;
  pJson = NULL;
}

VSysParameter::~VSysParameter(){
  cJSON_Delete(pJson);
}

int VSysParameter::Init(std::string url,int cid){
  FILE *pp;
  char json_string[5*BUFSIZ];
  char command[2048];
  sprintf(command,"curl %s\'&\'cid=%d",url.c_str(),cid);
  if (NULL != (pp = popen(command, "r"))){
      fread(json_string,sizeof(json_string), 1, pp);
  }else{
      last_error_string = command;
      last_error_string += " open error.";
      pclose(pp);
      return 0;
  }
  pclose(pp);
  pJson = cJSON_Parse(json_string);
  if(NULL==pJson){
    last_error_string = "json parse error.";
    return 0;
  }
  return 1;
}

int VSysParameter::GetPara(std::string key_name,std::string* value){
  cJSON* pSub = cJSON_GetObjectItem(pJson,key_name.c_str());
  if(NULL == pSub){
    last_error_string = key_name;
    last_error_string += " parse error.";
    return 0;
  }else{
    if(!pSub->valuestring){
      last_error_string = key_name;
      last_error_string += " null.";
      return 0;
    }
    (*value) = pSub->valuestring;
    return 1;
  }
}

int VSysParameter::GetDoorDetailPoints(int frame_width,int frame_height,std::string doorline_detail_string,Doorline* door_detail){
  char str[100]="";
  sscanf(doorline_detail_string.data(),"{%[^}]}",str);
  const char* split=":,";
  char* p;
  p=strtok(str,split);
  int _count = 0;
  int _point_num = 0;
  Point _point;
  while(p!=NULL){
    _count++;
    switch(_count%4){
      case 1:{
        break;
      }
      case 2:{;
        int len = sizeof(p);
        char* x = new char(len-3);
        x = p+1;
        _point.x = (int)(atoi(x)*frame_width/1280);
        break;
      }
      case 3:{
        break;
      }
      case 0:{
        int len = sizeof(p); 
        char* y = new char(len-3);
        y = p+1;
        _point.y = (int)(atoi(y)*frame_height/720);
        _point_num++;  
        switch(_point_num){
          case 1:
            (*door_detail).p1 = _point;
            break;
          case 2:
            (*door_detail).p2 = _point;
            break;
        }
        break;
      }
    }
    p=strtok(NULL,split);
  }

  if(_point_num==0){
    last_error_string = "no door line points."; 
    return 0;
  }
  if(_point_num>2){
    last_error_string = "door line points are more than two.";
    return 0;
  }
  
  return 1;

}

int VSysParameter::GetDoorDetail(std::vector<DoorDetail>* door_details,int frame_width,int frame_height){
  cJSON* pJsonArray = cJSON_GetObjectItem(pJson,"door_way_detail");
  if(NULL==pJsonArray){
    last_error_string = "no door_way_detail or parse error.";
    return 0;
  }
  cJSON* pSub = NULL;
  cJSON* list = pJsonArray->child;
  while(list!=NULL){
    DoorDetail door_detail;
    pSub = cJSON_GetObjectItem(list,"path_id");
    door_detail.path_id = atoi(pSub->valuestring);
    pSub = cJSON_GetObjectItem(list,"type_id");
    door_detail.type_id = atoi(pSub->valuestring);
    pSub = cJSON_GetObjectItem(list,"cb_type");
    door_detail.cb_type = atoi(pSub->valuestring);
    pSub = cJSON_GetObjectItem(list,"detail");
    Doorline _doorline;
    if(this->GetDoorDetailPoints(frame_width,frame_height,pSub->valuestring,&_doorline)){
      door_detail.detail = _doorline;
    }
    (*door_details).push_back(door_detail);
    list = list->next;
  }
  return 1;
}

int VSysParameter::GetPathDetailPoints(int frame_width,int frame_height,std::string pathway_detail_string,Pathway* path_detail){
  char str[100]="";
  sscanf(pathway_detail_string.data(),"{%[^}]}",str);
  const char* split=":,";
  char* p;
  p=strtok(str,split);
  int _count = 0;
  int _point_num = 0;
  Point _point;
  while(p!=NULL){
    _count++;
    switch(_count%4){
      case 1:{
        _point_num++;
        break;
      }
      case 2:{
        int len = sizeof(p);
        char* x = new char(len-3);
        x = p+1;
        _point.x = (int)(atoi(x)*frame_width/1280);
        break;
      }
      case 3:{
        break;
      }
      case 0:{
        int len = sizeof(p);
        char* y = new char(len-3);
        y = p+1;
        _point.y = (int)(atoi(y)*frame_height/720);
        switch(_point_num){
          case 1:
            (*path_detail).p1 = _point;
            break;
          case 2:
            (*path_detail).p2 = _point;
            break;
          case 3:
            (*path_detail).p3 = _point;
            break;
        }
        break;
      }
    }
    p=strtok(NULL,split);
  }
  if(_point_num==0){
    last_error_string = "no path detail points.";
    return 0;
  }
  return 1;

}

int VSysParameter::GetPathDetail(std::vector<PathDetail>* path_details,int frame_width,int frame_height){
  cJSON* pJsonArray = cJSON_GetObjectItem(pJson,"path_detail");
  if(NULL==pJsonArray){
    last_error_string = "no pathway detail or parse error.";
    return 0;
  }
  cJSON* pSub = NULL;
  cJSON* list=pJsonArray->child;
  while(list!=NULL){
    cJSON* group = list->child;
    while(group!=NULL){
      PathDetail path_detail;
      pSub = cJSON_GetObjectItem(group,"path_id");
      path_detail.path_id = atoi(pSub->valuestring);
      pSub = cJSON_GetObjectItem(group,"type_id");
      path_detail.type_id = atoi(pSub->valuestring);
      pSub = cJSON_GetObjectItem(group,"cb_type");
      path_detail.cb_type = atoi(pSub->valuestring);
      pSub = cJSON_GetObjectItem(group,"detail");
      Pathway _pathway;
      if(this->GetPathDetailPoints(frame_width,frame_height,pSub->valuestring,&_pathway)){
        path_detail.detail = _pathway;
      }
      (*path_details).push_back(path_detail);
      group = group->next;
    }
    list = list->next;
  }
  return 1;
}

int VSysParameter::GetAreaDetailPoints(int frame_width,int frame_height,std::string area_detail_string,Area* area_detail){
  char str[1024]="";
  sscanf(area_detail_string.data(),"{%[^}]}",str);
  const char* split=":,";
  char* p;
  p=strtok(str,split);
  int _count = 0;
  int _point_num = 0;
  Point _point;
  while(p!=NULL){
    _count++;
    switch(_count%4){
      case 1:{
        _point_num++;
        break;
      }
      case 2:{
        int len = sizeof(p);
        char* x = new char(len-3);
        x = p+1;
        _point.x = atoi(x)*frame_width/1280;
        break;
      }
      case 3:{
        break;
      }
      case 0:{
        int len = sizeof(p);
        char* y = new char(len-3);
        y = p+1;
        _point.y = atoi(y)*frame_height/720;
        (*area_detail).push_back(_point);
        break;
      }
    }
    p=strtok(NULL,split);
  }
  if(_count==0){
    last_error_string = "no area detail points.";
    return 0;
  }
  return 1;
}

int VSysParameter::GetAreaDetail(std::vector<AreaDetail>* area_details,int frame_width,int frame_height){
  cJSON* pJsonArray = cJSON_GetObjectItem(pJson,"area_detail");
  if(NULL==pJsonArray){
    last_error_string = "no area detail or parse error.";
    return 0;
  }
  cJSON* list=pJsonArray->child;
  cJSON* pSub = NULL;
  while(list!=NULL){
    AreaDetail area_detail;
    pSub = cJSON_GetObjectItem(list,"path_id");
    area_detail.path_id = atoi(pSub->valuestring);
    pSub = cJSON_GetObjectItem(list,"type_id");
    area_detail.type_id = atoi(pSub->valuestring);
    pSub = cJSON_GetObjectItem(list,"cb_type");
    area_detail.cb_type = atoi(pSub->valuestring);
    pSub = cJSON_GetObjectItem(list,"detail");
    Area _area;
    if(this->GetAreaDetailPoints(frame_width,frame_height,pSub->valuestring,&_area)){
       area_detail.detail = _area;
    }
    (*area_details).push_back(area_detail);
    list = list->next;
  }
  return 1;

}

int VSysParameter::GetEntranceArea(std::vector<EntranceArea>* entrance_areas,int frame_width,int frame_height){
  std::vector<DoorDetail> door_details;
  this->GetDoorDetail(&door_details,frame_width,frame_height);
  std::vector<AreaDetail> area_details;
  this->GetAreaDetail(&area_details,frame_width,frame_height);
  if(door_details.size()!=area_details.size()){
    last_error_string = "door line number is not equal to area number";
    return 0;
  }
  for(int i=0;i<door_details.size();i++){
    int cb_type = door_details[i].cb_type;
    EntranceArea entrance_area;
    entrance_area.cb_type = cb_type;
    entrance_area.doorline = door_details[i].detail;
    for(int j=0;j<area_details.size();j++){
      if(area_details[j].cb_type==cb_type){
        entrance_area.area = area_details[j].detail;
        break;
      }
    }
    (*entrance_areas).push_back(entrance_area);
  }
  return 1;
}

void VSysParameter::PrintDoorDetail(std::vector<DoorDetail>& door_details){

  std::cout<<"=============== Doorline ==================="<<std::endl;
  for(unsigned int i=0;i<door_details.size();i++){
    std::cout<<"path_id:"<<door_details[i].path_id<<std::endl;
    std::cout<<"type_id:"<<door_details[i].type_id<<std::endl;
    std::cout<<"cb_type:"<<door_details[i].cb_type<<std::endl;
    std::cout<<"path_detail:"<<std::endl;
    std::cout<<"p1.x:"<<door_details[i].detail.p1.x<<" p1.y:"<<door_details[i].detail.p1.y<<std::endl;
    std::cout<<"p2.x:"<<door_details[i].detail.p2.x<<" p2.y:"<<door_details[i].detail.p2.y<<std::endl;
    std::cout<<"-----------------------------------------"<<std::endl;
  }
  if(door_details.size()==0){
    std::cout<<"no doorlines"<<std::endl;
  }
}

void VSysParameter::PrintPathDetail(std::vector<PathDetail>& path_details){

  std::cout<<"=============== Pathways ==================="<<std::endl;
  for(unsigned int i=0;i<path_details.size();i++){
    std::cout<<"path_id:"<<path_details[i].path_id<<std::endl;
    std::cout<<"type_id:"<<path_details[i].type_id<<std::endl;
    std::cout<<"cb_type:"<<path_details[i].cb_type<<std::endl;
    std::cout<<"path_detail:"<<std::endl;
    std::cout<<"p1.x:"<<path_details[i].detail.p1.x<<" p1.y:"<<path_details[i].detail.p1.y<<std::endl;
    std::cout<<"p2.x:"<<path_details[i].detail.p2.x<<" p2.y:"<<path_details[i].detail.p2.y<<std::endl;
    std::cout<<"p3.x:"<<path_details[i].detail.p3.x<<" p3.y:"<<path_details[i].detail.p3.y<<std::endl;
    std::cout<<"-----------------------------------------"<<std::endl;
  }
  if(path_details.size()==0){
    std::cout<<"no pathways"<<std::endl;
  }
}

void VSysParameter::PrintAreaDetail(std::vector<AreaDetail>& area_details){

  std::cout<<"================ Areas ==================="<<std::endl;
  for(unsigned int i=0;i<area_details.size();i++){
    std::cout<<"path_id:"<<area_details[i].path_id<<std::endl;
    std::cout<<"type_id:"<<area_details[i].type_id<<std::endl;
    std::cout<<"cb_type:"<<area_details[i].cb_type<<std::endl;
    std::cout<<"path_detail:"<<std::endl;
    for(unsigned int j=0;j<area_details[i].detail.size();j++){
      std::cout<<"p"<<j<<".x:"<<area_details[i].detail[j].x<<" p"<<j<<".y:"<<area_details[i].detail[j].y<<std::endl;
    }
    std::cout<<"---------------------------------------"<<std::endl;
  }
  if(area_details.size()==0){
    std::cout<<"no areas."<<std::endl;
  }

}

void VSysParameter::PrintEntranceArea(std::vector<EntranceArea>& entrance_areas){

  std::cout<<"============== Entrance Areas ==========="<<std::endl;
  for(int i=0;i<entrance_areas.size();i++){
    std::cout<<"cb_type:"<<entrance_areas[i].cb_type<<std::endl;
    std::cout<<"door_line:"<<std::endl;
    std::cout<<"p1.x:"<<entrance_areas[i].doorline.p1.x<<" p1.y:"<<entrance_areas[i].doorline.p1.y<<std::endl;
    std::cout<<"p2.x:"<<entrance_areas[i].doorline.p2.x<<" p2.y:"<<entrance_areas[i].doorline.p2.y<<std::endl;
    std::cout<<"area:"<<std::endl;
    for(int j=0;j<entrance_areas[i].area.size();j++){
      std::cout<<"p"<<j<<".x:"<<entrance_areas[i].area[j].x<<" p"<<j<<".y"<<entrance_areas[i].area[j].y<<std::endl;
    }
    std::cout<<"----------------------------------------"<<std::endl;
  }
  if(entrance_areas.size()==0){
    std::cout<<"no entrance areas."<<std::endl;
  }

}

} // namespace vidy
