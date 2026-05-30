#include "Application.h"

void Application::init_resources()
{
    chunk_view.loadFromFile("resources\\textures\\plate.png");
    sub_chunk_view.loadFromFile("resources\\textures\\plate.png");

	the_core.resource_manager.add_texture("resources\\textures\\plate.png", Textures::main_t);
    the_core.resource_manager.add_texture("resources\\textures\\plate.png", submain);

    the_core.resource_manager.add_texture("resources\\textures\\interface_background.png", 1);

    the_core.resource_manager.add_font("resources\\fonts\\MonaspaceNeon-Medium.otf", 0);
}

void Application::init_interface()
{
    interface_group.set_name("group");

    interface_body.setOutlineColor(sf::Color::Black);
    interface_body.setOutlineThickness(3);
    interface_body.setFillColor(sf::Color(255, 255, 255, 120));
    interface_body.setSize(sf::Vector2f(225, 120));
    interface_body.set_name("body");

    interface_group.add(&interface_body, sf::Vector2f(645 - 228, 645 - 322-60));
    
//-----------------------------------------------------------------
    A_l.set_name("A_l");
    A_l.text->setString("A");
    A_l.text->setFillColor(sf::Color::White);
    A_l.text->setCharacterSize(256);
    A_l.text->setScale(sf::Vector2f(0.2, 0.2));

    interface_group.add(A_l.text, sf::Vector2f(10, 0));

    B_l.set_name("B_l");
    B_l.text->setString("B");
    B_l.text->setFillColor(sf::Color::White);
    B_l.text->setCharacterSize(256);
    B_l.text->setScale(sf::Vector2f(0.2, 0.2));

    interface_group.add(B_l.text, sf::Vector2f(645 - 40, 0));

    D_l.set_name("D_l");
    D_l.text->setString("D");
    D_l.text->setFillColor(sf::Color::White);
    D_l.text->setCharacterSize(256);
    D_l.text->setScale(sf::Vector2f(0.2, 0.2));

    interface_group.add(D_l.text, sf::Vector2f(10, 645 - 60));

    C_l.set_name("C_l");
    C_l.text->setString("C");
    C_l.text->setFillColor(sf::Color::White);
    C_l.text->setCharacterSize(256);
    C_l.text->setScale(sf::Vector2f(0.2, 0.2));

    interface_group.add(C_l.text, sf::Vector2f(645 - 40, 645-60));
//-----------------------------------------------------------------
    sf::Vector2f in_anc = sf::Vector2f(645 - 228 + 45, 645 - 322 - 60 + 10);

    A.set_name("A");
    A.set_text("0");
    A.body.setSize(sf::Vector2f(80, 20));
    interface_group.add(&A.body, in_anc);

    B.set_name("B");
    B.set_text("0");
    B.body.setSize(sf::Vector2f(80, 20));
    interface_group.add(&B.body, sf::Vector2f(in_anc.x+90,in_anc.y));

    C.set_name("C");
    C.set_text("0");
    C.body.setSize(sf::Vector2f(80, 20));
    interface_group.add(&C.body, sf::Vector2f(in_anc.x + 90, in_anc.y + 30));

    D.set_name("D");
    D.set_text("0");
    D.body.setSize(sf::Vector2f(80, 20));
    interface_group.add(&D.body, sf::Vector2f(in_anc.x, in_anc.y + 30));

    R.set_name("R");
    R.set_text("0.5");
    R.body.setSize(sf::Vector2f(80, 20));
    interface_group.add(&R.body, sf::Vector2f(in_anc.x, in_anc.y + 60));
//-----------------------------------------------------------------
    AB.set_name("AB");
    AB.text->setString("AB");
    AB.text->setFillColor(sf::Color::Black);
    AB.text->setCharacterSize(256);
    AB.text->setScale(sf::Vector2f(0.08,0.08));

    interface_group.add(AB.text, sf::Vector2f(in_anc.x - 40, in_anc.y));

    DC.set_name("DC");
    DC.text->setString("DC");
    DC.text->setFillColor(sf::Color::Black);
    DC.text->setCharacterSize(256);
    DC.text->setScale(sf::Vector2f(0.08, 0.08));

    interface_group.add(DC.text, sf::Vector2f(in_anc.x - 40, in_anc.y+30));

    R_l.set_name("R_l");
    R_l.text->setString("R");
    R_l.text->setFillColor(sf::Color::Black);
    R_l.text->setCharacterSize(256);
    R_l.text->setScale(sf::Vector2f(0.08, 0.08));

    interface_group.add(R_l.text, sf::Vector2f(in_anc.x - 40, in_anc.y + 60));
//-----------------------------------------------------------------

    app_scene.add(&interface_group, 0);
    app_scene.add(&interface_body, 1);
    app_scene.add(&A_l, 1);
    app_scene.add(&B_l, 1);
    app_scene.add(&C_l, 1);
    app_scene.add(&D_l, 1);
    app_scene.add(&A, 2);
    app_scene.add(&B, 2);
    app_scene.add(&C, 2);
    app_scene.add(&D, 2);
    app_scene.add(&R, 2);
    app_scene.add(&AB, 2);
    app_scene.add(&DC, 2);
    app_scene.add(&R_l, 2);
}

