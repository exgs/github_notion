// https://copynull.tistory.com/128

#include <iostream>
using namespace std;

class State
{
public:
    virtual void handle() = 0;
};
 
//------------------------------------------------------------------
// ConcreteState1 클래스
class ConcreteState1 : public State
{
public:
    void handle() override { cout << "ConcreteState1" << endl; }
};
 
//------------------------------------------------------------------
// ConcreteState2 클래스
class ConcreteState2 : public State
{
public:
    void handle() override { cout << "ConcreteState2" << endl; }
};
 
//------------------------------------------------------------------
// Context 클래스
class Context
{
public:
    Context(State* state) : pState(state) {}
    ~Context() { if (pState) delete pState; }
 
public:
    void SetState(State* state)
	{
		if (pState)
			delete pState;
		pState = state;
	}
	void request()
	{
		pState->handle();
	}
 
private:
	State* pState;
};
 
//------------------------------------------------------------------
// Main
int main(int argc, char* argv[])
{
    Context* pContext = new Context(new ConcreteState1());
    pContext->request();
 
    pContext->SetState(new ConcreteState2());
    pContext->request();
 
    delete pContext;
    return 0;
}