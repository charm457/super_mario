#pragma once

#include <QPixmap>
#include <string>
#include <unordered_map>

namespace biv {
	class QtSpriteManager {
		private:
			std::unordered_map<std::string, QPixmap> sprites;
			QtSpriteManager() = default;

			QPixmap create_fallback_pixmap(const std::string& name) const;

		public:
			static QtSpriteManager& instance();

			const QPixmap& get_sprite(const std::string& name);
	};
}
