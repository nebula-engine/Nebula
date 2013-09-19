#include <RendererWindow.h>
#include <RendererMemoryMacros.h>
#include <SamplePlatform.h>
#include <stdio.h>

using namespace SampleRenderer;

		RendererWindow::RendererWindow(void)
{
	m_platform = SampleFramework::createPlatform(this);
	m_isOpen = false;
}
		RendererWindow::~RendererWindow(void)
{
	DELETESINGLE(m_platform);
}
bool	RendererWindow::hasFocus() const
{
	return m_platform->hasFocus();
}
void	RendererWindow::setFocus(bool b) 
{
	m_platform->setFocus(b);
}
bool	RendererWindow::open(PxU32 width, PxU32 height, const char *title, bool fullscreen)
{
	bool ok = false;
	RENDERER_ASSERT(width && height, "Attempting to open a window with invalid width and/or height.");
	if(width && height)
	{
		ok = m_platform->openWindow(width, height, title, fullscreen);
#if !defined(RENDERER_WINDOWS)
		onOpen(); // overwritten by NxApplication
		m_isOpen = true;
#endif
	}
	return ok;
}
void	RendererWindow::close(void)
{
	m_platform->closeWindow();
#if !defined(RENDERER_WINDOWS)
	if(isOpen())
	{
		m_isOpen = false;
		onClose();
	}
#endif
}
bool	RendererWindow::isOpen(void) const
{
	bool open = m_platform->isOpen();
#if !defined(RENDERER_WINDOWS)
	open = m_isOpen;
#endif
	return open;
}
void	RendererWindow::update(void)
{
	// update the window's state, handle messages, etc.

	// platform inputs
	m_platform->update();
#if defined(RENDERER_MACOSX)
	if (isOpen())
	{
		if (!m_platform->updateWindow())
		{
			close();
		}
	}
    return;
#endif

#if defined(RENDERER_ANDROID)
	if (!m_platform->isOpen())
		return;
#endif

	if(isOpen())
	{
		onDraw();
	}
}
void	RendererWindow::setSize(PxU32 width, PxU32 height)
{
	m_platform->setWindowSize(width, height);
}
void	RendererWindow::getTitle(char *title, PxU32 maxLength) const
{
	// get the window's title...
	m_platform->getTitle(title, maxLength);
}
void	RendererWindow::setTitle(const char *title)
{
	// set the window's title...
	m_platform->setTitle(title);
}


