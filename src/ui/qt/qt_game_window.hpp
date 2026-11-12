#pragma once

#include <QWidget>
#include <vector>

namespace biv {
	class QtUIObject;
	class QtKeyboard;
	class Mario;

	class QtGameWindow : public QWidget {
		Q_OBJECT

		private:
			QtKeyboard* keyboard = nullptr;
			std::vector<QtUIObject*> objs;
			Mario* mario = nullptr;
			int map_height = 30;
			int map_width = 200;

		public:
			QtGameWindow(QtKeyboard* keyboard, int map_height, int map_width, QWidget* parent = nullptr);

			void update_objs(const std::vector<QtUIObject*>& new_objs, Mario* new_mario);

		protected:
			void paintEvent(QPaintEvent* event) override;
			void keyPressEvent(QKeyEvent* event) override;
			void keyReleaseEvent(QKeyEvent* event) override;
			void closeEvent(QCloseEvent* event) override;
	};
}
