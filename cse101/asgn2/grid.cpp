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
	std::fill(weights.begin(), weights.end(), NOEDGE);
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
    if ((a.x + 1 == b.x || a.x - 1 == b.x) && (a.y == b.y))
    {
	    return nodes_[a.x][a.y].weights[1];
    }
    
    //Down
    if ((a.y + 1 == b.y || a.y - 1 == b.y) && (a.x == b.x))
    {
	    return nodes_[a.x][a.y].weights[0];
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
    if ((a.x + 1 == b.x || a.x - 1 == b.x) && (a.y == b.y))
    {
            nodes_[a.x][a.y].weights[1] = weight;
	    return true;
    }

    //Down
    if ((a.y + 1 == b.y || a.y - 1 == b.y) && (a.x == b.x))
    {
            nodes_[a.x][a.y].weights[0] = weight;
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
    out << "P3" << std::endl;
    out << widthOfPic << " " << heightOfPic << std::endl;
    out << "255" << std::endl;

    //drawing the top border
    for (unsigned i = 0; i < widthOfPic; i++)
    {
	    out << P3_WALL;
    }
    
    //Drawing the middle bits
    for (unsigned row = 0; row < getHeight(); row++)
    {
	    //Draws left border
	    out << P3_WALL;

	    //Drawing Node Line
	    for (unsigned col = 0; col < getWidth(); col++)
	    {
		   
		    //Node drawing
		    out << P3_NODE;

		    //Right Edge Drawing
		    weight_t rightEdge = getEdge({col, row}, {col + 1, row});

		    if (rightEdge == Grid::NOEDGE)
		    {
			    out << P3_WALL;
		    }
		    else if (rightEdge != Grid::NOEDGE)
		    {
			    out << P3_EDGE;
		    }
    	    }

	    //Drawing Wall Line
	    for (unsigned col = 0; col < getWidth(); col++)
	    {
		    //Down Edge Drawing
                    weight_t downEdge = getEdge({col, row}, {col, row + 1});
                    if (downEdge == Grid::NOEDGE)
                    {
                            out << P3_WALL;
                    }
                    else if (downEdge != Grid::NOEDGE)
                    {
                            out << P3_EDGE;
                    }

		    //Wall Drawing
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
