//
// Created by cpasjuste on 08/12/16.
//

#include "c2d.h"
#include "main.h"

#include "../libcross2d/res/default.h"

using namespace c2d;

Renderer *renderer;
Font *font;
Io *io;

int main() {

    // create main renderer
    renderer = new C2DRenderer(Vector2f(SCR_W, SCR_H));
    renderer->setFillColor(Color::GrayLight);

    // create a font
    font = new Font();
    font->loadFromMemory(pfba_font, pfba_font_length);

    // create io
    io = new C2DIo();

    // create input
    Input *input = new C2DInput(NULL);
    input->setJoystickMapping(0, KEYS, 0);

    // create a rect
    Rectangle *rect = new C2DRectangle(Vector2f(renderer->getSize().x - 4, renderer->getSize().y - 4));
    rect->setPosition(2, 2);
    rect->setFillColor(Color::Transparent);
    rect->setOutlineColor(Color::Orange);
    rect->setOutlineThickness(2);

    // add all this crap to the renderer
    renderer->add(rect);

    while (true) {

        // handle input
        unsigned int key = input->update()[0].state;
        if (key) {
            printf("input[0]: 0x%08X\n", key);
            //input->clear(0);
            if (key & Input::Key::KEY_FIRE2) {
                break;
            }
        }

        renderer->flip();
    }

    // will delete widgets recursively
    delete (io);
    delete (font);
    delete (renderer);

    return 0;
}
