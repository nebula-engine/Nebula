	Interface::Interface() {
}
	Interface::~Interface() {
}
/*
bool Interface::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_MOUSEMOVE:
        return onMouseMove( wParam, lParam );
    case WM_LBUTTONDOWN:
        return return onLButtonDown( wParam, lParam );
    case WM_LBUTTONUP:
		return onLButtonUp( wParam, lParam );
    case WM_RBUTTONDOWN:
		return onRButtonDown( wParam, lParam );
    case WM_RBUTTONUP:
		return onRButtonUp( wParam, lParam );
    case WM_KEYDOWN:
		return onKeyDown( wParam, lParam );
    case WM_KEYUP:
        return onKeyUp( wParam, lParam );
    default:
        return false;
    }
}

bool Interface::onLButtonDown( WPARAM wParam, LPARAM lParam )
{
    if (NbInterfaceObject object = getObject(x,y))
        return object->onLButtonDown( WPARAM wParam, LPARAM lParam );
    
    return false;
}

bool NbInterface::onLButtonUp( WPARAM wParam, LPARAM lParam)
{
    return false;
}

bool NbInterface::onRButtonDown( WPARAM wParam, LPARAM lParam)
{
    return false;
}

bool NbInterface::onRButtonUp( WPARAM wParam, LPARAM lParam)
{
    return false;
}

bool NbInterface::onKeyDown( WPARAM wParam, LPARAM lParam)
{
    return false;
}

bool NbInterface::onKeyUp( WPARAM wParam, LPARAM lParam)
{
    return false;
}

bool NbInterface::onGetFocus( WPARAM wParam, LPARAM lParam)
{
    return false;
}

bool NbInterface::onLooseFocus( WPARAM wParam, LPARAM lParam)
{
    return false;
}
*/