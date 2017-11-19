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
    \param event
    \parblock
        This method evaluate what button was pressed with the variable event
        and then take decisions based on event
    \endparblock
    \return anything because the method is void
*/
void Keyboard::setKeys( SDL_Event* event ) {

    assert(event != NULL);

    /**
        \note Check what key was pressed to take a decision based on the key
        pressed.
    */
    if( event -> type == SDL_KEYDOWN ) {
        keycodes_down.push_back( event -> key.keysym.sym );
    }
    else if( event -> type == SDL_KEYUP ) {
        keycodes_up.push_back( event -> key.keysym.sym );
    }
    else if( event -> type == SDL_JOYBUTTONDOWN ) {

        /**
            \note Check what joystick button was pressed to take a decision
            based on the joystick button pressed
        */
        if( ( ( int ) event -> jbutton.button ) == SPACE_JBUTTON ) {
             keycodes_down.push_back( SDLK_SPACE );
        }
        else if( ( ( int ) event -> jbutton.button ) == W_JBUTTON ) {
            keycodes_down.push_back( SDLK_w );
        }
        else if( ( ( int ) event -> jbutton.button ) == F_JBUTTON ) {
            keycodes_down.push_back( SDLK_f );
        }
        else if( ( ( int ) event -> jbutton.button ) == RETURN_JBUTTON ) {
            keycodes_down.push_back( SDLK_RETURN );
        }
        else {
            Log::instance.error("Failed to identify joystick down action");
        }

    }
    else if( event -> type == SDL_JOYBUTTONUP ) {

        /**
            \note Check what joystick button was pressed to take a decision
            based on the joystick button pressed
        */ 
        if( ( ( int ) event -> jbutton.button ) == SPACE_JBUTTON ) {
            keycodes_up.push_back( SDLK_SPACE );
        }
        else if( ( ( int ) event -> jbutton.button ) == W_JBUTTON ) {
            keycodes_up.push_back( SDLK_w );
        }
        else if( ( ( int ) event -> jbutton.button ) == F_JBUTTON ) {
            keycodes_up.push_back( SDLK_f );
        }
        else if( ( ( int ) event -> jbutton.button ) == RETURN_JBUTTON ) {
            keycodes_up.push_back( SDLK_RETURN );
        }
        else {
            Log::instance.error("Failed to identify joystick up action");
        }

    }
    else if( event -> type == SDL_JOYAXISMOTION ) {

        /**
            \note Check what joystick button was pressed to take a decision
            based on the joystick button pressed
        */ 
        if( event -> jaxis.axis == HORIZONTAL_JAXIS ) {

            /// \note Verify if direction of axis was to the right.
            if( event -> jaxis.value > POSITIVE_JAXIS ) {
                keycodes_down.push_back( SDLK_d );
            }
            else {
                keycodes_up.push_back( SDLK_d );
            }

            /// \note Verify if direction of axis was to the left.
            if( event -> jaxis.value < NEGATIVE_JAXIS ) {
                keycodes_down.push_back( SDLK_a );
            }
            else {
                keycodes_up.push_back( SDLK_a );
            }

        }
        else if( event -> jaxis.axis == VERTICAL_JAXIS ) {
            
            /// \note Verify if direction of axis was upward.
            if( event -> jaxis.value > POSITIVE_JAXIS ) {
                keycodes_down.push_back( SDLK_s );
            }
            else {
                keycodes_up.push_back( SDLK_s );
            }

            /// \note Verify if direction of axis was downward.
            if( event -> jaxis.value < NEGATIVE_JAXIS ) {
                keycodes_down.push_back( SDLK_w );
            }
            else {
                keycodes_up.push_back( SDLK_w );
            }

        }
        else {
            Log::instance.error("Failed to identify joystick axis action");
        }
    }
    else {
        Log::instance.error("Failed to identify control actions");
    }

}

