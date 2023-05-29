#include <barnes_hut_tree.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

//inner node struct definitions//

/**
 * @brief Construct a new b_h_node object.
*/
b_h_tree::b_h_node::b_h_node()
{

}

/**
 * @brief Construct a new b_h_node object.
 * 
 * @param _top_left The top left coordinate of the quadrant that this node will represent.
 * @param _width The width of the quadrant that this node will represent.
 * @param _height The height of the quadrant that this node will represent.
*/
b_h_tree::b_h_node::b_h_node(sf::Vector2<int> _top_left, int _width, int _height)
: top_left{_top_left}, width{_width}, height{_height}
{

}

/**
 * @brief  Determines whether this node is an internal node. An internal node is one that represents the body objects of its children nodes.
 * 
 * @return bool True if this node is an internal node, false otherwise.
*/
bool b_h_tree::b_h_node::is_internal()
{
    return node_body == nullptr && children.size() != 0;
}

/**
 * @brief Determines whether this node is an external node. An external node represents a single body object. It is a leaf of the quadtree.
 * 
 * @return bool True if this node is an external node, false otherwise.
*/
bool b_h_tree::b_h_node::is_external()
{
    return node_body != nullptr && children.size() == 0;
}

/**
 * @brief Determines whether this node is an empty node. An empty node has no children and has no body object that it represents.
 * 
 * @return bool True if this node is an empty node, false otherwise.
*/
bool b_h_tree::b_h_node::is_empty()
{
    return node_body == nullptr && children.size() == 0;
}

/**
 * @brief Updates the total mass of this node, if this node is an inner node.
*/
void b_h_tree::b_h_node::update_total_mass()
{
    if(is_external())
    {
        total_mass = node_body -> get_mass();
    }
    else if(is_internal())
    {
        double new_total_mass{};
        for(std::shared_ptr<b_h_node> child_node: children)
        {
            new_total_mass += child_node -> total_mass;
        }

        total_mass = new_total_mass;
    }
}

/**
 * @brief Updates the center of mass represented by this node, if this node is an inner node.
*/
void b_h_tree::b_h_node::update_center_of_mass()
{
    if(is_external())
    {
        center_of_mass = node_body -> get_position();
    }
    else if(is_internal())
    {
        sf::Vector2<double> new_center_of_mass{};

        for(std::shared_ptr<b_h_node> child_node: children)
        {
            new_center_of_mass += ((child_node -> center_of_mass) * child_node -> total_mass);
        }

        new_center_of_mass /= total_mass;

        center_of_mass = new_center_of_mass;
    }

}

/**
 * @brief Determines if a body object is inside the quadrant represented by this node.
 * 
 * @param b Will determine if the body object being pointed to is inside the quadrant represented by this node.
 * @return bool True if the body object is inside the quadrant, false otherwise.
*/
bool b_h_tree::b_h_node::in_quadrant(body* b)
{
    sf::Vector2<double> b_pos = b -> get_position();

    return b_pos.x >= top_left.x && b_pos.y >= top_left.y && b_pos.x < top_left.x + width && b_pos.y < top_left.y + height;

}

/**
 * @brief Creates children for this node. Essentially changes this node to be an inner node in the quadtree.
*/
void b_h_tree::b_h_node::create_children()
{
    int half_width = width / 2;
    int half_height = height / 2;

    std::shared_ptr<b_h_node> q1 = std::make_shared<b_h_node>(sf::Vector2(top_left.x + half_width, top_left.y), half_width, half_height);
    std::shared_ptr<b_h_node> q2 = std::make_shared<b_h_node>(top_left, half_width, half_height);
    std::shared_ptr<b_h_node> q3 = std::make_shared<b_h_node>(sf::Vector2(top_left.x, top_left.y + half_height), half_width, half_height);
    std::shared_ptr<b_h_node> q4 = std::make_shared<b_h_node>(sf::Vector2(top_left.x + half_width, top_left.y + half_height), half_width, half_height);

    children.push_back(q1);
    children.push_back(q2);
    children.push_back(q3);
    children.push_back(q4);
}


