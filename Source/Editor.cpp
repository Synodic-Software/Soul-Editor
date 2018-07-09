#include "Editor.h"

Editor::Editor(SoulParameters params) :
	SoulApplication(params) {

}

int main(int, char*[])
{
	//app params
	SoulParameters appParams;
	Editor app(appParams);

	//create the window
	WindowParameters windowParams;
	windowParams.type = WindowType::WINDOWED;
	windowParams.title = "Main";
	windowParams.monitor = 0;
	windowParams.pixelPosX = 0;
	windowParams.pixelPosY = 0;
	windowParams.pixelWidth = 512;
	windowParams.pixelHeight = 512;

	Window& window = app.CreateWindow(windowParams);

	//Window* mainWindow = CreateWindow(singleWindowType, "main", monitor, xPos, yPos, xSize, ySize);

	//SetWindowLayout(mainWindow, new SingleLayout(new RenderWidget()));


	app.Run();

}