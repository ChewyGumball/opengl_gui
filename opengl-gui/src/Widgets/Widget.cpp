#include "Widgets/Widget.h"
#include "Borders/Border.h"

namespace OpenGLGUI
{
	short Widget::nextReceiptNumber(EventType type)
	{
		auto reclaimed = reclaimedReceiptNumbers.find(type);
		if (reclaimed == reclaimedReceiptNumbers.end())
		{
			if (highestReceiptNumber.count(type) == 0)
			{
				highestReceiptNumber[type] = 0;
			}
			return highestReceiptNumber[type]++;
		}
		else
		{
			short receipt = reclaimed->second;
			reclaimedReceiptNumbers.erase(reclaimed);
			return receipt;
		}
	}

	void Widget::eraseOldSubscriptions()
	{
		for (auto &subscription : subscriptionsToErase)
		{
			eventHandlers[subscription->eventType].erase(subscription);
		}
		subscriptionsToErase.clear();
	}

	Widget::Widget() : Widget(0,0,0,0)
	{ }

	Widget::Widget(int offsetX, int offsetY, int width, int height) : widgetPositionX(offsetX), widgetPositionY(offsetY), widgetWidth(width), widgetHeight(height) 
	{ }

	Widget::Widget(std::shared_ptr<Widget> parentWidget) : widgetPositionX(0), widgetPositionY(0), widgetWidth(parentWidget->width()), widgetHeight(parentWidget->height())
	{
		parent = parentWidget;
		parentWidget->setChild(shared_from_this());
	}

	Widget::~Widget()
	{
	}

	std::shared_ptr<EventSubscription> Widget::subscribe(EventType type, std::function<void(std::shared_ptr<EventSubscription>, Event&)> callback)
	{
		std::shared_ptr<EventSubscription> subscription = std::make_shared<EventSubscription>(this, type, nextReceiptNumber(type));
		eventHandlers[type][subscription] = callback;

		return subscription;
	}

	void Widget::unsubscribe(std::shared_ptr<OpenGLGUI::EventSubscription> subscription)
	{
		if (subscription->source == this)
		{
			subscriptionsToErase.insert(subscription);
		}
	}

	void Widget::unsubscribeAll()
	{
		eventHandlers.clear();
	}

	void Widget::notify(EventType type, Event& eventData)
	{
		eraseOldSubscriptions();

		bool keyEvent = type == EventType::KeyPressed || type == EventType::KeyReleased;
		if (child != nullptr)
		{
			child->notify(type, eventData);
		}

		if (!eventData.consumed() && visible)
		{
			if (enabled && (!keyEvent || focused) && eventHandlers.count(type) > 0)
			{
				for(auto &callback : eventHandlers[type])
				{
					callback.second(callback.first, eventData);
				}
			}
		}
	}
	/* Widget Relationship Functions */

	std::shared_ptr<Widget> Widget::removeChild()
	{
		std::shared_ptr<Widget> childWidget = child;
		removeParentChildRelationship(shared_from_this(), child);
		return child;
	}

	std::shared_ptr<Widget> Widget::removeParent()
	{
		std::shared_ptr<Widget> parentWidget = parent;
		removeParentChildRelationship(parent, shared_from_this());
		return parentWidget;
	}
	void Widget::removeParentChildRelationship(std::shared_ptr<Widget> parent, std::shared_ptr<Widget> child)
	{
		if (parent != nullptr)
		{
			parent->child = nullptr;
		}

		if (child != nullptr)
		{
			child->parent = nullptr;
		}
	}

	std::shared_ptr<Widget> Widget::parentWidget() const { return parent; }
	std::shared_ptr<Widget> Widget::Widget::childWidget() const { return child; }

	void Widget::setParent(std::shared_ptr<Widget> parentWidget) 
	{ 
		removeParentChildRelationship(parent, shared_from_this());
		parent = parentWidget; 
		parent->child = shared_from_this();
	}
	void Widget::setChild(std::shared_ptr<Widget> childWidget) 
	{
		removeParentChildRelationship(shared_from_this(), child);
		child = childWidget; 
		child->parent = shared_from_this();
	}


