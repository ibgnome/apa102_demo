#define PIN1 5
#define PIN2 6
#define PIN3 7
#define PIN4 8

Button btnA(PIN1);
Button btnB(PIN2);
Button btnC(PIN3);
Button btnD(PIN4);

// Sets params for the Fire function
#define SPARKING 200
#define COOLING  200
#define HOT 300
#define MAXHOT HOT*HEIGHT
#define MAX_DIMENSION ((WIDTH>HEIGHT) ? WIDTH : HEIGHT)

uint16_t Options;
uint8_t angle = 0;
int randcount, randbrow, countup, countdown;
int count, eye_count, mcount, cube_count, mauscount, zcount = 0;
uint8_t hue = 0;
uint8_t gHue = 0;
int16_t counter = 0;

uint16_t PlasmaTime, PlasmaShift;

bool gReverseDirection = false;

static uint16_t f;
static uint16_t g;
static uint16_t h;
uint16_t scale = 20;
uint16_t speed = 2;


int state=1;
int nextstate = 0;
int bright = 20;
