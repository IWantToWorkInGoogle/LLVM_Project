#include "app.h"

void app()
{
    bool new_state[SIM_X_SIZE][SIM_Y_SIZE];
    for (int step = 0; step < 1000; ++step)
    {
        for (int x = 0; x < SIM_X_SIZE; ++x)
        {
            for (int y = 0; y < SIM_Y_SIZE; ++y)
            {
                int count = 0;
                for (int i = -1;i <= 1;i++)
                {
                    for (int j = -1;j <= 1;j++)
                    {
                        if (!i && !j ||
                            x + i >= SIM_X_SIZE ||
                            y + j >= SIM_Y_SIZE ||
                            x + i < 0 ||
                            y + j < 0)
                        {
                            continue;
                        }

                        if (state[x + i][y + j])
                        {
                            count++;
                        }
                    }
                }
                if (!state[x][y] && count == 3 || state[x][y] && (count == 2 || count == 3))
                {
                    new_state[x][y] = true;
                }
                else
                {
                    new_state[x][y] = false;
                }
            }
        }

        for (int x = 0; x < SIM_X_SIZE; ++x)
        {
            for (int y = 0; y < SIM_Y_SIZE; ++y)
            {
                if (new_state[x][y])
                {
                    simPutPixel(x, y, 0xFFFFFF);
                }
                else
                {
                    simPutPixel(x, y, 0x000000);
                }

                state[x][y] = new_state[x][y];
            }
        }
        simFlush();
    }
}
