#include <GL/glew.h>
#include <array>
#include "Widgets/Pane.h"
#include "Util.h"

#include "Brushes/Brush.h"
#include "Borders/Border.h"

namespace OpenGLGUI
{

	Pane::Pane() : Pane(0,0,0,0)
	{ }

	Pane::Pane(int offsetX, int offsetY, int width, int height) : Widget(offsetX, offsetY, width, height), backgroundRectangle(Rectangle(width,height))
	{
	}

	Pane::Pane(std::shared_ptr<Widget> parent) : Widget(parent), backgroundRectangle(Rectangle(width(), height()))
	{
	}
		
	void OpenGLGUI::Pane::draw(glm::vec2 origin)
	{	
		glm::vec2 widgetOrigin = origin + widgetPosition;

		backgroundRectangle.draw(widgetOrigin);
		borderInstance.draw(widgetOrigin);

		if (child != nullptr)
		{
			child->draw(widgetOrigin);
		}
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
				if (clickEvent.mouse.buttonWithMostRecentStateChange() == MouseButton::Left && containsPoint(clickEvent.mouse.position()))
				{
					std::shared_ptr<EventSubscription> dragEventSubscription = subscribe(EventType::MouseMove, [=](std::shared_ptr<EventSubscription> currentSubscription, Event &dragEvent) {
						setPositionDelta(dragEvent.mouse.deltaPosition());
						dragEvent.consume();
					});

					subscribe(EventType::MouseButtonReleased, [=](std::shared_ptr<EventSubscription> currentSubscription, Event &unclickEvent) {
						if (unclickEvent.mouse.buttonWithMostRecentStateChange() == MouseButton::Left)
						{
							unsubscribe(dragEventSubscription);
							unsubscribe(currentSubscription);
							unclickEvent.consume();
						}
					});
					clickEvent.consume();
				}
			});
		}
	}

	const std::shared_ptr<Brush> Pane::background() const
	{
		return backgroundDefinition;
	}

	Widget& Pane::background(std::shared_ptr<Brush> background)
	{
		backgroundRectangle.setBrush(background);
		return Widget::background(background);
	}
}
