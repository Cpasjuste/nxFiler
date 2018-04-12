//
// Created by cpasjuste on 12/04/18.
//

#ifndef NXFILER_FILER_H
#define NXFILER_FILER_H

#include <c2d.h>

class Filer : public c2d::ListBox {

public:

    Filer(const std::string &path, c2d::Io *io,
          const c2d::Font &font, int fontSize,
          const c2d::FloatRect &rect, const std::vector<c2d::Io::File *> &fileList);

    ~Filer();

private:

    std::string path;
    std::vector<c2d::Io::File *> files;
    c2d::Io *io;
};

#endif //NXFILER_FILER_H
