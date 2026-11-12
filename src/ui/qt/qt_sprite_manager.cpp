#include "qt_sprite_manager.hpp"

#include <QFileInfo>
#include <QPainter>
#include <vector>

using biv::QtSpriteManager;

QtSpriteManager& QtSpriteManager::instance() {
	static QtSpriteManager mgr;
	return mgr;
}

QPixmap QtSpriteManager::create_fallback_pixmap(const std::string& name) const {
	QPixmap pm(16, 16);
	pm.fill(Qt::transparent);
	QPainter p(&pm);

	QColor col = Qt::magenta;
	if (name == "mario") col = Qt::red;
	else if (name == "enemy" || name == "jumping_enemy" || name == "flying_enemy") col = QColor(184, 72, 0);
	else if (name == "box") col = QColor(200, 76, 12);
	else if (name == "full_box") col = QColor(252, 160, 16);
	else if (name == "empty_box") col = QColor(100, 60, 30);
	else if (name == "ground_top") col = QColor(0, 168, 0);
	else if (name == "ground_sub") col = QColor(104, 32, 0);
	else if (name == "money") col = QColor(252, 216, 0);
	else if (name == "moving_platform") col = QColor(248, 120, 32);
	else if (name == "finish") col = Qt::darkGreen;

	p.fillRect(0, 0, 16, 16, col);
	return pm;
}

const QPixmap& QtSpriteManager::get_sprite(const std::string& name) {
	auto it = sprites.find(name);
	if (it != sprites.end()) {
		return it->second;
	}

	std::vector<QString> candidates = {
		QString(":/sprites/resources/sprites/%1.png").arg(QString::fromStdString(name)),
		QString("resources/sprites/%1.png").arg(QString::fromStdString(name)),
		QString("../src/ui/qt/resources/sprites/%1.png").arg(QString::fromStdString(name)),
		QString("src/ui/qt/resources/sprites/%1.png").arg(QString::fromStdString(name))
	};

	QPixmap pm;
	for (const auto& path : candidates) {
		if (pm.load(path)) {
			break;
		}
	}

	if (pm.isNull()) {
		pm = create_fallback_pixmap(name);
	}

	sprites[name] = pm;
	return sprites[name];
}
