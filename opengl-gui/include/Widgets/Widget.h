#pragma once
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

#include "Drawables/Drawable.h"
#include "Events/Event.h"
#include "Events/EventSubscription.h"
#include "Util.h"
#include "Borders/BorderInstance.h"


namespace OpenGLGUI
{
	class Widget : public Drawable, private std::enable_shared_from_this<Widget>
	{
	private:
		std::unordered_set<std::shared_ptr<EventSubscription>> subscriptionsToErase;
		std::unordered_multimap<EventType, short> reclaimedReceiptNumbers;
		std::unordered_map<EventType, short> highestReceiptNumber;
		std::unordered_map<EventType, std::unordered_map<std::shared_ptr<EventSubscription>, std::function<void(std::shared_ptr<EventSubscription>,Event&)>>> eventHandlers;

		short nextReceiptNumber(EventType type);
		void eraseOldSubscriptions();

	protected:
		std::shared_ptr<Widget> parent;
		std::shared_ptr<Widget> child;

		glm::vec2 widgetPosition;

		int widgetHeight;
		int widgetWidth;
		int widgetLeftMargin;
		int widgetRightMargin;
		int widgetTopMargin;
		int widgetBottomMargin;

		BorderInstance borderInstance;

		std::shared_ptr<Border> borderDefinition;

		std::shared_ptr<Brush> backgroundDefinition;

		bool visible;
		bool enabled;
		bool focused;

		void removeParentChildRelationship(std::shared_ptr<Widget> parent, std::shared_ptr<Widget> child);
		void processUpdate(long delta);

		std::vector<glm::vec2> cornerList;
		virtual std::vector<glm::vec2> makeCorners();
		virtual std::vector<glm::vec2>& corners();
		
	public:
		Widget();
		Widget(int offsetX, int offsetY, int width, int height);
		Widget(std::shared_ptr<Widget> parentWidget);
		virtual ~Widget();

		/* Event Handling Functions */
		std::shared_ptr<EventSubscription> subscribe(EventType type, std::function<void(std::shared_ptr<EventSubscription>, Event&)> callback);
		void unsubscribe(std::shared_ptr<EventSubscription> subscription);
		void unsubscribeAll();

		virtual bool containsPoint(glm::vec2 point);

		virtual void notify(EventType type, Event& eventData);

		/* Widget Relationship Functions */
		void setChild(std::shared_ptr<Widget> childWidget);
		std::shared_ptr<Widget> removeChild();
		std::shared_ptr<Widget> childWidget() const;

		void setParent(std::shared_ptr<Widget> parentWidget);
		std::shared_ptr<Widget> removeParent();
		std::shared_ptr<Widget> parentWidget() const;


		/* Widget Position Functions */
		glm::vec2 position() const;
		glm::vec2 screenPosition() const;
		Widget& setPosition(glm::vec2 position);
		Widget& setPositionDelta(glm::vec2 delta);


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
		virtual std::shared_ptr<Border> border() const;
		virtual Widget& border(std::shared_ptr<Border> border);

		/* Widget Background Functions */
		virtual const std::shared_ptr<Brush> background() const;
		virtual Widget& background(std::shared_ptr<Brush> background);


		/* Widget Visibility Functions */
		//Non visible widgets do not get drawn
		bool isVisible() const;
		Widget& setVisibility(bool visible);

		//Disabled widgets do not process their event handlers, but events still propagate to children
		bool isEnabled() const;
		Widget& setEnabled(bool enabled, bool recursive = true);

		virtual void update(long delta) {};
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
