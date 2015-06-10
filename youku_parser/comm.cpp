#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

std::string na(const std::string &value) {
    if (value.empty()) {
        return "";
    }

    int h[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53,
            54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2,
            3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
            22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32,
            33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
            50, 51, -1, -1, -1, -1, -1 };
    int i = value.length();
    std::string a = value;
    int f = 0;
    int c = 0;
    int b = 0;
    std::string e = "";
    for (e = ""; f < i;) {
        do {
            c = h[(int) a[f++] & 255];
        } while (f < i && -1 == c);

        if (-1 == c) {
            break;
        }

        do {
            if (f >= i) {
                b = 0;
            } else {
                b = h[(int) a[f++] & 255];
            }
        } while (f < i && -1 == b);

        if (-1 == b)
            break;

        e += (char) (c << 2 | (b & 48) >> 4);

        do {
            if (f >= i) {
                c = 0;
            } else {
                c = (int) a[f++] & 255;
            }
            if (61 == c)
                return e;
            c = h[c];
        } while (f < i && -1 == c);
        if (-1 == c)
            break;
        e += (char) ((b & 15) << 4 | (c & 60) >> 2);
        do {
            if (f >= i) {
                b = 0;
            } else {
                b = (int) a[f++] & 255;
            }
            if (61 == b)
                return e;
            b = h[b];
        } while (f < i && -1 == b);
        if (-1 == b)
            break;
        e += (char) ((c & 3) << 6 | b);
    };

    return e;
}

std::string E(const std::string &a, const std::string &cc) {
    std::string c = cc;
    std::string value = a;

    std::string e = "";
    int *b = new int[256];
    int h = 0;
    int i = 0;
    int f = 0;

    for (h = 0; 256 > h; h++) {
        b[h] = h;
    }

    for (h = 0; 256 > h; h++) {
        f = (f + b[h] + (int) value[h % value.length()]) % 256;

        i = b[h];
        b[h] = b[f];
        b[f] = i;
    }

    f = 0;
    h = 0;
    for (int q = 0; q < (int)c.length(); q++) {
        h = (h + 1) % 256;
        f = (f + b[h]) % 256;
        i = b[h];
        b[h] = b[f];
        b[f] = i;
        e += (char) ((int) c[q] ^ b[(b[h] + b[f]) % 256]);
    }
    return e;
}

std::string F(const std::string &value, int *c) {
    std::string a = value;
    char *b = new char[a.length()];
    int i = 0;

    for(int f=0;f<(int)a.length();f++) {
        int e = 0;
        for(i= ((int) 'a'<=(int)a[f]&&(int)'z'>=(int)a[f]) ? (int)a[f]-97:atoi(&a[f])-0+26;36>e;e++) {
            if(c[e]==i) {
                i=e;
                break;
            }
        }
        if (25 < i) {
            char tmp_ch[32];
            sprintf(tmp_ch, "%d", i - 26);
            b[f] = tmp_ch[0];
        } else {
            b[f] = (char) (i + 97);
        }
    }
    std::string result = "";

    for (i = 0; i < (int)a.length(); i++) {
        result += (char)b[i];
    }

    return result;
}

std::string D(const std::string &value) {
    if (value.empty()) {
        return "";
    }
    std::string a = value;
    char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int f = a.length();
    int b = 0;
    std::string c = "";

    for (c = ""; b < f;) {
        int e = (int) a[b++] & 255;
        if (b == f) {
            c += base[e >> 2];
            c += base[(e & 3) << 4];
            c += "==";
            break;
        }
        int g = a[b++];
        if (b == f) {
            c += base[e >> 2];
            c += base[(e & 3) << 4 | (g & 240) >> 4];
            c += base[(g & 15) << 2];
            c += "=";
            break;
        }
        int h = a[b++];
        c += base[e >> 2];
        c += base[(e & 3) << 4 | (g & 240) >> 4];
        c += base[(g & 15) << 2 | (h & 192) >> 6];
        c += base[h & 63];
    }

    return c;
}



int main ( int argc, char *argv[] )
{

    int a[] = {19,1,4,7,30,14,28,8,24,17,6,35,34,16,9,10,13,22,32,29,31,21,18,3,2,23,25,27,11,20,5,15,12,0,33,26};
    string ep = "MwXTTQQcILnT1/DB8eJxU9SmuBZr1wjIWRw=";
    std::string cc = E(F("b4eto0b4", a), na(ep));
    cout << cc << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