/**
    Verify key down
    \param key
    \parblock
        This method verify if key pressed is down
    \endparblock
    \return returns bool to key down or not
*/
bool Keyboard::isKeyDown( std::string key ) {

    /// \note Check if key down was pressed.
    if(m_button_code.count(key) != 0) {
        std::list<Uint8>::iterator m_key;

        /// \note Iterate button down.
        for( m_key = keycodes_down.begin() ; m_key != keycodes_down.end() ; m_key++ ) {

            /// \note Check if button down was mapped.
            if( *m_key == m_button_code[key] ) {
                return true;
            }
            else {
                // Do nothing
            }

        }

        return false;

    }
    else {
        Log::instance.error("The '" + key + "' was not mapped");
        return false;
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
bool Keyboard::isKeyUp( std::string key ) {

    /// \note Check if key up was pressed.
    if(m_button_code.count(key) != 0) {

        std::list<Uint8>::iterator m_key;

        /// \note Iterate button up. 
        for( m_key = keycodes_up.begin() ; m_key != keycodes_up.end() ; m_key++ ) {
            
            /// \note Check if button up was mapped.
            if( *m_key == m_button_code[key] ) {
                return true;
            }
            else {
                // Do nothing
            }

        }

        return false;
    }
    else {
        Log::instance.error("The '" + key + "' was not mapped");
        return false;
    }
}

/**
    This method clear key down and key up logic after pressed by the player
*/
void Keyboard::clearKeyboard() {

   keycodes_up.clear();
   keycodes_down.clear();

}

/**
   This method map all enable and not enable buttons that can be used in game
*/
void Keyboard::create_keyboard_mapping() {

    m_button_code["unknown"] = SDLK_UNKNOWN;
    m_button_code["enter"] = SDLK_RETURN;
    m_button_code["esc"] = SDLK_ESCAPE;
    m_button_code["backspace"] = SDLK_BACKSPACE;
    m_button_code["tab"] = SDLK_TAB;
    m_button_code["space"] = SDLK_SPACE;
    m_button_code["!"] = SDLK_EXCLAIM;
    m_button_code["\""] = SDLK_QUOTEDBL;
    m_button_code["#"] = SDLK_HASH;
    m_button_code["%"] = SDLK_PERCENT;
    m_button_code["$"] = SDLK_DOLLAR;
    m_button_code["&"] = SDLK_AMPERSAND;
    m_button_code["'"] = SDLK_QUOTE;
    m_button_code["("] = SDLK_LEFTPAREN;
    m_button_code[")"] = SDLK_RIGHTPAREN;
    m_button_code["*"] = SDLK_ASTERISK;
    m_button_code["+"] = SDLK_PLUS;
    m_button_code[","] = SDLK_COMMA;
    m_button_code["-"] = SDLK_MINUS;
    m_button_code["."] = SDLK_PERIOD;
    m_button_code["/"] = SDLK_SLASH;
    m_button_code["0"] = SDLK_0;
    m_button_code["1"] = SDLK_1;
    m_button_code["2"] = SDLK_2;
    m_button_code["3"] = SDLK_3;
    m_button_code["4"] = SDLK_4;
    m_button_code["5"] = SDLK_5;
    m_button_code["6"] = SDLK_6;
    m_button_code["7"] = SDLK_7;
    m_button_code["8"] = SDLK_8;
    m_button_code["9"] = SDLK_9;
    m_button_code[":"] = SDLK_COLON;
    m_button_code[";"] = SDLK_SEMICOLON;
    m_button_code["<"] = SDLK_LESS;
    m_button_code["="] = SDLK_EQUALS;
    m_button_code[">"] = SDLK_GREATER;
    m_button_code["?"] = SDLK_QUESTION;
    m_button_code["@"] = SDLK_AT;

    m_button_code["["] = SDLK_LEFTBRACKET;
    m_button_code["\\"] = SDLK_BACKSLASH;
    m_button_code["]"] = SDLK_RIGHTBRACKET;
    m_button_code["^"] = SDLK_CARET;
    m_button_code["_"] = SDLK_UNDERSCORE;
    m_button_code["`"] = SDLK_BACKQUOTE;
    m_button_code["a"] = SDLK_a;
    m_button_code["b"] = SDLK_b;
    m_button_code["c"] = SDLK_c;
    m_button_code["d"] = SDLK_d;
    m_button_code["e"] = SDLK_e;
    m_button_code["f"] = SDLK_f;
    m_button_code["g"] = SDLK_g;
    m_button_code["h"] = SDLK_h;
    m_button_code["i"] = SDLK_i;
    m_button_code["j"] = SDLK_j;
    m_button_code["k"] = SDLK_k;
    m_button_code["l"] = SDLK_l;
    m_button_code["m"] = SDLK_m;
    m_button_code["n"] = SDLK_n;
    m_button_code["o"] = SDLK_o;
    m_button_code["p"] = SDLK_p;
    m_button_code["q"] = SDLK_q;
    m_button_code["r"] = SDLK_r;
    m_button_code["s"] = SDLK_s;
    m_button_code["t"] = SDLK_t;
    m_button_code["u"] = SDLK_u;
    m_button_code["v"] = SDLK_v;
    m_button_code["w"] = SDLK_w;
    m_button_code["x"] = SDLK_x;
    m_button_code["y"] = SDLK_y;
    m_button_code["z"] = SDLK_z;

    m_button_code["capslock"] = SDLK_CAPSLOCK;

    m_button_code["f1"] = SDLK_F1;
    m_button_code["f2"] = SDLK_F2;
    m_button_code["f3"] = SDLK_F3;
    m_button_code["f4"] = SDLK_F4;
    m_button_code["f5"] = SDLK_F5;
    m_button_code["f6"] = SDLK_F6;
    m_button_code["f7"] = SDLK_F7;
    m_button_code["f8"] = SDLK_F8;
    m_button_code["f9"] = SDLK_F9;
    m_button_code["f10"] = SDLK_F10;
    m_button_code["f11"] = SDLK_F11;
    m_button_code["f12"] = SDLK_F12;

    m_button_code["printscreen"] = SDLK_PRINTSCREEN;
    m_button_code["scrolllock"] = SDLK_SCROLLLOCK;
    m_button_code["pause"] = SDLK_PAUSE;
    m_button_code["insert"] = SDLK_INSERT;
    m_button_code["home"] = SDLK_HOME;
    m_button_code["pageup"] = SDLK_PAGEUP;
    m_button_code["delete"] = SDLK_DELETE;
    m_button_code["end"] = SDLK_END;
    m_button_code["pagedown"] = SDLK_PAGEDOWN;
    m_button_code["right"] = SDLK_RIGHT;
    m_button_code["left"] = SDLK_LEFT;
    m_button_code["down"] = SDLK_DOWN;
    m_button_code["up"] = SDLK_UP;

    m_button_code["numlock"] = SDLK_NUMLOCKCLEAR;
    m_button_code["key pad /"] = SDLK_KP_DIVIDE;
    m_button_code["key pad *"] = SDLK_KP_MULTIPLY;
    m_button_code["key pad -"] = SDLK_KP_MINUS;
    m_button_code["key pad +"] = SDLK_KP_PLUS;
    m_button_code["key pad enter"] = SDLK_KP_ENTER;
    m_button_code["key pad 1"] = SDLK_KP_1;
    m_button_code["key pad 2"] = SDLK_KP_2;
    m_button_code["key pad 3"] = SDLK_KP_3;
    m_button_code["key pad 4"] = SDLK_KP_4;
    m_button_code["key pad 5"] = SDLK_KP_5;
    m_button_code["key pad 6"] = SDLK_KP_6;
    m_button_code["key pad 7"] = SDLK_KP_7;
    m_button_code["key pad 8"] = SDLK_KP_8;
    m_button_code["key pad 9"] = SDLK_KP_9;
    m_button_code["key pad 0"] = SDLK_KP_0;
    m_button_code["key pad ."] = SDLK_KP_PERIOD;

    m_button_code["application"] = SDLK_APPLICATION;
    m_button_code["power"] = SDLK_POWER;
    m_button_code["key pad ="] = SDLK_KP_EQUALS;
    m_button_code["f13"] = SDLK_F13;
    m_button_code["f14"] = SDLK_F14;
    m_button_code["f15"] = SDLK_F15;
    m_button_code["f16"] = SDLK_F16;
    m_button_code["f17"] = SDLK_F17;
    m_button_code["f18"] = SDLK_F18;
    m_button_code["f19"] = SDLK_F19;
    m_button_code["f20"] = SDLK_F20;
    m_button_code["f21"] = SDLK_F21;
    m_button_code["f22"] = SDLK_F22;
    m_button_code["f23"] = SDLK_F23;
    m_button_code["f24"] = SDLK_F24;
    m_button_code["execute"] = SDLK_EXECUTE;
    m_button_code["help"] = SDLK_HELP;
    m_button_code["menu"] = SDLK_MENU;
    m_button_code["select"] = SDLK_SELECT;
    m_button_code["stop"] = SDLK_STOP;
    m_button_code["again"] = SDLK_AGAIN;
    m_button_code["undo"] = SDLK_UNDO;
    m_button_code["cut"] = SDLK_CUT;
    m_button_code["copy"] = SDLK_COPY;
    m_button_code["paste"] = SDLK_PASTE;
    m_button_code["find"] = SDLK_FIND;
    m_button_code["mute"] = SDLK_MUTE;
    m_button_code["volumeuP"] = SDLK_VOLUMEUP;
    m_button_code["volumedown"] = SDLK_VOLUMEDOWN;
    m_button_code["key pad ,"] = SDLK_KP_COMMA;
    m_button_code["key pad equalsas400"] = SDLK_KP_EQUALSAS400;

    m_button_code["alterase"] = SDLK_ALTERASE;
    m_button_code["sysreq"] = SDLK_SYSREQ;
    m_button_code["cancel"] = SDLK_CANCEL;
    m_button_code["clear"] = SDLK_CLEAR;
    m_button_code["prior"] = SDLK_PRIOR;
    m_button_code["return2"] = SDLK_RETURN2;
    m_button_code["separator"] = SDLK_SEPARATOR;
    m_button_code["out"] = SDLK_OUT;
    m_button_code["oper"] = SDLK_OPER;
    m_button_code["clearagain"] = SDLK_CLEARAGAIN;
    m_button_code["crsel"] = SDLK_CRSEL;
    m_button_code["exsel"] = SDLK_EXSEL;

    m_button_code["key pad 00"] = SDLK_KP_00;
    m_button_code["key pad 000"] = SDLK_KP_000;
    m_button_code["thousandsseparator"] = SDLK_THOUSANDSSEPARATOR;
    m_button_code["decimalseparator"] = SDLK_DECIMALSEPARATOR;
    m_button_code["currencyunit"] = SDLK_CURRENCYUNIT;
    m_button_code["currencysubunit"] = SDLK_CURRENCYSUBUNIT;
    m_button_code["key pad ("] = SDLK_KP_LEFTPAREN;
    m_button_code["key pad )"] = SDLK_KP_RIGHTPAREN;
    m_button_code["key pad {"] = SDLK_KP_LEFTBRACE;
    m_button_code["key pad }"] = SDLK_KP_RIGHTBRACE;
    m_button_code["key pad tab"] = SDLK_KP_TAB;
    m_button_code["key pad backspace"] = SDLK_KP_BACKSPACE;
    m_button_code["key pad a"] = SDLK_KP_A;
    m_button_code["key pad b"] = SDLK_KP_B;
    m_button_code["key pad c"] = SDLK_KP_C;
    m_button_code["key pad d"] = SDLK_KP_D;
    m_button_code["key pad e"] = SDLK_KP_E;
    m_button_code["key pad f"] = SDLK_KP_F;
    m_button_code["key pad xor"] = SDLK_KP_XOR;
    m_button_code["key pad power"] = SDLK_KP_POWER;
    m_button_code["key pad %"] = SDLK_KP_PERCENT;
    m_button_code["key pad <"] = SDLK_KP_LESS;
    m_button_code["key pad >"] = SDLK_KP_GREATER;
    m_button_code["key pad &"] = SDLK_KP_AMPERSAND;
    m_button_code["key pad &&"] = SDLK_KP_DBLAMPERSAND;
    m_button_code["key pad |"] = SDLK_KP_VERTICALBAR;
    m_button_code["key pad ||"] = SDLK_KP_DBLVERTICALBAR;
    m_button_code["key pad :"] = SDLK_KP_COLON;
    m_button_code["key pad #"] = SDLK_KP_HASH;
    m_button_code["key pad space"] = SDLK_KP_SPACE;
    m_button_code["key pad @"] = SDLK_KP_AT;
    m_button_code["key pad !"] = SDLK_KP_EXCLAM;
    m_button_code["key pad memstore"] = SDLK_KP_MEMSTORE;
    m_button_code["key pad memrecall"] = SDLK_KP_MEMRECALL;
    m_button_code["key pad memclear"] = SDLK_KP_MEMCLEAR;
    m_button_code["key pad memadd"] = SDLK_KP_MEMADD;
    m_button_code["key pad memsubtract"] = SDLK_KP_MEMSUBTRACT;
    m_button_code["key pad memmultiply"] = SDLK_KP_MEMMULTIPLY;
    m_button_code["key pad memdivide"] = SDLK_KP_MEMDIVIDE;
    m_button_code["key pad plusminus"] = SDLK_KP_PLUSMINUS;
    m_button_code["key pad clear"] = SDLK_KP_CLEAR;
    m_button_code["key pad clearentry"] = SDLK_KP_CLEARENTRY;
    m_button_code["key pad binary"] = SDLK_KP_BINARY;
    m_button_code["key pad octal"] = SDLK_KP_OCTAL;
    m_button_code["key pad decimal"] = SDLK_KP_DECIMAL;
    m_button_code["key pad hexadecimal"] = SDLK_KP_HEXADECIMAL;

    m_button_code["left ctrl"] = SDLK_LCTRL;
    m_button_code["left shift"] = SDLK_LSHIFT;
    m_button_code["left alt"] = SDLK_LALT;
    m_button_code["left gui"] = SDLK_LGUI;
    m_button_code["right ctrl"] = SDLK_RCTRL;
    m_button_code["right shift"] = SDLK_RSHIFT;
    m_button_code["right alt"] = SDLK_RALT;
    m_button_code["right gui"] = SDLK_RGUI;

    m_button_code["mode"] = SDLK_MODE;

    m_button_code["audio next"] = SDLK_AUDIONEXT;
    m_button_code["audio prev"] = SDLK_AUDIOPREV;
    m_button_code["audio stop"] = SDLK_AUDIOSTOP;
    m_button_code["audio play"] = SDLK_AUDIOPLAY;
    m_button_code["audio mute"] = SDLK_AUDIOMUTE;
    m_button_code["media select"] = SDLK_MEDIASELECT;
    m_button_code["www"] = SDLK_WWW;
    m_button_code["mail"] = SDLK_MAIL;
    m_button_code["calculator"] = SDLK_CALCULATOR;
    m_button_code["computer"] = SDLK_COMPUTER;
    m_button_code["ac_search"] = SDLK_AC_SEARCH;
    m_button_code["ac_home"] = SDLK_AC_HOME;
    m_button_code["ac_back"] = SDLK_AC_BACK;
    m_button_code["ac_forward"] = SDLK_AC_FORWARD;
    m_button_code["ac_stop"] = SDLK_AC_STOP;
    m_button_code["ac_refresh"] = SDLK_AC_REFRESH;
    m_button_code["ac_bookmarks"] = SDLK_AC_BOOKMARKS;

    m_button_code["brightness down"] = SDLK_BRIGHTNESSDOWN;
    m_button_code["brightness up"] = SDLK_BRIGHTNESSUP;
    m_button_code["displayswitch"] = SDLK_DISPLAYSWITCH;
    m_button_code["kbdillumtoggle"] = SDLK_KBDILLUMTOGGLE;
    m_button_code["kbdillumdown"] = SDLK_KBDILLUMDOWN;
    m_button_code["kbdillumup"] = SDLK_KBDILLUMUP;
    m_button_code["eject"] = SDLK_EJECT;
    m_button_code["sleep"] = SDLK_SLEEP;

}
