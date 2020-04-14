#include <iostream>
#include <vector>

int main()
{


                // 2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  A  |
            {{ActionType.HIT} ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 8
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 9
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 10
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 11
            {true ,true ,false,false,false,true ,true ,true ,true ,true }, // 12
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 13
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 14
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 15
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 16
            {false,false,false,false,false,false,false,false,false,false}, // 17
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 2-2
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 3-3
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 4-4
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 5-5
            {true ,true ,false,false,false,true ,true ,true ,true ,true }, // 6-6
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 7-7
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 8-8
            {false,false,false,false,false,false,false,false,false,false}, // 9-9
            {false,false,false,false,false,false,false,false,false,false}, // 10-10
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A-A
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A2
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A3
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A4
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A5
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A6
            {false,false,false,false,false,false,false,true ,true ,true }, // A7
            {false,false,false,false,false,false,false,false,false,false}, // A8
            {false,false,false,false,false,false,false,false,false,false} // A9
        },
        doubleDown{
            // 2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  A  |
            {false,false,false,false,false,false,false,false,false,false}, // 8
            {false,true ,true ,true ,true ,false,false,false,false,false}, // 9
            {true ,true ,true ,true ,true ,true ,true ,true ,false,false}, // 10
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,false}, // 11
            {false,false,false,false,false,false,false,false,false,false}, // 12
            {false,false,false,false,false,false,false,false,false,false}, // 13
            {false,false,false,false,false,false,false,false,false,false}, // 14
            {false,false,false,false,false,false,false,false,false,false}, // 15
            {false,false,false,false,false,false,false,false,false,false}, // 16
            {false,false,false,false,false,false,false,false,false,false}, // 17
            {false,false,false,false,false,false,false,false,false,false}, // 2-2
            {false,false,false,false,false,false,false,false,false,false}, // 3-3
            {false,false,false,false,false,false,false,false,false,false}, // 4-4
            {true ,true ,true ,true ,true ,true ,true ,true ,false,false}, // 5-5
            {false,false,false,false,false,false,false,false,false,false}, // 6-6
            {false,false,false,false,false,false,false,false,false,false}, // 7-7
            {false,false,false,false,false,false,false,false,false,false}, // 8-8
            {false,false,false,false,false,false,false,false,false,false}, // 9-9
            {false,false,false,false,false,false,false,false,false,false}, // 10-10
            {false,false,false,false,true ,false,false,false,false,false}, // A-A
            {false,false,false,false,true ,false,false,false,false,false}, // A2
            {false,false,false,true ,true ,false,false,false,false,false}, // A3
            {false,false,true ,true ,true ,false,false,false,false,false}, // A4
            {false,false,true ,true ,true ,false,false,false,false,false}, // A5
            {false,true ,true ,true ,true ,false,false,false,false,false}, // A6
            {false,true ,true ,true ,true ,false,false,false,false,false}, // A7
            {false,false,false,false,false,false,false,false,false,false}, // A8
            {false,false,false,false,false,false,false,false,false,false}, // A9
        },
        split{
            // 2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  A  |
            {true ,true ,true ,true ,true ,true ,false,false,false,false}, // 2-2
            {true ,true ,true ,true ,true ,true ,false,false,false,false}, // 3-3
            {false,false,false,true ,true ,false,false,false,false,false}, // 4-4
            {false,false,false,false,false,false,false,false,false,false}, // 5-5
            {true ,true ,true ,true ,true ,false,false,false,false,false}, // 6-6
            {true ,true ,true ,true ,true ,true ,false,false,false,false}, // 7-7
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 8-8
            {true ,true ,true ,true ,true ,false,true ,true ,false,false}, // 9-9
            {false,false,false,false,false,false,false,false,false,false}, // 10-10
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A-A
        }
    std::vector<int> a[2][3] = {
        {{1,346,3467,3},{34,1},{1}},
        {{1},{3,3,3,3,3,3,31},{1}}
    };

    for (int i=0; i < 2; ++i)
    {
        for (int j=0; j < 3; ++j)
        {
            std::cout << "{";
            for (int k : a[i][j])
            {
                std::cout << k << ",";
            }
            std::cout << "},";
        }
        std::cout << std::endl;
    }

    return 0;
}
