#define SIM_X_SIZE 512
#define SIM_Y_SIZE 256
#include <stdbool.h>

bool state[SIM_X_SIZE][SIM_Y_SIZE];

void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
