#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "Events/Event.h"
#include "Events/EventSubscription.h"


namespace OpenGLGUI
{
	class Border;

	class Widget
	{
	private:
		std::unordered_multimap<EventType, short> reclaimedReceiptNumbers;
		std::unordered_map<EventType, short> highestReceiptNumber;
		std::unordered_map<EventType, std::unordered_map<EventSubscription, std::function<void(Event&)>>> eventHandlers;

		short nextReceiptNumber(EventType type);

		Widget *parent;
		Widget *child;

		int widgetPositionX;
		int widgetPositionY;

		int widgetHeight;
		int widgetWidth;
		int widgetLeftMargin;
		int widgetRightMargin;
		int widgetTopMargin;
		int widgetBottomMargin;

		Border *borderDefinition;

		bool visible;
		bool enabled;
		bool focused;

		void removeParentChildRelationship(Widget *parent, Widget *child);
		void processUpdate(long delta);

	public:
		Widget();
		Widget(Widget *parentWidget);
		virtual ~Widget();

		/* Event Handling Functions */
		EventSubscription subscribe(EventType type, std::function<void(Event&)> callback);
		void unsubscribe(EventSubscription& subscription);
		void unsubscribeAll();

		virtual bool containsPoint(int x, int y);

		virtual void notify(EventType type, Event& eventData);

		/* Widget Relationship Functions */
		void setChild(Widget *childWidget);
		Widget* removeChild();
		Widget* childWidget() const;

		void setParent(Widget *parentWidget);
		Widget* removeParent();
		Widget* parentWidget() const;


		/* Widget Position Functions */
		int X() const;
		int Y() const;
		Widget& setX(int x);
		Widget& setY(int y);
		Widget& setPosition(int x, int y);
		Widget& setXDelta(int deltaX);
		Widget& setYDelta(int deltaY);
		Widget& setPositionDelta(int deltaX, int deltaY);


		/* Widget Size Functions */
		int height() const;
		int width() const;
		int leftMargin() const;
		int rightMargin() const;
		int topMargin() const;
		int bottomMargin() const;

		Widget& setHeight(int height);
		Widget& setWidth(int width);
		Widget& setMargins(int topMargin, int bottomMargin, int leftMargin, int rightMargin);
		Widget& setLeftMargin(int leftMargin);
		Widget& setRightMargin(int leftMargin);
		Widget& setTopMargin(int leftMargin);
		Widget& setBottomMargin(int leftMargin);


		/* Widget Border Functions */
		Border* border() const;
		Widget& setBorder(Border *border);


		/* Widget Visibility Functions */
		//Non visible widgets do not get drawn
		bool isVisible() const;
		Widget& setVisibility(bool visible);

		//Disabled widgets do not process their event handlers, but events still propagate to children
		bool isEnabled() const;
		Widget& setEnabled(bool enabled, bool recursive = true);

		virtual void update(long delta);
	};

	bool operator==(const Widget& lhs, const Widget& rhs);
}

namespace std {
	template <>
	struct hash<OpenGLGUI::Widget>
	{
		size_t operator()(const OpenGLGUI::Widget &type) const
		{
			return reinterpret_cast<size_t>(&type);
		}
	};
}
