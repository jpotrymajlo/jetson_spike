#include "liba.h"
#include <fmt/color.h>

A::A(){
     fmt::print(fg(fmt::terminal_color::cyan), "Hello fmt {}!\n", FMT_VERSION );   
}

