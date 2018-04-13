//
// Created by cpasjuste on 12/04/18.
//

#include "filer.h"

using namespace c2d;

static bool endWith(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

Filer::Filer(c2d::Io *io, const std::string &path,
             const c2d::Font &font, int fontSize, const c2d::FloatRect &rect)
        : ListBox(font, fontSize, rect, NULL) {

    this->io = io;
    this->path = path;

    getDir(path);
}

bool Filer::getDir(const std::string &path) {

    if (!io->exist(path) || io->getType(path) != C2D_IO_DIR) {
        return false;
    }

    printf("getDir(%s)\n", path.c_str());

    this->path = path;
    index = 0;
    _files = io->getDirList(path);
    setFiles(&_files);
    setSelection(0);

    return true;
}

std::string Filer::getPath() {
    return path;
}

void Filer::down() {
    index++;
    if (index >= (int) getFiles()->size()) {
        index = 0;
    }
    setSelection(index);
}

void Filer::up() {
    index--;
    if (index < 0)
        index = (int) (getFiles()->size() - 1);
    setSelection(index);
}

void Filer::left() {
    index -= getMaxLines();
    if (index < 0)
        index = 0;
    setSelection(index);
}

void Filer::right() {
    index += getMaxLines();
    if (index >= (int) getFiles()->size())
        index = (int) (getFiles()->size() - 1);
    setSelection(index);
}

void Filer::enter() {

    // TODO: manually handle ".."2

    if (path == "/") {
        getDir(path + getSelection()->name);
    } else {
        getDir(path + "/" + getSelection()->name);
    }
}

void Filer::exit() {

    if (path == "/" || path.find('/') == std::string::npos) {
        return;
    }

    while (path.back() != '/') {
        path.erase(path.size() - 1);
    }

    if (path.size() > 1 && endWith(path, "/")) {
        path.erase(path.size() - 1);
    }

    getDir(path);
}

Filer::~Filer() {

}
