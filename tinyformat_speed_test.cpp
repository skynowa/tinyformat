#if defined(__linux__) && defined(__clang__)
// Workaround for bug in gcc 4.4 standard library headers when compling with
// clang in C++11 mode.
namespace std { class type_info; }
#endif

#include <boost/format.hpp>
#include <iomanip>
#include <stdio.h>
#include "tinyformat.h"
#include <xLib/Core/Format.h>

void speedTest(const std::string& which)
{
    const long loops = 2000000L;

    #define str "asdcf'awsrk.fw3[045im2,[4oc'wxe;/fzd1[-,c4rxj.wk;szlcgjx34-rx134rxqwetaertg"

    // Following is required so that we're not limited by per-character buffering
    std::ios_base::sync_with_stdio(false);

    if (which == "std::printf") {
        for (long i = 0; i < loops; ++ i) {
            std::printf("%0.10f" str "%04d" str "%+g" str "%s" str "%p" str "%c" str "%%\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }
    }
    else if (which == "std::iostreams") {
        for (long i = 0; i < loops; ++ i) {
            std::cout
                << std::setprecision(10) << std::fixed << 1.234
                << std::resetiosflags(std::ios::floatfield) << str
                << std::setw(4) << std::setfill('0') << 42 << std::setfill(' ') << str
                << std::setiosflags(std::ios::showpos) << 3.13 << std::resetiosflags(std::ios::showpos) << str
                << "string" << str
                << (void *)1000 << str
                << 'X' << str "%\n";
        }
    }
    else if (which == "tinyformat") {
        for (long i = 0; i < loops; ++ i) {
            tfm::printf("%0.10f" str "%04d" str "%+g" str "%s" str "%p" str "%c" str "%%\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }
    }
    else if (which == "boost::format") {
        for (long i = 0; i < loops; ++ i) {
            std::cout << boost::format("%0.10f" str "%04d" str "%+g" str "%s" str "%p" str "%c" str "%%\n")
                % 1.234 % 42 % 3.13 % "string" % (void *)1000 % (int)'X';
        }
    }
    else if (which == "xlib::core::String::format") {
        for (long i = 0; i < loops; ++ i) {
            std::cout << xlib::core::String::format("%0.10f" str "%04d" str "%+g" str "%s" str "%p" str "%c" str "%%\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }
    }
    else if (which == "xlib::Format") {
        for (long i = 0; i < loops; ++ i) {
            std::cout << xlib::core::Format("{}" str "{}" str "{}" str "{}" str "{}" str "{}" str "{}\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }
    }
    else {
        assert(0 && "Speed test for which version?");
    }
}


int main(int argc, char* argv[])
{
    if (argc >= 2) {
        speedTest(argv[1]);
    }

    return 0;
}
