#include <string>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
    long h, m, s;
    string sh{"00"}, sm{"00"}, ss{"00"};
    h = seconds / 3600;
    m = (seconds - h * 3600) / 60;
    s = (seconds - h * 3600) % 60;

    if (h < 10){sh = "0" + std::to_string(h);}
    else {sh = std::to_string(h);}

    if (m < 10){sm = "0" + std::to_string(m);}
    else {sm = std::to_string(m);}

    if (s < 10){ss = "0" + std::to_string(s);}
    else {ss = std::to_string(s);}
    
    
    return sh + ":" + sm + ":" + ss; 
}