//tree definitions  
/**
 * @brief Constructs the quadtree.
 * 
 * @param bodies Vector containing pointers to bodies in the sim from which the tree will be constructed.
*/
b_h_tree::b_h_tree(const std::vector<body*>& bodies)
{
    root = std::make_shared<b_h_node>(sf::Vector2<int>(0, 0), settings::DIMENSIONS.first, settings::DIMENSIONS.second);

    for(body* b : bodies)
    {
        insert_node(root, b);
    }
}

/**
 * @brief Gets the acceleration induced on the body being pointed to by b.
 * 
 * @param b The induced acceleration on the body pointed to by b from other bodies will be returned.
 * @return sf::Vector2<double> Acceleration vector induced on b.
*/
sf::Vector2<double> b_h_tree::get_accel(body* b) const
{
    return calc_accel(root, b);
}

/**
 * @brief Recursively inserts a node representing a body in the system into the quadtree. This is the crux in
 *        constructing the quadtree utilized in the Barnes Hut algorithm.
 *        Check https://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/barnes-hut.html
 *        for the algorithm.
 * 
 * @param root The node being examined in current recursive call.
 * @param new_body Pointer to the body object that is being inserted into the quadtree.
*/
void b_h_tree::insert_node(std::shared_ptr<b_h_node> root, body* new_body)
{
    if(root -> is_empty())
    {
        root -> node_body = new_body;
    }
    else if(root -> is_internal())
    {

        for(std::shared_ptr<b_h_node>  quadrant : root -> children)
        {
            if(quadrant -> in_quadrant(new_body))
            {
                insert_node(quadrant, new_body);
                break;
            }
        }
        root -> update_total_mass();
        root -> update_center_of_mass();
    }
    else if(root -> is_external())
    {
        body* body_a = root -> node_body;

        root -> node_body = nullptr;

        body* body_b = new_body;

        root -> create_children();

        for(std::shared_ptr<b_h_node>  quadrant : root -> children)
        {
            if(quadrant -> in_quadrant(body_a))
            {
                insert_node(quadrant, body_a);
                break;
            }
        }

        for(std::shared_ptr<b_h_node>  quadrant : root -> children)
        {
            if(quadrant -> in_quadrant(body_b))
            {
                insert_node(quadrant, body_b);
                break;
            }
        }

        root -> update_total_mass();
        root -> update_center_of_mass();
    }

}

/**
 * @brief Recursively calculates the acceleration induced by the other bodies in the quadtree
 *        on the inputted body.
 *        Check https://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/barnes-hut.html
 *        for the algorithm.
 * 
 * @param root The current node being examined in the recursive call.
 * @param b The acceleration induced on the body pointed to by b will be calculated.
 * @return sf::Vector2<double> The induced acceleration produced on the inputted body by the body represented by the current node being examined.
*          If the a bunch of bodies are far enough, the node will represent a collection of these bodies and the center of mass
*          formed by these bodies will be used to calculated the induced acceleration and this will be returned.
*/
sf::Vector2<double> b_h_tree::calc_accel(std::shared_ptr<b_h_node> root, body* b) const
{
    if(root -> is_external() && root -> node_body != b)
    {
        return b -> calc_accel(root -> node_body);
    }
    else if(root -> is_internal())
    {
        double body_pos_x = (b -> get_position()).x;
        double body_pos_y = (b -> get_position()).y;

        double center_of_mass_x = (root -> center_of_mass).x;
        double center_of_mass_y = (root -> center_of_mass).y;

        double distance = sqrt(pow(body_pos_x - center_of_mass_x, 2) + pow(body_pos_y - center_of_mass_y, 2));

        double ratio = root -> width / distance;

        if(ratio < settings::RATIO_EPSILON)
        {
            body center_of_mass_rep{root -> total_mass, 0, true, root -> center_of_mass};

            return b -> calc_accel(&center_of_mass_rep);
        }
        else
        {
            sf::Vector2<double> net_accel{0, 0};

            for(std::shared_ptr<b_h_node>  node : root -> children)
            {
                net_accel += calc_accel(node, b);
            }

            return net_accel;
        }

    }
    else
    {
        return sf::Vector2<double>{0, 0};
    }
}   
