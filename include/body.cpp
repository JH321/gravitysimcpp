#include <body.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief Construct a new body object.
 *
 * @param _mass Mass of the body.
 * @param _radius Radius of the body.
 * @param _inplace Whether the body can move.
 * @param _position The starting position of the body.
 * @param _velocity The initial velocity of the body
 */
body::body(double _mass, int _radius, bool _inplace, sf::Vector2<double> _position, sf::Vector2<double> _velocity)
: mass{_mass}, radius{_radius}, inplace{_inplace}, position{_position}, velocity{_velocity}, acceleration{0, 0}
{}


/**
 * @brief Gets the radius (pixels) of the body.
 * @return int The radius (pixel count) of the body.
 */
int body::get_radius()
{
    return radius;
}


/**
 * @brief Gets the mass of the body.
 * @return double The mass of the body.
 */
double body::get_mass()
{
    return mass;
}


/**
 * @brief Gets the position of the body.
 * @return double The 2D coordinates of the body.
 */
sf::Vector2<double> body::get_position()
{
    return position;
}


/**
 * @brief Function to call to initiate updating of position given 
 *        a vector of other bodies exerting a force on this body and
 *        a small time segment.
 * 
 * @param bodies Vector containing other bodies exerting a force on this body.
 * @param dt Time segment (time since last frame update) in seconds.
 */
void body::update_position(const std::vector<body*>& bodies, double dt)
{
    if(!inplace)
    {
        increment_position(dt);
        update_velocity(bodies, dt);
    }

    if(position.x < 0 || position.x > settings::DIMENSIONS.first)
    {
        if(position.x < 0)
        {
            position = sf::Vector2<double>{radius * 1.0, position.y};
        }
        if(position.x > settings::DIMENSIONS.first)
        {
            position = sf::Vector2<double>{settings::DIMENSIONS.first - radius * 1.0, position.y};
        }

    }
    if(position.y < 0 || position.y > settings::DIMENSIONS.second)
    {
        if(position.y < 0)
        {
            position = sf::Vector2<double>{position.x, radius * 1.0};
        }
        if(position.y > settings::DIMENSIONS.second)
        {
            position = sf::Vector2<double>{position.x, settings::DIMENSIONS.second - radius * 1.0};
        }
    }

}

void body::update_position_barnes_hut(const b_h_tree& body_tree, double dt)
{
    if(!inplace)
    {
        increment_position(dt);
        update_velocity_barnes_hut(body_tree, dt);
    }

    if(position.x < 0 || position.x > settings::DIMENSIONS.first)
    {
        if(position.x < 0)
        {
            position = sf::Vector2<double>{radius * 1.0, position.y};
        }
        if(position.x > settings::DIMENSIONS.first)
        {
            position = sf::Vector2<double>{settings::DIMENSIONS.first - radius * 1.0, position.y};
        }

    }
    if(position.y < 0 || position.y > settings::DIMENSIONS.second)
    {
        if(position.y < 0)
        {
            position = sf::Vector2<double>{position.x, radius * 1.0};
        }
        if(position.y > settings::DIMENSIONS.second)
        {
            position = sf::Vector2<double>{position.x, settings::DIMENSIONS.second - radius * 1.0};
        }
    }

}

/**
 * @brief Calculates the acceleration induced on this body by another body.
 * 
 * @param bodyptr Pointer to the body object inducing an acceleration on this body.
 * @return sf::Vector2<double> The acceleration vector induced on this body.
 */
sf::Vector2<double> body::calc_accel(const body* bodyptr)
{
    double x_dist = bodyptr -> position.x - this -> position.x;
    double y_dist = bodyptr -> position.y - this -> position.y;

    double theta = atan2(y_dist, x_dist);

    double dist_mag = sqrt(pow(x_dist, 2) + pow(y_dist, 2));

    double accel_mult = 1;
    if(dist_mag <= this -> radius + bodyptr -> radius)
    {

        dist_mag = this -> radius + bodyptr -> radius;
        accel_mult = -1;
    }

    double accel_mag = (settings::G * bodyptr -> mass) / (pow(dist_mag, 2));

    accel_mag *= accel_mult;

    sf::Vector2<double> new_acceleration{accel_mag * cos(theta), accel_mag * sin(theta)};

    return new_acceleration;
}


/**
 * @brief Increments the position of the body given some 
 *        time segment and velocity.
 * 
 * @param dt Time segment from last frame in seconds.
 */
void body::increment_position(double dt)
{
    sf::Vector2<double> delta_x = velocity * dt;
    position = position + delta_x;
}

/**
 * @brief Increments the velocity of the body given some 
 *        time segment and acceleration.
 * 
 * @param dt Time segment (time since last frame update) in seconds.
 */
void body::increment_velocity(double dt)
{
    sf::Vector2<double> delta_v = acceleration * dt;
    velocity = velocity + delta_v;
}

/**
 * @brief Function to call to initiate updating of velocity given 
 *        a vector of other bodies exerting a force on this body and
 *        a small time segment.
 * 
 * @param bodies Vector containing other bodies exerting a force on this body.
 * @param dt Time segment (time since last frame update) in seconds.
 */
void body::update_velocity(const std::vector<body*>& bodies, double dt)
{
    if(position.x < 0 || position.x > settings::DIMENSIONS.first)
    {
        velocity = sf::Vector2<double>{-velocity.x, velocity.y};
    }
    if(position.y < 0 || position.y > settings::DIMENSIONS.second)
    {
        velocity = sf::Vector2<double>{velocity.x, -velocity.y};
    }

    update_acceleration(bodies);
    increment_velocity(dt);
    
}

/**
 * @brief Function to call to initiate updating of velocity given 
 *        a vector of other bodies exerting a force on this body and
 *        a small time segment.
 * 
 * @param bodies Vector containing other bodies exerting a force on this body.
 * @param dt Time segment (time since last frame update) in seconds.
 */
void body::update_velocity_barnes_hut(const b_h_tree& body_tree, double dt)
{

    if(position.x < 0 || position.x > settings::DIMENSIONS.first)
    {
        velocity = sf::Vector2<double>{-velocity.x, velocity.y};
    }
    if(position.y < 0 || position.y > settings::DIMENSIONS.second)
    {
        velocity = sf::Vector2<double>{velocity.x, -velocity.y};
    }
    update_acceleration_barnes_hut(body_tree);
    increment_velocity(dt);

}

/**
 * @brief Function to call to initiate updating of acceleration given 
 *        a vector of other bodies exerting a force on this body and
 *        a small time segment.
 * 
 * @param bodies Vector containing other bodies exerting a force on this body.
 * @param dt Time segment (time since last frame update) in seconds.
 */
void body::update_acceleration(const std::vector<body*>& bodies)
{
    sf::Vector2<double> new_acceleration{0, 0};
    for(const body* element : bodies)
    {

        if(element != this)
        {
        sf::Vector2<double> a_vector = calc_accel(element);
        new_acceleration = new_acceleration + a_vector;
        }

    }

    acceleration = new_acceleration;
    
}

void body::update_acceleration_barnes_hut(const b_h_tree& body_tree)
{
   
    acceleration = body_tree.get_accel(this);
    
}

