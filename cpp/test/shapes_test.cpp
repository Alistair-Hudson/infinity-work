/******************************************************************************
 *	Title:		Shapes Test
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	08.06.2020.0
 ******************************************************************************/

#include <iostream>

#include "line.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

/******MACROS******/
#define SCREEN_WIDTH    (1000)
#define SCREEN_HEIGHT   (1000)

/******TYPEDEFS*****/

/*****STRUCTS*******/

/*****CLASSES******/
class Node
{
public:
    Node();
    Node(const Node& node_);
    Node& operator= (const Node& node_);
    ~Node();

    inline Square GetShape() const;
    inline Node* NextNode() const;
    inline void SetNextNode(Node* node_);
    inline void SetShape(Square shape_);

private:
    Square shape;
    Node* next_node;
};

class Targets
{
public:
    Targets(int x_);
    Targets(const Targets& targets_);
    Targets& operator=(const Targets& targets_);
    ~Targets();

    void InsertNode(Square& shape);
    void RemoveNode(Node& node);
    inline Node* Begining() const;
    inline Node* End() const;
    void DrawAll();
    void MoveAll();
    void CheckAll(Line& target);

private:
    Node* head_node;
    Node* tail_node;
};

/******CLASS FUNCTIONS*******/
/*===NODE FUNCTIONS===*/
Node::Node()
{
    next_node = NULL;
}

Node::Node(const Node& node_)
{
    shape = node_.GetShape();
    next_node = node_.NextNode();
}

Node& Node::operator=(const Node& node_)
{
    shape = node_.GetShape();
    next_node = node_.NextNode();
    return *this;
}

Node::~Node()
{

}

Square Node::GetShape() const
{
    return shape;
}

Node* Node::NextNode() const
{
    return next_node;
}

void Node::SetNextNode(Node* node_)
{
    next_node = node_;
}

void Node::SetShape(Square shape_)
{
    shape = shape_;
}

/*===Targets Functions===*/
Targets::Targets(int x_)
{
    head_node = new Node;
    tail_node = head_node;
}

Targets::Targets(const Targets& targets_)
{
    head_node = targets_.Begining();
    tail_node = targets_.End();
}

Targets& Targets::operator=(const Targets& targets_)
{
    head_node = targets_.Begining();
    tail_node = targets_.End();
    return *this;
}

Targets::~Targets()
{
    delete tail_node;
}

void Targets::InsertNode(Square& shape)
{
    Node *new_node = new Node;
    End()->SetShape(shape);
    End()->SetNextNode(new_node);
    tail_node = new_node;

}

void Targets::RemoveNode(Node& node)
{
    Node *next_node = node.NextNode();
    next_node->SetNextNode(next_node);
    next_node->SetShape(next_node->GetShape());
    delete next_node;
}

Node* Targets::Begining() const
{
    return head_node;
}

Node* Targets::End() const
{
    return tail_node;
}

void Targets::DrawAll()
{
    Node* node =  Begining();
    while(node != End())
    {
        node->GetShape().DrawInternal();
        node = node->NextNode();
    }
}

void Targets::MoveAll()
{
    Node* node = Begining();
    Point vector(0,0);

    while(node != End())
    {
        vector.SetX((rand()%5)-10);
        vector.SetY(rand()%5);
        node->GetShape().Move(vector);
        //std::cout << node->GetShape().GetPos().GetX() << ", " << node->GetShape().GetPos().GetY() << std::endl;
        node = node->NextNode();
    }
    
}

void Targets::CheckAll(Line& target)
{
    Node* node = Begining();
    Point reset(0, 0);

    while (node != End())
    {
        if (target.GetPos().GetX()-node->GetShape().GetPos().GetX() < node->GetShape().GetLength()/2 && 
            target.GetPos().GetX()-node->GetShape().GetPos().GetX() > -node->GetShape().GetLength()/2 && 
            target.GetPos().GetY()-node->GetShape().GetPos().GetY() < node->GetShape().GetLength()/2 && 
            target.GetPos().GetY()-node->GetShape().GetPos().GetY() > -node->GetShape().GetLength()/2)
        {
            reset.SetX(rand()%SCREEN_WIDTH);
            reset.SetY(0);
            node->GetShape().SetPos(reset);
        }
    }
}

/****** GLOBAL VARIABLES*****/

/*===TARGETING RECTICLE===*/
Line target_vert(SCREEN_WIDTH/2, 
                SCREEN_HEIGHT/2, 
                90, 100, COLOR_RED);
Line target_horiz(SCREEN_WIDTH/2, 
                SCREEN_HEIGHT/2, 
                0, 100, COLOR_RED);

/*===SHAPE TARGETS===*/
Square square(0, 0, 0, 100, COLOR_GREEN);
Circle circle(0, 0, 0, 100, COLOR_YELLOW);
Targets target_list(0);

/******INTERNAL FUNCTION DECLARATION******/

static void DrawFunc();
static int KeyCapture(unsigned char key, int x, int y);
static int TimedEvents();

bool operator!=(const Node& node1, const Node& node2);

/*****FUNCTION DEFINITION******/

int main(int argc, char** argv)
{
    target_list.InsertNode(square);

    DrawInit(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, DrawFunc);
    DrawSetKeyboardFunc(KeyCapture);
    DrawSetTimerFunc(TimedEvents, 100);

    DrawMainLoop();
    
    return 0;
}

static void DrawFunc()
{
    target_horiz.DrawInternal();
    target_vert.DrawInternal();
    target_list.DrawAll();
}

static int KeyCapture(unsigned char key, int x, int y)
{
    Point up_vector(0, -5);
    Point down_vector(0, 5);
    Point left_vector(-5, 0);
    Point right_vector(5, 0);
    Point reset(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);

    switch (key)
    {
    case 27: //ESC key Capture
        return -1;
    
    case 'w': //W key caputre
        target_horiz.Move(up_vector);
        target_vert.Move(up_vector);
        break;
    case 's': //S key caputre
        target_horiz.Move(down_vector);
        target_vert.Move(down_vector);
        break;
    case 'a': //A key caputre
        target_horiz.Move(left_vector);
        target_vert.Move(left_vector);
        break;
    case 'd': //D key caputre
        target_horiz.Move(right_vector);
        target_vert.Move(right_vector);
        break;
    case ' ': // Space key cpature
        target_list.CheckAll(target_horiz);
        break;
    default:
        break;
    }
    return 0;
}

static int TimedEvents()
{
    int vert_dir = (rand()%2 == 0) ? 1 : -1;
    int horiz_dir = (rand()%2 == 0) ? 1 : -1;

    Point vector(1, 1);//(horiz_dir*(rand()%5), vert_dir*(rand()%5));
    Point reset(0, 0); //(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);

    target_list.MoveAll();
    /*
    if (square.GetPos().GetX() > SCREEN_WIDTH ||
        square.GetPos().GetX() < 0 ||
        square.GetPos().GetY() > SCREEN_HEIGHT ||
        square.GetPos().GetY() > 0)
    {
        square.SetPos(reset);
    // }*/

    return 1;
}

bool operator!=(const Node& node1, const Node& node2)
{
    return node1!=node2;
}

