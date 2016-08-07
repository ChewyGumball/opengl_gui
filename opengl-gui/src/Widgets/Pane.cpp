#include <GL/glew.h>
#include <array>
#include "Widgets/Pane.h"
#include "Util.h"

#include "Brushes/Brush.h"
#include "Borders/Border.h"

namespace {
	using OpenGLGUI::Util::Mesh;

	bool initialized = false;
	Mesh *paneMesh;

	void initializeGLData() {
		paneMesh = new Mesh({
			0.0, 0.0,
			1.0, 0.0,
			0.0, 1.0,
			1.0, 1.0
		});
		initialized = true;
	}
}


namespace OpenGLGUI
{
	std::vector<std::pair<float, float>>& Pane::corners()
	{
		return cornerList;
	}
	Pane::Pane()
	{
		widgetPositionX = 100;
		widgetPositionY = 100;
		widgetWidth = 150;
		widgetHeight = 100; 
		cornerList = {
			std::make_pair(0, 0),
				std::make_pair(widgetWidth, 0),
				std::make_pair(widgetWidth, widgetHeight),
				std::make_pair(0, widgetHeight)
		};
	}

	Pane::~Pane()
	{
	}
	
	void OpenGLGUI::Pane::draw()
	{		
		if (!initialized)
		{
			initializeGLData();
		}
		backgroundDefinition->activate();
		backgroundDefinition->setUniform2f("offset", widgetPositionX, widgetPositionY);
		backgroundDefinition->setUniform2f("dimension", widgetWidth, widgetHeight);
		backgroundDefinition->setUniform2f("screenSize", 640, 480);
		paneMesh->draw();
		backgroundDefinition->deactivate();

		borderDefinition->brush().activate();
		borderDefinition->brush().setUniform2f("offset", widgetPositionX, widgetPositionY);
		borderDefinition->brush().setUniform2f("dimension", 1, 1);
		borderDefinition->brush().setUniform2f("screenSize", 640, 480);
		borderMesh->draw();
		borderDefinition->brush().deactivate();
	}

	void Pane::setDraggable(bool draggable)
	{
		if (dragSubscription)
		{
			unsubscribe(dragSubscription);
		}

		if (draggable)
		{
			dragSubscription = subscribe(EventType::MouseButtonPressed, [&](std::shared_ptr<EventSubscription> pressSubscription, Event &clickEvent) {
				if (clickEvent.mouse.buttonWithMostRecentStateChange() == MouseButton::Left)
				{
					std::shared_ptr<EventSubscription> dragEventSubscription = subscribe(EventType::MouseMove, [=](std::shared_ptr<EventSubscription> currentSubscription, Event &dragEvent) {
						setXDelta(dragEvent.mouse.deltaX());
						setYDelta(dragEvent.mouse.deltaY());
					});

					subscribe(EventType::MouseButtonReleased, [=](std::shared_ptr<EventSubscription> currentSubscription, Event &unclickEvent) {
						if (unclickEvent.mouse.buttonWithMostRecentStateChange() == MouseButton::Left)
						{
							unsubscribe(dragEventSubscription);
							unsubscribe(currentSubscription);
						}
					});
				}
			});
		}
	}
}
