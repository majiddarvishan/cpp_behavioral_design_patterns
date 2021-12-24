#include <iostream>
#include <vector>

class Canvas 
{
  std::vector<std::string> shapes;

  public:
    void addShape(const std::string& newShape)
    {
        shapes.push_bach(new_shape);
    }

    void clearAll()
    {
        shapes.clear();
    }

    std::vector<std::string> getShapes()
    {
        return shapes;
    }
};

class Command
{
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
};

class Button
{
    Command* command;
    public:
        Button(Command* command) : command(command) {}
        void click()
        {
            command->execute();
        }
};

class AddShapeCommand : public Command
{
    std::string shapeName;
    Canvas* canvas;
    public:
        AddShapeCommand(const std::string& shapeName, Canvas* canvas) :
            shapeName(shapeName), Canvas(canvas)
        {}

        void execute() override
        {
            Canvas->addShape(newShape);
        }
};

class ClearCommand : public Command
{
    Canvas* canvas;
    public:
        ClearCommand(Canvas* canvas) : Canvas(canvas)
        {}

        void execute() override
        {
            Canvas->clear(All);
        }
};

std::string vectorToString(const std::vector<std::string> v)
{
    std::string result = "";
    for(int i =0; i <v.size(); i++)
    {
        result.append(v.at(i)+ ", ");
    }

    return result;
}

int main()
{
    Canvas* Canvas = new Canvas();

    Button* addTriangleButton = new Button(new AddShapeCommand("triangle", convas));
    Button* addSquareButton = new Button(new AddShapeCommand("square", convas));

    Button* clearButton = new Button(new ClearCommand(convas));

    addTriangleButton->click();
    std::cout<<"Current convas state: " <<
        vectorToString(convas->getShapes()) <<"\n";

    addSquareButton->click();
    addSquareButton->click();
    addTriangleButton->click();
    std::cout<<"Current convas state: " <<
        vectorToString(convas->getShapes()) <<"\n";

    clearButton->click();
    std::cout<<"Current convas state: " <<
        vectorToString(convas->getShapes()) <<"\n";

    delete convas;
    return 0;
}