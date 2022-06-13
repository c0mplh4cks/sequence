const int horizontal = 12;
const int vertical = 5;

int horz[horizontal] = {13, 5, 10, 6, 12, 11, 7, A5, A4, A3, A2, A1};
int vert[vertical] = {9, 8, 0, 1, 4};

const int layers = 2;

int layout[layers][vertical][horizontal] = {
  {
    {0xb1,'1', '2', '3', '4', '5',    '6', '7', '8', '9', '0', 0xb2},
    {0xb3,'q', 'w', 'e', 'r', 't',    'y', 'u', 'i', 'o', 'p', '\\'},
    {0xc1,'a', 's', 'd', 'f', 'g',    'h', 'j', 'k', 'l', '\'',0xb0},
    {0x81,'z', 'x', 'c', 'v', 'b',    'n', 'm', ',', '.', '/', 0x85},
    {0,   0,   0,   0x80,0x82,0x20,   0x20,0,   0x83,0,   0,   0}
  },
  {
    {0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,   0xc8,0xc9,0xca,0xcb,0xcc,0xcd},
    {0xb3,0xd2,0xda,0xd5,0xd3,0,      0,   0,   0,   0,   0,   0},
    {0xc1,0xd8,0xd9,0xd7,0xd6,';',    '[', ']', '=', '-', '`', 0},
    {0x81,0,   0,   0,   0,   0,      0,   0,   0,   0,   0,   0},
    {0,   0,   0,   0x80,0x82,0x20,   0x20,0,   0x83,0,   0,   0},
  }
};

const int modifiers = 5;

int modifier[modifiers] = {
  0x82, 0x80, 0x81, 0x85, 0x83
};
