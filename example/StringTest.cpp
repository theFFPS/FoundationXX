// SPDX-License-Identifier: GPL-2.0-or-later

#include <FoundationXX/String>
#include <cstdio>
#include <string>
using namespace foundation;

int main() {
    AsciiString string = "Hello World!";
    printf("%s\n", string.data());
}