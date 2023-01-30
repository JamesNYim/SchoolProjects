#include "grid.h"
#include <cassert>

// Constants ---------------------------------------------------------
Grid::weight_t const Grid::NOEDGE = -1;
Grid::weight_t const Grid::PATH = 1;
std::string const P3_NODE = "255 255 255\n";
std::string const P3_EDGE = "255 255 255\n";
std::string const P3_WALL = "0 0 0\n";
std::string const P3_PATH = "255 0 0\n";

// Definitions -------------------------------------------------------
std::ostream& operator<<(std::ostream &out, Point const &p) {
    return out << '(' << p.x << ',' << p.y << ')';
}

Grid::Node::Node() 
{
    // TODO
	weights[DOWN] = -1;
	weights[RIGHT] = -1;
}

Grid::Grid(unsigned height, unsigned width)
    : nodes_(height, decltype(nodes_)::value_type(width))
{
    if (height == 0 || width == 0)
    {
	    throw std::invalid_argument("Area cannot be 0");
    }

}
unsigned Grid::getHeight() const 
{
    // TODO
    return nodes_.size();
}

unsigned Grid::getWidth() const 
{
    // TODO
    return nodes_.front().size();
}

Grid::weight_t Grid::getEdge(Point const &a, Point const &b) const 
{
    // TODO
    
    //Right
    if ((a.x + 1 == b.x || b.x + 1 == a.x) && (a.y == b.y))
    {
	    return std::min(nodes_[a.y][a.x].weights[1], nodes_[b.y][b.x].weights[1]);
    }
    
    //Down
    if ((a.y + 1 == b.y || b.y - 1 == a.y) && (a.x == b.x))
    {
	    return std::min(nodes_[a.y][a.x].weights[0], nodes_[b.y][b.x].weights[0]);
    }
    else
    {
	    return 0;
    }

}

bool Grid::setEdge(Point const &a, Point const &b, weight_t weight) 
{
    // TODO
    //Right
    if ((a.x + 1 == b.x || b.x + 1 == a.x) && (a.y == b.y))
    {
	    if (nodes_[a.y][a.x].weights[1] < nodes_[b.y][b.x].weights[1])
	    { 
		    nodes_[a.y][a.x].weights[1] = weight;
	    }
	    else
	    {
		    nodes_[b.y][b.x].weights[1] = weight;
	    }
	    return true;	    
    }

    //Down
    if ((a.y + 1 == b.y || b.y + 1 == a.y) && (a.x == b.x))
    {
	    if (nodes_[a.y][a.x].weights[0] < nodes_[b.y][b.x].weights[0]) 
	    {
		    nodes_[a.y][a.x].weights[0] = weight;
	    }
	    else
	    {
		    nodes_[b.y][b.x].weights[0] = weight;
	    }
	    return true;
    }
    else
    {
            return false;
    }
}

void Grid::draw(std::ostream &out) const 
{
    // TODO
    unsigned heightOfPic = (getHeight() * 2) + 1;
    unsigned widthOfPic = (getWidth() * 2) + 1;
    out << "P3\n";
    out << widthOfPic << " " << heightOfPic << "\n";
    out << "255\n";

    //drawing the top border
    for (unsigned i = 0; i < widthOfPic; i++)
    {
	    out << P3_WALL;
    }
    out << "\n";
    
    //Drawing the middle bits
    for (unsigned row = 0; row < getHeight(); row++)
    {
	    //Draws left border
	    out << P3_WALL;
	    //Drawing Node Line
	    for (unsigned col = 0; col < getWidth(); col++)
	    {
		    out << "200 200 200\n";
		    //Right Edge Drawing
		    weight_t rightEdge = nodes_[row][col].weights[1];

		    if (rightEdge != Grid::NOEDGE)
		    {
			    out << P3_EDGE;
		    }
		    else 
		    {
			    out << P3_WALL;
		    }
		   
    	    }

	    //Drawing Wall Line
	    for (unsigned col = 0; col < getWidth(); col++)
	    {
		    //Down Edge Drawing
                    weight_t downEdge = nodes_[row][col].weights[0];
                    if (downEdge != Grid::NOEDGE)
                    {
                            out << P3_EDGE;
                    }
                    else
                    {
                            out << P3_WALL;
                    }
		    
		    //Drawing wall
		    out << P3_WALL;

	    }

    }
    return;

}


void Grid::serialize(std::ostream &out) const {
    // TODO
    return;
}


Grid Grid::load(std::istream &in) {
    // TODO
	Grid g  = Grid(1, 1);
	return g;
}
