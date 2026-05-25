#include "Application.h"

void Application::init_resources()
{
	current_chunk_view.loadFromFile("resources\\textures\\plate.png");
	the_core.resource_manager.add_texture("resources\\textures\\plate.png", 0);
    the_core.resource_manager.add_texture("resources\\textures\\interface_background.png", 1);

    the_core.resource_manager.add_font("resources\\fonts\\MonaspaceNeon-Medium.otf", 0);
    //the_core.resource_manager.get_font(0).setSmooth(false);
}

void Application::init_interface()
{

    lazy_otline = Entity(sf::Vector2i(204, 104), 1);
    lazy_otline.set_name("0");
    lazy_otline.set_colliding(false);
    lazy_otline.set_updatable(false);
    lazy_otline.setPosition(sf::Vector2f(645 - 204, 645 - 104));
    lazy_otline.setColor(sf::Color::Black);

    app_scene.add(&lazy_otline, 1);

    
    interface_back = Entity(sf::Vector2i(200, 100), 1);
    interface_back.set_name("1");
    interface_back.set_colliding(false);
    interface_back.set_updatable(false);
    interface_back.setPosition(sf::Vector2f(645-202, 645-102));

    app_scene.add(&interface_back, 1);

    A_input.body.setSize(sf::Vector2f(80, 20));
    A_input.set_name("A_input");
    A_input.body.setPosition(interface_back.getPosition());
    A_input.body.move(sf::Vector2f(30, 10));
    A_input.set_text("-80");
    app_scene.add(&A_input, 2);

    B_input.body.setSize(sf::Vector2f(80, 20));
    B_input.set_name("B_input");
    B_input.body.setPosition(interface_back.getPosition());
    B_input.body.move(sf::Vector2f(110, 10));
    B_input.set_text("-80");
    app_scene.add(&B_input, 2);

    D_input.body.setSize(sf::Vector2f(80, 20));
    D_input.set_name("D_input");
    D_input.body.setPosition(interface_back.getPosition());
    D_input.body.move(sf::Vector2f(30, 40));
    D_input.set_text("-80");
    app_scene.add(&D_input, 2);

    C_input.body.setSize(sf::Vector2f(80, 20));
    C_input.set_name("C_input");
    C_input.body.setPosition(interface_back.getPosition());
    C_input.body.move(sf::Vector2f(110, 40));
    C_input.set_text("-80");
    app_scene.add(&C_input, 2);

    r_factor_input.body.setSize(sf::Vector2f(80, 20));
    r_factor_input.set_name("r_input");
    r_factor_input.body.setPosition(interface_back.getPosition());
    r_factor_input.body.move(sf::Vector2f(30, 70));
    r_factor_input.set_text("0.6");
    app_scene.add(&r_factor_input, 2);

    A_B_l.text->setString("AB");
    A_B_l.set_resource(0);
    A_B_l.text->setCharacterSize(72);
    A_B_l.text->setScale(sf::Vector2f(0.2, 0.2));
    A_B_l.text->setPosition(A_input.body.getPosition());
    A_B_l.text->move(sf::Vector2f(-25, 0));
    A_B_l.set_name("A-B_l");
    A_B_l.text->setFillColor(sf::Color::Black);
    app_scene.add(&A_B_l, 2);

    C_D_l.text->setString("DC");
    C_D_l.set_resource(0);
    C_D_l.text->setCharacterSize(72);
    C_D_l.text->setScale(sf::Vector2f(0.2, 0.2));
    C_D_l.text->setPosition(D_input.body.getPosition());
    C_D_l.text->move(sf::Vector2f(-25, 0));
    C_D_l.set_name("C-D_l");
    C_D_l.text->setFillColor(sf::Color::Black);
    app_scene.add(&C_D_l, 2);

    r_l.text->setString("R");
    r_l.set_resource(0);
    r_l.text->setCharacterSize(72);
    r_l.text->setScale(sf::Vector2f(0.2, 0.2));
    r_l.text->setPosition(r_factor_input.body.getPosition());
    r_l.text->move(sf::Vector2f(-25, 0));
    r_l.set_name("r_l");
    r_l.text->setFillColor(sf::Color::Black);
    app_scene.add(&r_l, 2);
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
            
            if (color_code > 50)
            {
                current_chunk_view.setPixel(sf::Vector2u(x, y), sf::Color(color_code, color_code, color_code));
            }
            else
            {
                current_chunk_view.setPixel(sf::Vector2u(x, y), sf::Color(0, 0, color_code * 4));
            }

            current_mesh[y][x] = value;
            ++x;
            if (x >= CHUNK_SIZE)
            {
                x = 0;
                ++y;
            }
        }

        the_core.resource_manager.get_texture(0).loadFromImage(current_chunk_view);
    }

    return res;
}

