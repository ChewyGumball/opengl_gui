
#include "Widgets/Widget.h"

namespace OpenGLGUI
{
	short Widget::nextReceiptNumber(EventType type)
	{
		auto reclaimed = reclaimedReceiptNumbers.find(type);
		if (reclaimed == reclaimedReceiptNumbers.end())
		{
			return highestReceiptNumber[type]++;
		}
		else
		{
			short receipt = reclaimed->second;
			reclaimedReceiptNumbers.erase(reclaimed);
			return receipt;
		}
	}

	Widget::Widget()
	{
	}

	Widget::Widget(Widget * parentWidget)
	{
		parent = parentWidget;
		parentWidget->setChild(this);
	}

	Widget::~Widget()
	{
	}

	EventSubscription Widget::subscribe(EventType type, std::function<void(Event&)> callback)
	{
		EventSubscription subscription(*this, type, nextReceiptNumber(type));
		eventHandlers[type][subscription] = callback;

		return subscription;
	}

	void Widget::unsubscribe(EventSubscription& subscription)
	{
		if (&subscription.source == this)
		{
			eventHandlers[subscription.eventType].erase(subscription);
		}
	}

	void Widget::unsubscribeAll()
	{
		eventHandlers.clear();
	}

	void Widget::notify(EventType type, Event& eventData)
	{
		bool keyEvent = type == EventType::KeyPressed || type == EventType::KeyReleased;
		if (keyEvent || this->containsPoint(eventData.mouse.x(), eventData.mouse.y()))
		{
			if (child != nullptr)
			{
				child->notify(type, eventData);
			}

			if (!eventData.consumed() && visible)
			{
				eventData.consume();
				if (enabled && (!keyEvent || focused) && eventHandlers.count(type) > 0)
				{
					for (auto &callback : eventHandlers[type])
					{
						callback.second(eventData);
					}
				}
			}
		}
	}
	/* Widget Relationship Functions */

	Widget* Widget::removeChild()
	{
		Widget *childWidget = child;
		removeParentChildRelationship(this, child);
		return child;
	}

	Widget* Widget::removeParent()
	{
		Widget *parentWidget = parent;
		removeParentChildRelationship(parent, this);
		return parentWidget;
	}
	void Widget::removeParentChildRelationship(Widget *parent, Widget *child)
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

	Widget* Widget::parentWidget() const { return parent; }
	Widget* Widget::Widget::childWidget() const { return child; }

	void Widget::setParent(Widget *parentWidget) { parent = parentWidget; }
	void Widget::setChild(Widget *childWidget) { child = childWidget; }


	/* Widget Position Functions */
	int Widget::X() const { return widgetPositionX; }
	int Widget::Y() const { return widgetPositionY; }
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
	Border* Widget::border() const { return borderDefinition; }
	Widget& Widget::setBorder(Border *border) { borderDefinition = border; return *this; }


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

	void Widget::update(long delta) {}

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
		return x >= widgetPositionX && x <= widgetPositionX + widgetWidth &&
			y >= widgetPositionY && y <= widgetPositionY + widgetHeight;
	}

	bool operator==(const Widget& lhs, const Widget& rhs)
	{
		return &lhs == &rhs;
	}
}
