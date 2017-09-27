/**
    \file keyboard.cpp
    This file use Keyboard functions
*/
#include "Keyboard.hpp"

using namespace engine;

//const Uint8 *(Keyboard::Keyboard_State) = SDL_GetKeyboardState(nullptr);

Keyboard::Keyboard() {

    create_keyboard_mapping();

}

Keyboard::~Keyboard() {

}

/**
    Set keys
    \param evt
    \parblock
        This method evaluate what button was pressed with the variable evt
        and then take decisions based on evt
    \endparblock
    \return anything because the method is void
*/
void Keyboard::setKeys( SDL_Event* evt ) {

    if( evt -> type == SDL_KEYDOWN ) {
        keycode_down.push_back( evt -> key.keysym.sym );
    }

    else if( evt -> type == SDL_KEYUP ) {
        keycode_up.push_back( evt -> key.keysym.sym );
    }

    else if( evt -> type == SDL_JOYBUTTONDOWN ) {
        if( ( ( int ) evt -> jbutton.button ) == 1 ) {
            keycode_down.push_back( SDLK_SPACE );
        }

        if( ( ( int ) evt -> jbutton.button ) == 2 ) {
            keycode_down.push_back( SDLK_w );
        }
        if( ( ( int ) evt -> jbutton.button ) == 0 ) {
            keycode_down.push_back( SDLK_f );
        }
        if( ( ( int ) evt -> jbutton.button ) == 9 ) {
            keycode_down.push_back( SDLK_RETURN );
        }
        //std::cout<<((int)evt->jbutton.button)<<std::endl;
    }

    else if( evt -> type == SDL_JOYBUTTONUP ) {
        if( ( ( int ) evt -> jbutton.button ) == 1 ) {
            keycode_up.push_back( SDLK_SPACE );
        }
        if( ( ( int ) evt -> jbutton.button ) == 2 ) {
            keycode_up.push_back( SDLK_w );
        }
        if( ( ( int ) evt -> jbutton.button ) == 0 ) {
            keycode_up.push_back( SDLK_f );
        }
        if( ( ( int ) evt -> jbutton.button ) == 9 ) {
            keycode_up.push_back( SDLK_RETURN );
        }
    }

    else if( evt -> type == SDL_JOYAXISMOTION ) {
        if( evt -> jaxis.axis == 0 ) {
            if( evt -> jaxis.value > 8000 ) {
                keycode_down.push_back( SDLK_d );
            }
            else {
                keycode_up.push_back( SDLK_d );
            }
            if( evt -> jaxis.value < -8000 ) {
                keycode_down.push_back( SDLK_a );
            }
            else {
                keycode_up.push_back( SDLK_a );
            }
        }

        if( evt -> jaxis.axis == 1 ) {
            if( evt -> jaxis.value > 8000 ) {
                keycode_down.push_back( SDLK_s );
            }
            else {
                keycode_up.push_back( SDLK_s );
            }
            if( evt -> jaxis.value < -8000 ) {
                keycode_down.push_back( SDLK_w );
            }
            else {
                keycode_up.push_back( SDLK_w );
            }
        }
        //std::cout<<evt->jaxis.value<<std::endl;
    }

}

/**
    Verify key up
    \param key
    \parblock
        This method verify if key pressed is up
    \endparblock
    \return returns bool to key up or not
*/
bool Keyboard::isKeyDown( std::string key ) {

    for( auto m_key : keycode_down ) {
        if( m_key == m_buttons[key] ) {
            return true;
        }
    }

    return false;

}

/**
    Verify key up
    \param key
    \parblock
        This method verify if key pressed is up
    \endparblock
    \return returns bool to key up or not
*/
bool Keyboard::isKeyUp( std::string key ) {
    for( auto m_key : keycode_up ) {
        if( m_key == m_buttons[key] ) {
            return true;
        }
    }

    return false;

}

/**
    This method clear key down and key up logic after pressed by the player
*/
void Keyboard::clearKeyboard() {

   keycode_up.clear();
   keycode_down.clear();

}