void Application::save_chunk(const int& x, const int& y)
{
    std::string file_path = "saves\\" + std::to_string(x) + '-' + std::to_string(y) + ".txt";
    std::ofstream file(file_path);
    
    if (file.is_open())
    {
        for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            for (int j = 0; j < CHUNK_SIZE; ++j)
            {
                file << current_mesh[i][j] << ' ';
            }
        }
    }

    file.close();

}

bool Application::load_chunk(const int& x, const int& y)
{

    std::string file_path = "saves\\" + std::to_string(x) + '-' + std::to_string(y) + ".txt";

    std::ifstream file(file_path);

    bool res = false;

    if (file.is_open())
    {
        res = true;

        int x = 0;
        int y = 0;

        float value;

        int color_code;

        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i)
        {
            file >> value;

            color_code = 127 + value;
            
            if (color_code >= 127)
            {
                chunk_view.setPixel(sf::Vector2u(x, y), sf::Color(0, color_code, 0));
            }
            else
            {
                chunk_view.setPixel(sf::Vector2u(x, y), sf::Color(0, 0, color_code));
            }

            current_mesh[y][x] = value;
            ++x;
            if (x >= CHUNK_SIZE)
            {
                x = 0;
                ++y;
            }
        }

        the_core.resource_manager.get_texture(0).loadFromImage(chunk_view);
    }

    return res;
}

bool Application::get_value(float& value , const std::string& str)
{
    if (str.size() == 0) { value = 0; return true; }
    bool sign_flag = (str[0] == '-');
    bool dot_flag = false;
    for (int i = 0; i < str.size(); ++i)
    {
        if (sign_flag and str.size() == 1)
        {
            return false;
        }

        if (sign_flag and i == 0)
        {
            continue;
        }

        const char& sign = str[i];
        if (sign == '.')
        {
            if (dot_flag) { return false; }
            dot_flag = true;

            if (i == 0 or (i == 1 and sign_flag))
            {
                return false;
            }

            continue;
        }

        if (!(int(sign) >= 48 and int(sign) <= 57))
        {
            return false;
        }
    }
    value = std::stof(str);
    return true;

}

float Application::get_random_value(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(*this->gen);
}


void Application::generate_chunk(const float& A, const float& B, const float& C, const float& D)
{
    chunk_view.loadFromFile("resources\\textures\\plate.png");

    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            current_mesh[i][j] = 0;
        }
    }

    current_mesh[0][0] = A;
    current_mesh[0][CHUNK_SIZE - 1] = B;
    current_mesh[CHUNK_SIZE - 1][CHUNK_SIZE - 1] = C;
    current_mesh[CHUNK_SIZE - 1][0] = D;

    float value;

    float avg;
    float random;

    int step = CHUNK_SIZE - 1;
    float range = 100.0f;

    float topLeft, topRight, bottomRight, bottomLeft;

    int half;

    std::ifstream file;

    float sum = 0;
    int count = 0;

//------------------------------------------------------------------------------------------------------
    bool top_exist = false;
    std::vector<float> top_loaded_values;
    file.open("saves\\" + std::to_string(current_x) + '-' + std::to_string(curretn_y - 1) + ".txt");
    if (file.is_open())
    {
        top_exist = true;
        top_loaded_values.resize(CHUNK_SIZE * CHUNK_SIZE, 0);
        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i)
        {
            file >> top_loaded_values[i];
        }
        file.close();


        for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            current_mesh[0][i] = top_loaded_values[CHUNK_SIZE * (CHUNK_SIZE - 1) + i];
        }
    }
