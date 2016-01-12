
using namespace std;
enum KeyState { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_FIRE };
typedef std::bitset<5> Keys;
enum PositionType {NONE,PTREE,RIVER,MOUNTAIN,CIRCLE,BOX,BOOKED};
enum Bullettype{AL_BULLET,COM_BULLET};
enum Direction{LEFT,RIGHT,UP,DOWN};
enum Ptype{COM,AL};



struct Bullet
{
	int i;
	int j;
	int pid;
	Bullettype btype;
	Direction dir;
};

struct Apple
{
	int i;
	int j;
};


struct Commando
{
	int isauto;
	char name[30];
	static int count;
     int i;
	int j;
	int energy;
	Direction dir;
	int score;
	int pid;
};

struct Alien
{
	int isauto;
	char name[30];
	static int count;
     int i;
	int j;
	int energy;
	Direction dir;
	int score;
	int pid;
};

