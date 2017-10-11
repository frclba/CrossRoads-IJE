/**
  \file animation.cpp
  Animation class implementatioin
*/

#include"components/animation.hpp"

using namespace engine;

Animation::~Animation() {

    // Default method.

}

/**
    This method initiates the Animation in the game
    \return false if path to file is blank or main_texture is NULL
    \return true if the image was split and the sprites arranged in the correct position
*/
bool Animation::init() {

    Log::instance.info( "Iniciando componente de animacao" );

    if( main_path == PATH_ERROR ) {
        Log::instance.error( "Caminho inválido!" );

        return false;
    }
    else{

        // Default else.

    }

    SDL_Surface *image = IMG_Load( main_path.c_str() );

    if( image == NULL ) {

        // SDL_IMG_ERROR("Could not load image from path !" << main_path);

        // Default if.

        return false;
    }
    else{

        // Default else.

    }

    main_texture = SDL_CreateTextureFromSurface(Game::instance.main_canvas,
                                                image);

    if( main_texture == NULL ) {

        // SDL_ERROR("Could not create texture from image");

        return false;
    }
    else{

        // Default else.

    }

    //Pegando os sizes padrões da imagem, por isso precisa ser desenhada no tamanho desejado

    _main_game_object -> set_size( m_width_division, m_height_division );

    SDL_FreeSurface( image );

    //divide imagem

    //ler matriz de imagems em um arquivo

    /** 
        Count to render images sizes.
    */
    int count = 0;

    for( int h = 0; h < image -> h && count < m_num_image; h += m_height_division ) {
        for( int w = 0; w < image -> w && count < m_num_image; w += m_width_division ) {
            SDL_Rect *rect = new SDL_Rect();
            rect -> x = w;
            rect -> y = h;
            rect -> w = m_width_division;
            rect -> h = m_height_division;
            image_vector.push_back( rect );
            count++;
        }
    }

    main_animation[BEGIN] = 0;
    main_animation[END] = image_vector.size() - 1;

    return true;

}

/**
    Set initial sprite and end sprit for display certain image movement
    \param[in] animation_name existing identifier in animation_map
    \param[in] begin should less image_vector size
    \param[in] end should be less image_vector size and bigger or equal to begin param
*/
void Animation::setAnimation( std::string animation_name, int begin, int end ) {

    (animation_map[animation_name])[BEGIN] = begin;
    (animation_map[animation_name])[END] = end;

}

/**
    Starts running the animation
    \param[in] animation_name existing identifier in animation_map
    \return true if started execution
*/
bool Animation::useAnimation( std::string animation_name ) {

    main_animation[BEGIN] = (animation_map[animation_name])[BEGIN];
    main_animation[END] = (animation_map[animation_name])[END];

    if( main_frame < main_animation[BEGIN] || main_frame > main_animation[END] ) {
        main_frame = main_animation[BEGIN];
    }
    else{

        // Default else.

    }

    return true;

}

/**
    \param[in] to_set_delay time in ms
    \result update delay value in animation
*/
void Animation::setDelay( int to_set_delay ) {

    this -> delay = to_set_delay;

}

/**
    Define side to animation moviment
    \param[in] is_flip represent moviment side
    \parblock
      true value refers to RIGHT
      false value refers to LEFT
    \endparblock
*/
void Animation::flipping( bool is_flip ) {

    if( is_flip ) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else {
        flip = SDL_FLIP_NONE;
    }

}

/**
    Check if animation is on the last frame
    \return true if is the end of the animation
    \return false if still not the last frame
*/
bool Animation::has_finished() {

    if( main_frame == main_animation[END] ) {
        return true;
    }
    else{

        // Default else.

    }

    return false;

}

/**
    Sets the GameObject size measures with the values set for the animation
*/
void Animation::setup() {

    _main_game_object -> set_size( m_width_division, m_height_division );

}

/**
    Positions the element on the screen
*/
void Animation::draw() {

    /**
        Render 2D image.
    */
    SDL_Rect *render_quad = new SDL_Rect();

    render_quad -> x = _main_game_object -> main_positionX;
    render_quad -> y = _main_game_object -> main_positionY;
    render_quad -> w = image_vector[main_frame] -> w;
    render_quad -> h = image_vector[main_frame]-> h;

    if( ( int ) ( Game::instance.timer -> getTicks() - time_step ) >= delay ) {
        main_frame++;
        time_step = Game::instance.timer -> getTicks();
    }
    else{

        // Default else.

    }

    if( main_frame > main_animation[END] ) {
            main_frame = main_animation[BEGIN];
    }
    else{

        // Default else.
        
    }

    SDL_RenderCopyEx(
        Game::instance.main_canvas,
        main_texture,
        image_vector[main_frame],
        render_quad,
        0,
        NULL,
        flip
    );

}