//------------------------------------------------------------------------------------------------------
    bool bottom_exist = false;
    std::vector<float> bottom_loaded_values;
    file.open("saves\\" + std::to_string(current_x) + '-' + std::to_string(curretn_y + 1) + ".txt");
    if (file.is_open())
    {
        bottom_exist = true;
        bottom_loaded_values.resize(CHUNK_SIZE * CHUNK_SIZE, 0);
        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i)
        {
            file >> bottom_loaded_values[i];
        }
        file.close();

        for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            current_mesh[CHUNK_SIZE - 1][i] = bottom_loaded_values[i];
        }
    }
//------------------------------------------------------------------------------------------------------
    bool left_exist = false;
    std::vector<float> left_loaded_values;
    file.open("saves\\" + std::to_string(current_x - 1) + '-' + std::to_string(curretn_y) + ".txt");
    if (file.is_open())
    {
        left_exist = true;
        left_loaded_values.resize(CHUNK_SIZE * CHUNK_SIZE, 0);
        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i)
        {
            file >> left_loaded_values[i];
        }
        file.close();

        for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            current_mesh[i][0] = left_loaded_values[i * CHUNK_SIZE + (CHUNK_SIZE - 1)];
        }
    }
 //------------------------------------------------------------------------------------------------------
    bool right_exist = false;
    std::vector<float> right_loaded_values;
    file.open("saves\\" + std::to_string(current_x + 1) + '-' + std::to_string(curretn_y) + ".txt");
    if (file.is_open())
    {
        right_exist = true;
        right_loaded_values.resize(CHUNK_SIZE * CHUNK_SIZE, 0);
        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i)
        {
            file >> right_loaded_values[i];
        }
        file.close();

        for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            current_mesh[i][CHUNK_SIZE - 1] = right_loaded_values[i * CHUNK_SIZE];
        }
    }
