/**
 * \file   tinyformat_speed_test.cpp
 * \brief
 */


#include <iomanip>
#include <stdio.h>
#include "tinyformat.h"
#include <boost/format.hpp>
#include <xLib/Core/Format.h>
//-------------------------------------------------------------------------------------------------
void
speedTest(
    const std::string& a_testName
)
{
    const std::size_t loops = 2000000;

    #define str1 \
        "asdcf'awsrk.fw3[045im2,[4oc'wxe;/fzd1[-,c4rxj.wk;szlcgjx34-rx134rxqwetaertg" \
        "dsfgvsdfgshvdrtfghdfgh.,smdf.gknsd/f.sn;klfsn/dgmw4o5iut6c;w4o5ipt2[45pot[f" \
        "2341c4io mweroic4posdfcgsdfgcsdfgdfgsdfgsdfgsdfgcsdytbyfghbjfjkfybkjfgxdcfg" \
        "fghbjfghjfghjbfghjfghjbfghjfghjfgbhbjftgy jjk;.kpp,hgfvcddfghhnmknbdcfbgfcg" \
        "asdcf'awsrk.fw3[045im2,[4oc'wxe;/fzd1[-,c4rxj.wk;szgfhbjgfh4-rx4rxqwetaertg" \
        "acsfgvdbfghnjkllnffgcvgfbjnyhnl;/fzd1[-,c4rxj.wk;szlcgjx34-rx134rxqwetaertg" \
        "asdcf'awsrk.fw3[045im2,[4oc'wdfgvdhfghbdfghdfgjbfghjbfgjhfghx134rxqwetaertg" \
        "sdfcgsdfhgvdfghbfghbfgjbfgh1[-,c4rxj.wk;hfgszlcgjx3gfhjnhn4-rx134xqwetaertg" \
        "asdcfsaert45vt[045im2,[4oc'sacfasdfae5bu6rb678u5687mcsdfacssacfasdfsafsdfcg" \
        "ervtbe56un6i9ryvcae5tv6vb5n7m9i,098yob56ubr678mbfvtbyninbxhveujtybsrv56vye5"

    // Following is required so that we're not limited by per-character buffering
    std::ios_base::sync_with_stdio(false);

    if (a_testName == "std::printf") {
        char buff[1024] = {};

        for (std::size_t i = 0; i < loops; ++ i) {
            std::snprintf(buff, 1023, "%0.10f" str1 "%04d" str1 "%+g" str1 "%s" str1 "%p" str1 "%c" str1 "%%\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }

        std::cout << buff << std::endl;
    }
    else if (a_testName == "std::iostreams") {
        std::string sRv;

        for (std::size_t i = 0; i < loops; ++ i) {
            std::stringstream ss;
            ss
                << std::setprecision(10) << std::fixed << 1.234
                << std::resetiosflags(std::ios::floatfield) << str1
                << std::setw(4) << std::setfill('0') << 42 << std::setfill(' ') << str1
                << std::setiosflags(std::ios::showpos) << 3.13 << std::resetiosflags(std::ios::showpos) << str1
                << "string" << str1
                << (void *)1000 << str1
                << 'X' << str1 "%\n";
            sRv = ss.str();
        }

        std::cout << sRv << std::endl;
    }
    else if (a_testName == "tinyformat") {
        std::string sRv;

        for (std::size_t i = 0; i < loops; ++ i) {
            sRv = tfm::format("%0.10f" str1 "%04d" str1 "%+g" str1 "%s" str1 "%p" str1 "%c" str1 "%%\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }

        std::cout << sRv << std::endl;
    }
    else if (a_testName == "boost::format") {
        std::string sRv;

        for (std::size_t i = 0; i < loops; ++ i) {
            sRv = (boost::format("%0.10f" str1 "%04d" str1 "%+g" str1 "%s" str1 "%p" str1 "%c" str1 "%%\n")
                % 1.234 % 42 % 3.13 % "string" % (void *)1000 % (int)'X').str();
        }

        std::cout << sRv << std::endl;
    }
    else if (a_testName == "xlib::core::String::format") {
        std::string sRv;

        for (std::size_t i = 0; i < loops; ++ i) {
            sRv = xlib::core::String::format("%0.10f" str1 "%04d" str1 "%+g" str1 "%s" str1 "%p" str1 "%c" str1 "%%\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }

        std::cout << sRv << std::endl;
    }
    else if (a_testName == "xlib::Format") {
        std::string sRv;

        for (std::size_t i = 0; i < loops; ++ i) {
            sRv = xlib::core::Format("{}" str1 "{}" str1 "{}" str1 "{}" str1 "{}" str1 "{}" str1 "{}\n",
                1.234, 42, 3.13, "string", (void *)1000, (int)'X');
        }

        std::cout << sRv << std::endl;
    }
    else {
        std::cout << "Speed test for a_testName version?????" << std::endl;
    }
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    if (argc >= 2) {
        ::speedTest(argv[1]);
    }

    return EXIT_SUCCESS;
}
//-------------------------------------------------------------------------------------------------