	/* Widget Position Functions */
	int Widget::X() const { return widgetPositionX; }
	int Widget::Y() const { return widgetPositionY; }
	int Widget::screenX() const { return parent != nullptr ? parent->screenX() + widgetPositionX : widgetPositionX;	}
	int Widget::screenY() const	{ return parent != nullptr ? parent->screenY() + widgetPositionY : widgetPositionY;	}
	Widget& Widget::setX(int x) { widgetPositionX = x; return *this; }
	Widget& Widget::setY(int y) { widgetPositionY = y; return *this; }
	Widget& Widget::setPosition(int x, int y) { setX(x); setY(y); return *this; }
	Widget& Widget::setXDelta(int deltaX) { widgetPositionX += deltaX; return *this; }
	Widget& Widget::setYDelta(int deltaY) { widgetPositionY += deltaY; return *this; }
	Widget& Widget::setPositionDelta(int deltaX, int deltaY) { setXDelta(deltaX); setYDelta(deltaY); return *this; }

	/* Widget Size Functions */
	int Widget::height() const { return widgetHeight; }
	int Widget::width() const { return widgetWidth; }
	int Widget::leftMargin() const { return widgetLeftMargin; }
	int Widget::rightMargin() const { return widgetRightMargin; }
	int Widget::topMargin() const { return widgetTopMargin; }
	int Widget::bottomMargin() const { return widgetBottomMargin; }

	Widget& Widget::setHeight(int height) { widgetHeight = height; return *this; }
	Widget& Widget::setWidth(int width) { widgetWidth = width; return *this; }
	Widget& Widget::setMargins(int topMargin, int bottomMargin, int leftMargin, int rightMargin)
	{
		setTopMargin(topMargin);
		setBottomMargin(bottomMargin);
		setLeftMargin(leftMargin);
		setRightMargin(rightMargin);
		return *this;
	}
	Widget& Widget::setLeftMargin(int leftMargin) { widgetLeftMargin = leftMargin; return *this; }
	Widget& Widget::setRightMargin(int rightMargin) { widgetRightMargin = rightMargin; return *this; }
	Widget& Widget::setTopMargin(int topMargin) { widgetTopMargin = topMargin; return *this; }
	Widget& Widget::setBottomMargin(int bottomMargin) { widgetBottomMargin = bottomMargin; return *this; }


	/* Widget Border Functions */
	std::shared_ptr<Border> Widget::border() const { return borderDefinition; }
	Widget& Widget::border(std::shared_ptr<Border> border) { borderDefinition = border; borderMesh = borderDefinition->createBorderMesh(corners());  return *this; }

	std::shared_ptr<Brush> Widget::background() const { return backgroundDefinition; }
	Widget& Widget::background(std::shared_ptr<Brush> background) { backgroundDefinition = background; return *this; }


	/* Widget Visibility Functions */
	//Non visible widgets do not get drawn and neither do their children
	bool Widget::isVisible() const { return visible; }
	Widget& Widget::setVisibility(bool visible) { this->visible = visible; return *this; }

	//Disabled widgets do not process their event handlers, but events still propagate to children
	bool Widget::isEnabled() const { return enabled; }
	Widget& Widget::setEnabled(bool enabled, bool recursive)
	{
		this->enabled = enabled;
		if (recursive && child != nullptr)
		{
			child->setEnabled(enabled, recursive);
		}
		return *this;
	}

	void Widget::processUpdate(long delta)
	{
		this->update(delta);
		if (child != nullptr)
		{
			child->processUpdate(delta);
		}
	}

	bool Widget::containsPoint(int x, int y)
	{
		int offsetX = screenX();
		int offsetY = screenY();
		return x >= offsetX && x <= offsetX + widgetWidth &&
			y >= offsetY && y <= offsetY + widgetHeight;
	}

	bool operator==(const Widget& lhs, const Widget& rhs)
	{
		return &lhs == &rhs;
	}
}
