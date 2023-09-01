// CommandPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

class Canvas {
    std::vector<std::string> shapes;
public:
    void addShape(const std::string& newShape) {
        shapes.push_back(newShape);
    };
    void clearAll() {
        shapes.clear();
    };
    std::vector<std::string> getShapes() { return shapes; };
};

class Command {
public:
    virtual ~Command() {};
    virtual void execute() = 0;
};

class AddShapeCommand : public Command {
    std::string shapeName;
    Canvas* canvas;
public:
    AddShapeCommand(std::string shapeName, Canvas* canvas) : shapeName(shapeName), canvas(canvas) {};
    void execute() override
    {
        canvas->addShape(shapeName);
    }
};

class ClearCommand : public Command {
    Canvas* canvas;
public:
    ClearCommand(Canvas* canvas) : canvas(canvas) {};
    void execute() override
    {
        canvas->clearAll();
    }
};

class Button {
    Command* command;
public:
    Button(Command* command) : command(command) {};
    virtual void click()
    {
        command->execute();
    }
};

std::string vectorToString(std::vector<std::string> v) {
    std::string result = "";
    for (int i = 0; i < v.size(); i++) {
        result.append(v.at(i) + ", ");
    }
    return result;
}

int main()
{
    Canvas* canvas = new Canvas;

    Button* addTriangleButton = new Button(new AddShapeCommand("triangle", canvas));
    Button* addSquareButton = new Button(new AddShapeCommand("square", canvas));
    Button* clearButton = new Button(new ClearCommand(canvas));

    addTriangleButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    addSquareButton->click();
    addSquareButton->click();
    addTriangleButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    clearButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";

    delete canvas;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