//------------------------------------------------------------------------------------------------------

    while (step > 1)
    {

        half = step / 2;

        //DIAMOND
        for (int y = half; y < CHUNK_SIZE; y += step)
        {
            for (int x = half; x < CHUNK_SIZE; x += step)
            {
            //---------------------------------------------------------------------------------------------------------
                if (y - half == 0 and top_exist)
                {
                    topLeft = top_loaded_values[CHUNK_SIZE * (CHUNK_SIZE - 1) + (x - half)];
                }
                else if (x - half < 0 and left_exist)
                {
                    topLeft = left_loaded_values[(y - half) * CHUNK_SIZE + (CHUNK_SIZE - 1 + (x - half))];
                }
                else if ((y - half == 0 and top_exist) and (x - half < 0 and left_exist))
                {
                    topLeft = top_loaded_values[CHUNK_SIZE * (CHUNK_SIZE - 1) + (CHUNK_SIZE - 1 + (x - half))];
                }
                else
                {
                    topLeft = current_mesh[y - half][x - half];
                }
            //---------------------------------------------------------------------------------------------------------
                if (y - half == 0 and top_exist)
                {
                    topRight = top_loaded_values[CHUNK_SIZE * (CHUNK_SIZE - 1) + (x + half)];
                }
                else if (x + half >= CHUNK_SIZE and right_exist)
                {
                    topRight = right_loaded_values[(y - half) * CHUNK_SIZE + (x + half - CHUNK_SIZE)];
                }
                else if ((y - half == 0 and top_exist) and (x + half >= CHUNK_SIZE and right_exist))
                {
                    topRight = top_loaded_values[CHUNK_SIZE * (CHUNK_SIZE - 1) + (x + half - CHUNK_SIZE)];
                }
                else
                {
                    topRight = current_mesh[y - half][x + half];
                }
            //---------------------------------------------------------------------------------------------------------
                if (y + half >= CHUNK_SIZE and bottom_exist)
                {
                    bottomRight = bottom_loaded_values[(x + half)];
                }
                else if (x + half >= CHUNK_SIZE and right_exist)
                {
                    bottomRight = right_loaded_values[(y + half - CHUNK_SIZE) * CHUNK_SIZE + (x + half - CHUNK_SIZE)];
                }
                else if ((y + half >= CHUNK_SIZE and bottom_exist) and (x + half >= CHUNK_SIZE and right_exist))
                {
                    bottomRight = bottom_loaded_values[(x + half - CHUNK_SIZE)];
                }
                else
                {
                    bottomRight = current_mesh[y + half][x + half];
                }
            //---------------------------------------------------------------------------------------------------------
                if (y + half >= CHUNK_SIZE and bottom_exist)
                {
                    bottomLeft = bottom_loaded_values[(x - half)];
                }
                else if (x - half < 0 and left_exist)
                {
                    bottomLeft = left_loaded_values[(y + half) * CHUNK_SIZE + (CHUNK_SIZE - 1 + (x - half))];
                }
                else if ((y + half >= CHUNK_SIZE and bottom_exist) and (x - half < 0 and left_exist))
                {
                    bottomLeft = bottom_loaded_values[(CHUNK_SIZE - 1 + (x - half))];
                }
                else
                {
                    bottomLeft = current_mesh[y + half][x - half];
                }
            //---------------------------------------------------------------------------------------------------------

                avg = (topLeft + topRight + bottomRight + bottomLeft) / 4.0f;
                random = get_random_value(-range, range);
                value = avg + random;

                value = std::fmaxf(-127.0f, std::fminf(127.0f, value));

                current_mesh[y][x] = value;
            }
        }

        //SQUARE 

        for (int y = 0; y < CHUNK_SIZE; y += half)
        {
            int start;
            if ((y / half) % 2 == 0)
            {
                start = half;
            }
            else
            {
                start = 0;
            }

            for (int x = start; x < CHUNK_SIZE; x += step)
            {
                if (x % step == 0 and y % step == 0)
                {
                    continue;
                }


                if ((top_exist and y == 0) or
                    (bottom_exist and y == CHUNK_SIZE - 1) or
                    (left_exist and x == 0) or
                    (right_exist and x == CHUNK_SIZE - 1))
                {
                    continue;
                }

                sum = 0;
                count = 0;

                if (y - half >= 0)
                {
                    if (y - half == 0 and top_exist)
                    {
                        sum += top_loaded_values[CHUNK_SIZE * (CHUNK_SIZE - 1) + x];
                    }
                    else
                    {
                        sum += current_mesh[y - half][x];
                    }
                    ++count;
                }

                if (y + half < CHUNK_SIZE)
                {
                    if (y + half == CHUNK_SIZE - 1 and bottom_exist)
                    {
                        sum += bottom_loaded_values[x];
                    }
                    else
                    {
                        sum += current_mesh[y + half][x];
                    }
                    ++count;
                }

                if (x - half >= 0)
                {
                    if (x - half == 0 and left_exist)
                    {
                        sum += left_loaded_values[y * CHUNK_SIZE + (CHUNK_SIZE - 1)];
                    }
                    else
                    {
                        sum += current_mesh[y][x - half];
                    }
                    ++count;
                }

                if (x + half < CHUNK_SIZE)
                {
                    if (x + half == CHUNK_SIZE - 1 and right_exist)
                    {
                        sum += right_loaded_values[y * CHUNK_SIZE];
                    }
                    else
                    {
                        sum += current_mesh[y][x + half];
                    }
                    ++count;
                }

                if (count > 0)
                {
                    avg = sum / count;
                    random = get_random_value(-range, range);
                    value = avg + random;

                    value = std::fmaxf(-127.0f, std::fminf(127.0f, value));

                    current_mesh[y][x] = value;
                }
            }
        }

        step = half;
        range *= roughness;
    }

    int color_code;

    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            color_code = 127 + current_mesh[i][j];
            if (color_code >= 127)
            {
                chunk_view.setPixel(sf::Vector2u(j, i), sf::Color(0, color_code, 0));
            }
            else
            {
                chunk_view.setPixel(sf::Vector2u(j, i), sf::Color(0, 0, color_code));
            }
        }
    }

    the_core.resource_manager.get_texture(Textures:: main_t).loadFromImage(chunk_view);
}

