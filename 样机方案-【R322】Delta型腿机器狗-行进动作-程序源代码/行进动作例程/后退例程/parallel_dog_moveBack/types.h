typedef unsigned int uint;

/***** 二维坐标点结构体 *****/
struct Point
{
  float x;
  float y;
};

/***** 三维坐标点结构体 *****/
struct Point3d
{
  float x;
  float y;
  float z;
};

/***** 动作模式 *****/
typedef enum dog_mode
{
	DOG_MODE_FRONT,
	DOG_MODE_BACK,
  DOG_MODE_LEFT,
  DOG_MODE_RIGHT,
  DOG_MODE_LEFT_FRONT,
  DOG_MODE_RIGHT_FRONT,
  DOG_MODE_LEFT_BACK,
  DOG_MODE_RIGHT_BACK,
  DOG_MODE_TURN_LEFT,
  DOG_MODE_TURN_RIGHT,
  DOG_MODE_STOP
} dogMode;

/***** 平衡调节状态 *****/
#define ADJUST_STAT_OFF   0 // 未启用平衡调节
#define ADJUST_STAT_LEG   1 // 原地平衡调节
#define ADJUST_STAT_TRACK 2 // 行进间平衡调节
