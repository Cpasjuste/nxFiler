//
// Created by cpasjuste on 08/12/16.
//

#include "c2d.h"
#include "main.h"
#include "filer.h"

#include "../libcross2d/res/default.h"

using namespace c2d;

Renderer *renderer;
Font *font;
Io *io;
Input *input;
Clock *timer;
Filer *filer[2];

int current_filer = FILER_LEFT;

int main() {

    // create main renderer
    renderer = new C2DRenderer(Vector2f(SCR_W, SCR_H));
    renderer->setFillColor(Color::Gray);

    // create a font
    font = new Font();
    font->loadFromMemory(pfba_font, pfba_font_length);

    // create io
    io = new C2DIo();

    // create input
    input = new C2DInput();
    input->setJoystickMapping(0, KEYS, 0);
    input->setKeyboardMapping(KEYBOARD_KEYS);

    // create a timer
    timer = new C2DClock();

    // create a rect
    Rectangle *rect = new C2DRectangle(Vector2f(renderer->getSize().x - 4, renderer->getSize().y - 4));
    rect->setPosition(2, 2);
    rect->setFillColor(Color::Transparent);
    rect->setOutlineColor(Color::Orange);
    rect->setOutlineThickness(2);

    filer[FILER_LEFT] = new Filer(io, "/", *font, FONT_SIZE,
                                  FloatRect(rect->getPosition().x + 16, rect->getPosition().y + 16,
                                            (rect->getSize().x / 2) - 16, rect->getSize().y - 32));
    rect->add(filer[FILER_LEFT]);

    filer[FILER_RIGHT] = new Filer(io, "/", *font, FONT_SIZE,
                                   FloatRect(rect->getPosition().x + 16 + (rect->getSize().x / 2),
                                             rect->getPosition().y + 16,
                                             (rect->getSize().x / 2) - 32, rect->getSize().y - 32));
    rect->add(filer[FILER_RIGHT]);

    // add all this crap to the renderer
    renderer->add(rect);
    renderer->flip();

    while (true) {

        // handle input
        unsigned int key = input->update()[0].state;
        if (key > 0) {

            if (key & EV_QUIT) { // SDL2 quit event
                break;
            }

            if (key & Input::Key::KEY_FIRE2) {
                // TODO: ask confirmation to exit
                //break;
            }

            if (key & Input::Key::KEY_FIRE5) {
                current_filer = !current_filer;
            } else if (key & Input::Key::KEY_FIRE6) {
                current_filer = !current_filer;
            }

            if (key & Input::Key::KEY_UP) {
                filer[current_filer]->up();
            } else if (key & Input::Key::KEY_DOWN) {
                filer[current_filer]->down();
            } else if (key & Input::Key::KEY_RIGHT) {
                filer[current_filer]->right();
            } else if (key & Input::Key::KEY_LEFT) {
                filer[current_filer]->left();
            } else if (key & Input::Key::KEY_FIRE1) {
                filer[current_filer]->enter();
            } else if (key & Input::Key::KEY_FIRE2) {
                filer[current_filer]->exit();
            }

            renderer->flip();

            if (timer->getElapsedTime().asSeconds() > 10) {
                renderer->delay(INPUT_DELAY / 8);
            } else if (timer->getElapsedTime().asSeconds() > 6) {
                renderer->delay(INPUT_DELAY / 5);
            } else if (timer->getElapsedTime().asSeconds() > 2) {
                renderer->delay(INPUT_DELAY / 2);
            } else {
                renderer->delay(INPUT_DELAY);
            }
        } else {
            timer->restart();
        }
    }

    delete (timer);
    delete (input);
    delete (io);
    delete (font);
    // will delete widgets recursively
    delete (renderer);

    return 0;
}
