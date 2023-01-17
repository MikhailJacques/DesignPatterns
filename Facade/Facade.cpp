// Facade Design Pattern
// 
// Facade is a structural design pattern that provides a simplified (but limited) 
// interface to a complex system of classes, library or framework.

// A facade is a class that provides a simple interface to a complex subsystem which contains lots of moving parts.
// A facade might provide limited functionality in comparison to working with the subsystem directly.
// However, it includes only those features that clients really care about.
// Having a facade is handy when you need to integrate your app with a sophisticated library that has dozens of features, 
// but you just need a tiny bit of its functionality.

// https://refactoring.guru/design-patterns/facade

#include <iostream>
#include <string>

// The Subsystem can accept requests either from the facade or client directly.
// In any case, to the Subsystem, the Facade is yet another client, and it's not a part of the Subsystem.
class Subsystem1 
{
    public:
        std::string Operation1() const 
        {
            return "Subsystem1: Ready!\n";
        }

        // ...
        std::string OperationN() const 
        {
            return "Subsystem1: Go!\n";
        }
 };

// Some facades can work with multiple subsystems at the same time.
class Subsystem2 
{
    public:
        std::string Operation1() const 
        {
            return "Subsystem2: Get ready!\n";
        }

        // ...
        std::string OperationZ() const 
        {
            return "Subsystem2: Fire!\n";
        }
};

// The Facade class provides a simple interface to the complex logic of one or several subsystems. 
// The Facade delegates the client requests to the appropriate objects within the subsystem. 
// The Facade is also responsible for managing their lifecycle. 
// All of this shields the client from the undesired complexity of the subsystem.
class Facade 
{
    protected:
        Subsystem1* subsystem1_;
        Subsystem2* subsystem2_;

        // Depending on your application's needs, you can provide the Facade with
        // existing subsystem objects or force the Facade to create them on its own.
    public:

        // In this case we will delegate the memory ownership to Facade Class
        Facade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr) 
        {
            this->subsystem1_ = (subsystem1) ? subsystem1 : new Subsystem1;
            this->subsystem2_ = (subsystem2) ? subsystem2 : new Subsystem2;
        }

        ~Facade() 
        {
            delete subsystem1_;
            delete subsystem2_;
        }

        // The Facade's methods are convenient shortcuts to the sophisticated functionality of the subsystems. 
        // However, clients get only to a fraction of a subsystem's capabilities.
        std::string Operation() 
        {
            std::string result = "Facade initializes subsystems:\n";
            result += this->subsystem1_->Operation1();
            result += this->subsystem2_->Operation1();
            result += "Facade orders subsystems to perform the action:\n";
            result += this->subsystem1_->OperationN();
            result += this->subsystem2_->OperationZ();
            return result;
        }
};

// The client code works with complex subsystems through a simple interface provided by the Facade. 
// When a facade manages the lifecycle of the subsystem, the client might not even know about the existence of the subsystem. 
// This approach lets you keep the complexity under control.
void ClientCode(Facade* facade) 
{
    // ...
    std::cout << facade->Operation();
    // ...
}

// The client code may have some of the subsystem's objects already created. 
// In this case, it might be worthwhile to initialize the Facade with these objects
// instead of letting the Facade create new instances.
int main() 
{
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;

    Facade* facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    std::cout << std::endl;

    Facade* facade2 = new Facade(nullptr, nullptr);
    ClientCode(facade2);

    delete facade;

    return 0;
}