/**
   This method map all enable and not enable buttons that can be used in game 
*/
void Keyboard::create_keyboard_mapping() {

    m_buttons["unknown"] = SDLK_UNKNOWN;
    m_buttons["enter"] = SDLK_RETURN;
    m_buttons["esc"] = SDLK_ESCAPE;
    m_buttons["backspace"] = SDLK_BACKSPACE;
    m_buttons["tab"] = SDLK_TAB;
    m_buttons["space"] = SDLK_SPACE;
    m_buttons["!"] = SDLK_EXCLAIM;
    m_buttons["\""] = SDLK_QUOTEDBL;
    m_buttons["#"] = SDLK_HASH;
    m_buttons["%"] = SDLK_PERCENT;
    m_buttons["$"] = SDLK_DOLLAR;
    m_buttons["&"] = SDLK_AMPERSAND;
    m_buttons["'"] = SDLK_QUOTE;
    m_buttons["("] = SDLK_LEFTPAREN;
    m_buttons[")"] = SDLK_RIGHTPAREN;
    m_buttons["*"] = SDLK_ASTERISK;
    m_buttons["+"] = SDLK_PLUS;
    m_buttons[","] = SDLK_COMMA;
    m_buttons["-"] = SDLK_MINUS;
    m_buttons["."] = SDLK_PERIOD;
    m_buttons["/"] = SDLK_SLASH;
    m_buttons["0"] = SDLK_0;
    m_buttons["1"] = SDLK_1;
    m_buttons["2"] = SDLK_2;
    m_buttons["3"] = SDLK_3;
    m_buttons["4"] = SDLK_4;
    m_buttons["5"] = SDLK_5;
    m_buttons["6"] = SDLK_6;
    m_buttons["7"] = SDLK_7;
    m_buttons["8"] = SDLK_8;
    m_buttons["9"] = SDLK_9;
    m_buttons[":"] = SDLK_COLON;
    m_buttons[";"] = SDLK_SEMICOLON;
    m_buttons["<"] = SDLK_LESS;
    m_buttons["="] = SDLK_EQUALS;
    m_buttons[">"] = SDLK_GREATER;
    m_buttons["?"] = SDLK_QUESTION;
    m_buttons["@"] = SDLK_AT;

    m_buttons["["] = SDLK_LEFTBRACKET;
    m_buttons["\\"] = SDLK_BACKSLASH;
    m_buttons["]"] = SDLK_RIGHTBRACKET;
    m_buttons["^"] = SDLK_CARET;
    m_buttons["_"] = SDLK_UNDERSCORE;
    m_buttons["`"] = SDLK_BACKQUOTE;
    m_buttons["a"] = SDLK_a;
    m_buttons["b"] = SDLK_b;
    m_buttons["c"] = SDLK_c;
    m_buttons["d"] = SDLK_d;
    m_buttons["e"] = SDLK_e;
    m_buttons["f"] = SDLK_f;
    m_buttons["g"] = SDLK_g;
    m_buttons["h"] = SDLK_h;
    m_buttons["i"] = SDLK_i;
    m_buttons["j"] = SDLK_j;
    m_buttons["k"] = SDLK_k;
    m_buttons["l"] = SDLK_l;
    m_buttons["m"] = SDLK_m;
    m_buttons["n"] = SDLK_n;
    m_buttons["o"] = SDLK_o;
    m_buttons["p"] = SDLK_p;
    m_buttons["q"] = SDLK_q;
    m_buttons["r"] = SDLK_r;
    m_buttons["s"] = SDLK_s;
    m_buttons["t"] = SDLK_t;
    m_buttons["u"] = SDLK_u;
    m_buttons["v"] = SDLK_v;
    m_buttons["w"] = SDLK_w;
    m_buttons["x"] = SDLK_x;
    m_buttons["y"] = SDLK_y;
    m_buttons["z"] = SDLK_z;

    m_buttons["capslock"] = SDLK_CAPSLOCK;

    m_buttons["f1"] = SDLK_F1;
    m_buttons["f2"] = SDLK_F2;
    m_buttons["f3"] = SDLK_F3;
    m_buttons["f4"] = SDLK_F4;
    m_buttons["f5"] = SDLK_F5;
    m_buttons["f6"] = SDLK_F6;
    m_buttons["f7"] = SDLK_F7;
    m_buttons["f8"] = SDLK_F8;
    m_buttons["f9"] = SDLK_F9;
    m_buttons["f10"] = SDLK_F10;
    m_buttons["f11"] = SDLK_F11;
    m_buttons["f12"] = SDLK_F12;

    m_buttons["printscreen"] = SDLK_PRINTSCREEN;
    m_buttons["scrolllock"] = SDLK_SCROLLLOCK;
    m_buttons["pause"] = SDLK_PAUSE;
    m_buttons["insert"] = SDLK_INSERT;
    m_buttons["home"] = SDLK_HOME;
    m_buttons["pageup"] = SDLK_PAGEUP;
    m_buttons["delete"] = SDLK_DELETE;
    m_buttons["end"] = SDLK_END;
    m_buttons["pagedown"] = SDLK_PAGEDOWN;
    m_buttons["right"] = SDLK_RIGHT;
    m_buttons["left"] = SDLK_LEFT;
    m_buttons["down"] = SDLK_DOWN;
    m_buttons["up"] = SDLK_UP;

    m_buttons["numlock"] = SDLK_NUMLOCKCLEAR;
    m_buttons["key pad /"] = SDLK_KP_DIVIDE;
    m_buttons["key pad *"] = SDLK_KP_MULTIPLY;
    m_buttons["key pad -"] = SDLK_KP_MINUS;
    m_buttons["key pad +"] = SDLK_KP_PLUS;
    m_buttons["key pad enter"] = SDLK_KP_ENTER;
    m_buttons["key pad 1"] = SDLK_KP_1;
    m_buttons["key pad 2"] = SDLK_KP_2;
    m_buttons["key pad 3"] = SDLK_KP_3;
    m_buttons["key pad 4"] = SDLK_KP_4;
    m_buttons["key pad 5"] = SDLK_KP_5;
    m_buttons["key pad 6"] = SDLK_KP_6;
    m_buttons["key pad 7"] = SDLK_KP_7;
    m_buttons["key pad 8"] = SDLK_KP_8;
    m_buttons["key pad 9"] = SDLK_KP_9;
    m_buttons["key pad 0"] = SDLK_KP_0;
    m_buttons["key pad ."] = SDLK_KP_PERIOD;

    m_buttons["application"] = SDLK_APPLICATION;
    m_buttons["power"] = SDLK_POWER;
    m_buttons["key pad ="] = SDLK_KP_EQUALS;
    m_buttons["f13"] = SDLK_F13;
    m_buttons["f14"] = SDLK_F14;
    m_buttons["f15"] = SDLK_F15;
    m_buttons["f16"] = SDLK_F16;
    m_buttons["f17"] = SDLK_F17;
    m_buttons["f18"] = SDLK_F18;
    m_buttons["f19"] = SDLK_F19;
    m_buttons["f20"] = SDLK_F20;
    m_buttons["f21"] = SDLK_F21;
    m_buttons["f22"] = SDLK_F22;
    m_buttons["f23"] = SDLK_F23;
    m_buttons["f24"] = SDLK_F24;
    m_buttons["execute"] = SDLK_EXECUTE;
    m_buttons["help"] = SDLK_HELP;
    m_buttons["menu"] = SDLK_MENU;
    m_buttons["select"] = SDLK_SELECT;
    m_buttons["stop"] = SDLK_STOP;
    m_buttons["again"] = SDLK_AGAIN;
    m_buttons["undo"] = SDLK_UNDO;
    m_buttons["cut"] = SDLK_CUT;
    m_buttons["copy"] = SDLK_COPY;
    m_buttons["paste"] = SDLK_PASTE;
    m_buttons["find"] = SDLK_FIND;
    m_buttons["mute"] = SDLK_MUTE;
    m_buttons["volumeuP"] = SDLK_VOLUMEUP;
    m_buttons["volumedown"] = SDLK_VOLUMEDOWN;
    m_buttons["key pad ,"] = SDLK_KP_COMMA;
    m_buttons["key pad equalsas400"] = SDLK_KP_EQUALSAS400;

    m_buttons["alterase"] = SDLK_ALTERASE;
    m_buttons["sysreq"] = SDLK_SYSREQ;
    m_buttons["cancel"] = SDLK_CANCEL;
    m_buttons["clear"] = SDLK_CLEAR;
    m_buttons["prior"] = SDLK_PRIOR;
    m_buttons["return2"] = SDLK_RETURN2;
    m_buttons["separator"] = SDLK_SEPARATOR;
    m_buttons["out"] = SDLK_OUT;
    m_buttons["oper"] = SDLK_OPER;
    m_buttons["clearagain"] = SDLK_CLEARAGAIN;
    m_buttons["crsel"] = SDLK_CRSEL;
    m_buttons["exsel"] = SDLK_EXSEL;

    m_buttons["key pad 00"] = SDLK_KP_00;
    m_buttons["key pad 000"] = SDLK_KP_000;
    m_buttons["thousandsseparator"] = SDLK_THOUSANDSSEPARATOR;
    m_buttons["decimalseparator"] = SDLK_DECIMALSEPARATOR;
    m_buttons["currencyunit"] = SDLK_CURRENCYUNIT;
    m_buttons["currencysubunit"] = SDLK_CURRENCYSUBUNIT;
    m_buttons["key pad ("] = SDLK_KP_LEFTPAREN;
    m_buttons["key pad )"] = SDLK_KP_RIGHTPAREN;
    m_buttons["key pad {"] = SDLK_KP_LEFTBRACE;
    m_buttons["key pad }"] = SDLK_KP_RIGHTBRACE;
    m_buttons["key pad tab"] = SDLK_KP_TAB;
    m_buttons["key pad backspace"] = SDLK_KP_BACKSPACE;
    m_buttons["key pad a"] = SDLK_KP_A;
    m_buttons["key pad b"] = SDLK_KP_B;
    m_buttons["key pad c"] = SDLK_KP_C;
    m_buttons["key pad d"] = SDLK_KP_D;
    m_buttons["key pad e"] = SDLK_KP_E;
    m_buttons["key pad f"] = SDLK_KP_F;
    m_buttons["key pad xor"] = SDLK_KP_XOR;
    m_buttons["key pad power"] = SDLK_KP_POWER;
    m_buttons["key pad %"] = SDLK_KP_PERCENT;
    m_buttons["key pad <"] = SDLK_KP_LESS;
    m_buttons["key pad >"] = SDLK_KP_GREATER;
    m_buttons["key pad &"] = SDLK_KP_AMPERSAND;
    m_buttons["key pad &&"] = SDLK_KP_DBLAMPERSAND;
    m_buttons["key pad |"] = SDLK_KP_VERTICALBAR;
    m_buttons["key pad ||"] = SDLK_KP_DBLVERTICALBAR;
    m_buttons["key pad :"] = SDLK_KP_COLON;
    m_buttons["key pad #"] = SDLK_KP_HASH;
    m_buttons["key pad space"] = SDLK_KP_SPACE;
    m_buttons["key pad @"] = SDLK_KP_AT;
    m_buttons["key pad !"] = SDLK_KP_EXCLAM;
    m_buttons["key pad memstore"] = SDLK_KP_MEMSTORE;
    m_buttons["key pad memrecall"] = SDLK_KP_MEMRECALL;
    m_buttons["key pad memclear"] = SDLK_KP_MEMCLEAR;
    m_buttons["key pad memadd"] = SDLK_KP_MEMADD;
    m_buttons["key pad memsubtract"] = SDLK_KP_MEMSUBTRACT;
    m_buttons["key pad memmultiply"] = SDLK_KP_MEMMULTIPLY;
    m_buttons["key pad memdivide"] = SDLK_KP_MEMDIVIDE;
    m_buttons["key pad plusminus"] = SDLK_KP_PLUSMINUS;
    m_buttons["key pad clear"] = SDLK_KP_CLEAR;
    m_buttons["key pad clearentry"] = SDLK_KP_CLEARENTRY;
    m_buttons["key pad binary"] = SDLK_KP_BINARY;
    m_buttons["key pad octal"] = SDLK_KP_OCTAL;
    m_buttons["key pad decimal"] = SDLK_KP_DECIMAL;
    m_buttons["key pad hexadecimal"] = SDLK_KP_HEXADECIMAL;

    m_buttons["left ctrl"] = SDLK_LCTRL;
    m_buttons["left shift"] = SDLK_LSHIFT;
    m_buttons["left alt"] = SDLK_LALT;
    m_buttons["left gui"] = SDLK_LGUI;
    m_buttons["right ctrl"] = SDLK_RCTRL;
    m_buttons["right shift"] = SDLK_RSHIFT;
    m_buttons["right alt"] = SDLK_RALT;
    m_buttons["right gui"] = SDLK_RGUI;

    m_buttons["mode"] = SDLK_MODE;

    m_buttons["audio next"] = SDLK_AUDIONEXT;
    m_buttons["audio prev"] = SDLK_AUDIOPREV;
    m_buttons["audio stop"] = SDLK_AUDIOSTOP;
    m_buttons["audio play"] = SDLK_AUDIOPLAY;
    m_buttons["audio mute"] = SDLK_AUDIOMUTE;
    m_buttons["media select"] = SDLK_MEDIASELECT;
    m_buttons["www"] = SDLK_WWW;
    m_buttons["mail"] = SDLK_MAIL;
    m_buttons["calculator"] = SDLK_CALCULATOR;
    m_buttons["computer"] = SDLK_COMPUTER;
    m_buttons["ac_search"] = SDLK_AC_SEARCH;
    m_buttons["ac_home"] = SDLK_AC_HOME;
    m_buttons["ac_back"] = SDLK_AC_BACK;
    m_buttons["ac_forward"] = SDLK_AC_FORWARD;
    m_buttons["ac_stop"] = SDLK_AC_STOP;
    m_buttons["ac_refresh"] = SDLK_AC_REFRESH;
    m_buttons["ac_bookmarks"] = SDLK_AC_BOOKMARKS;

    m_buttons["brightness down"] = SDLK_BRIGHTNESSDOWN;
    m_buttons["brightness up"] = SDLK_BRIGHTNESSUP;
    m_buttons["displayswitch"] = SDLK_DISPLAYSWITCH;
    m_buttons["kbdillumtoggle"] = SDLK_KBDILLUMTOGGLE;
    m_buttons["kbdillumdown"] = SDLK_KBDILLUMDOWN;
    m_buttons["kbdillumup"] = SDLK_KBDILLUMUP;
    m_buttons["eject"] = SDLK_EJECT;
    m_buttons["sleep"] = SDLK_SLEEP;

}