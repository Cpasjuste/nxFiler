//
// Created by cpasjuste on 12/04/18.
//

#include "filer.h"

using namespace c2d;

extern Io *io;

Filer::Filer(const std::string &path, c2d::Io *io,
             const Font &font, int fontSize, const FloatRect &rect,
             const std::vector<Io::File *> &fileList) : ListBox(font, fontSize, rect, fileList) {

    this->io = io;
    this->path = path;

    std::vector<std::string> f = io->getDirList(this->path.c_str());
    for (size_t i = 0; i < f.size(); i++) {

        Io::File *file = new Io::File();
        //strncpy(file->path, )
        //file->path = this->path + f[i];
        files.push_back(file);
    }
}

Filer::~Filer() {


}
