// Read the input file.
// Augmentation the input with desired markup.
// Render markdown.

#include <gsl/gsl_util>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <cmark.h>

std::string slurp(std::istream& in) {
    std::ostringstream s;
    s << in.rdbuf();
    return s.str();
}

std::string to_html(std::string const& md) {
    auto const p = cmark_markdown_to_html(md.c_str(), md.size(), 0);
    auto const f = gsl::finally([p] { std::free(p); });
    return p;
}

void convert(std::istream& in, std::ostream& out) {
    out << to_html(slurp(in));
}

int main(int argc, char** argv) try {
    if (argc < 2) {
        convert(std::cin, std::cout);
    } else {
        while (*++argv) {
            std::string const fname = *argv;
            std::ifstream in(fname);
            if (!in) throw "can't read " + fname;
            std::ofstream out(fname + ".html");
            convert(in, out);
            if (!out) throw "can't write " + fname;
        }
    }
} catch (std::string const& what) {
    std::clog << "error: " << what << '\n';
    return 1;
}