float Application::get_random_value(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(*this->gen);
}


void Application::generate_chunk(const float& A, const float& B, const float& C, const float& D)
{
    current_chunk_view.loadFromFile("resources\\textures\\plate.png");

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
                    count++;
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
                    count++;
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
                    count++;
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
                    count++;
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
            if (color_code > 50)
            {
                current_chunk_view.setPixel(sf::Vector2u(j, i), sf::Color(color_code, color_code, color_code));
            }
            else
            {
                current_chunk_view.setPixel(sf::Vector2u(j, i), sf::Color(0, 0, color_code * 4));
            }
        }
    }

    the_core.resource_manager.get_texture(0).loadFromImage(current_chunk_view);
}

void Application::init_chunk()
{
	chunk = Entity(sf::Vector2i(CHUNK_SIZE, CHUNK_SIZE), 0);
	chunk.setScale(sf::Vector2f(645/CHUNK_SIZE, 645/CHUNK_SIZE));

	chunk.set_name("chunk");
	chunk.set_colliding(false);
	chunk.set_updatable(false);
	
	app_scene.add(&chunk, 0);
}

void Application::generate_chunk_by_side(const Sides& side)
{
    save_chunk(current_x, curretn_y);

    int x_back_up = current_x;
    int y_back_up = curretn_y;

    switch (side)
    {
    case Sides::N: { curretn_y -= 1; } break;
    case Sides::S: { curretn_y += 1; } break;
    case Sides::E: { current_x += 1; } break;
    case Sides::W: { current_x -= 1; } break;
    default:
        break;
    }
    if (!load_chunk(current_x, curretn_y))
    {
        float A = std::stof(A_input.get_text());
        float B = std::stof(B_input.get_text());
        float C = std::stof(C_input.get_text());
        float D = std::stof(D_input.get_text());

        roughness = std::stof(r_factor_input.get_text());

        bool error_flag = false;

        if (A < -127 or A > 127)
        {
            error_flag = true;
            A_input.body.setFillColor(sf::Color(240, 128, 128));
        }
        if (B < -127 or B > 127)
        {
            error_flag = true;
            B_input.body.setFillColor(sf::Color(240, 128, 128));
        }
        if (C < -127 or C > 127)
        {
            error_flag = true;
            C_input.body.setFillColor(sf::Color(240, 128, 128));
        }
        if (D < -127 or D > 127)
        {
            error_flag = true;
            D_input.body.setFillColor(sf::Color(240, 128, 128));
        }
        if (roughness < 0 or roughness > 1)
        {
            error_flag = true;
            r_factor_input.body.setFillColor(sf::Color(240, 128, 128));
        }
       
        if (error_flag) 
        {
            current_x = x_back_up;
            curretn_y = y_back_up;
            return; 
        }


        

        generate_chunk(A, B, C, D);
    }
    else
    {

    }
    pre_side = side;
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
    the_core.emit(&generate_signal);
	the_core.run(645, 645, "DmSq by fAD-SDK 2.0.0", 60, sf::State::Windowed);
}
