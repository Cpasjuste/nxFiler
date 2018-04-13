//
// Created by cpasjuste on 12/04/18.
//

#ifndef NXFILER_FILER_H
#define NXFILER_FILER_H

#include <c2d.h>

class Filer : public c2d::ListBox {

public:

    Filer(c2d::Io *io, const std::string &path,
          const c2d::Font &font, int fontSize, const c2d::FloatRect &rect);

    ~Filer();

    bool getDir(const std::string &path);

    std::string getPath();

    void down();

    void up();

    void left();

    void right();

    void enter();

    void exit();

private:

    std::string path;
    std::vector<c2d::Io::File> _files;
    c2d::Io *io;
    int index = 0;
};

#endif //NXFILER_FILER_H