void Application::init_chunk()
{
	chunk = Entity(sf::Vector2i(CHUNK_SIZE, CHUNK_SIZE), main_t);
	chunk.setScale(sf::Vector2f(645/CHUNK_SIZE, 645/CHUNK_SIZE));

	chunk.set_name("chunk");
	chunk.set_colliding(false);
	chunk.set_updatable(false);

    sub_chunk = Entity(sf::Vector2i(CHUNK_SIZE, CHUNK_SIZE), submain);
    sub_chunk.setScale(sf::Vector2f(645 / CHUNK_SIZE, 645 / CHUNK_SIZE));
    sub_chunk.set_name("subchunk");
    sub_chunk.set_colliding(false);
    sub_chunk.set_updatable(false);
  
	
	app_scene.add(&chunk, 0);
    app_scene.add(&sub_chunk, 0);

}

void Application::init_keys()
{
    key_status[sf::Keyboard::Scancode::W] = false;
    key_status[sf::Keyboard::Scancode::A] = false;
    key_status[sf::Keyboard::Scancode::S] = false;
    key_status[sf::Keyboard::Scancode::D] = false;

    key_status[sf::Keyboard::Scancode::Backspace] = false;
}

void Application::generate_chunk_by_side(const Sides& side)
{
    save_chunk(current_x, curretn_y);
    
    bool error = false;

    float Af, Bf, Cf, Df, Rf;

    if (!get_value(Af, A.get_text()) or !(Af >= -127 and Af <= 127))
    {
        A.body.setFillColor(sf::Color(240, 128, 128));
        error = true;
    }
    if (!get_value(Bf, B.get_text()) or !(Bf >= -127 and Bf <= 127))
    {
        B.body.setFillColor(sf::Color(240, 128, 128));
        error = true;

    }
    if (!get_value(Cf, C.get_text()) or !(Cf >= -127 and Cf <= 127))
    {
        C.body.setFillColor(sf::Color(240, 128, 128));
        error = true;
    }
    if (!get_value(Df, D.get_text()) or !(Df >= -127 and Df <= 127))
    {
        D.body.setFillColor(sf::Color(240, 128, 128));
        error = true;
    }
    if (!get_value(Rf, R.get_text()) or !(Rf >= 0 and Rf <= 1))
    {
        R.body.setFillColor(sf::Color(240, 128, 128));
        error = true;
    }

    if (error) { return; }


    the_core.resource_manager.get_texture(submain) = the_core.resource_manager.get_texture(main_t);
    sub_chunk.setPosition(chunk.getPosition());

    switch (side)
    {
    case Sides::N: { curretn_y -= 1; } break;
    case Sides::S: { curretn_y += 1; } break;
    case Sides::E: { current_x += 1; } break;
    case Sides::W: { current_x -= 1; } break;
    default:
        break;
    }

    transition_destination = side;
    animated_transition = true;

    chunk.setPosition(sf::Vector2f(current_x * chunk.getGlobalBounds().size.x, curretn_y * chunk.getGlobalBounds().size.y));

    if (roughness != Rf)
    {
        std::filesystem::remove_all("saves");
        std::filesystem::create_directory("saves");
    }
    
    roughness = Rf;

    if (!load_chunk(current_x, curretn_y))
    {
        generate_chunk(Af,Bf,Cf,Df);
    }
}
	

Application::Application()
{

    current_mesh = std::vector<std::vector<float>>(CHUNK_SIZE, std::vector<float>(CHUNK_SIZE, 0));

    generate_chunk_by_side_slot.reassign(&Application::generate_chunk_by_side, this);
    connect(&generate_signal, &generate_chunk_by_side_slot);

    this->gen = new std::mt19937(this->rd());

	app_scene = Scene(3);
	
	the_core.set_event_handler(&event_handler);
	the_core.change_scene(&app_scene);

	init_resources();
	init_chunk();
    init_interface();

	the_core.add_view("main", sf::View());
	the_core.get_view("main")->setCenter(chunk.getGlobalBounds().getCenter());
	the_core.get_view("main")->setSize(sf::Vector2f(645, 645));

}

void Application::run()
{
    std::filesystem::remove_all("saves\\");
    std::filesystem::create_directory("saves");
    generate_chunk(0, 0, 0, 0);
	the_core.run(645, 645, "DmSq by fAD-SDK 2.0.0", 480, sf::State::Windowed);
}
