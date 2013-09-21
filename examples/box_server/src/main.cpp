#include <Nebula/App.h>

int main()
{
    Nebula::App::shared_ptr app(new Nebula::App());
    
    app->Init(app);
    
    app->network->Create_Server(20248);
    
    app->Main_Loop();
    
}


