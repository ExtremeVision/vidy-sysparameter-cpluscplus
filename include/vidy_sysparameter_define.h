#ifndef VIDY_SYSPARAMETER_DEFINE_H_
#define VIDY_SYSPARAMETER_DEFINE_H_

#include <vector>

#define NORMAL_WIDTH 720
#define NORMAL_HEIGHT 1280

//define error string.
#define NO_ERROR "no error"

namespace vidy{

//----- define a point. -----------
struct Point{
  int x;
  int y;
};

//----- define a door line ---------
struct Doorline{
  Point p1;
  Point p2;
};
struct DoorDetail{
  int path_id;
  int type_id;
  int cb_type;
  Doorline detail;
};

//------ define a pathway.----------
// p1                    *
//    *                   * * * 
//    * * * * * * * * * * * * * * p3
//    *                   * * *
// p2                    *
struct Pathway{
  Point p1; // pathway begin left.
  Point p2; // pathway begin right.
  Point p3; // pathway end.
};
struct PathDetail{
  int path_id;
  int type_id;
  int cb_type;
  Pathway detail;
};

//------ define an area. -----------
typedef std::vector<Point> Area;
struct AreaDetail{
  int path_id;
  int type_id;
  int cb_type;
  Area detail;
};

//----- define entrance area. (include door line and area) ---
struct EntranceArea{
  int cb_type;
  Doorline doorline;
  Area area;
};

} // namespace vidy

#endif // VIDY_SYSPARAMETER_DEFINE_H_
