#pragma once

#include <vector>
#include <map>
#include<iostream>

#include "Direction.hpp"

using namespace std;
using ariel::Direction;


namespace ariel {

	// מחלקה שמייצגת את לוח המודעות
	class Board {
      private:
            // מילון שממפה שורה למילון נוסף שממפה עמודה לתו, זהו התו במיקום של השורה ושל העמודה
            // הוא התו בשורה ה 1 ובעמודה ה 4 _board[1][4] לדוגמא
            map<unsigned int, map<unsigned int, char>> _board;
            // מייצגים את השורה והעמודה, המינימלית והמקסימלית כדי שההדפסה של כל הלוח תיהיה בטווח הזה שיכיל את כל התוכן שבלוח המודעות
            unsigned int _minRow;
            unsigned int _minColumn;
            unsigned int _maxRow;
            unsigned int _maxColumn;
        public:
            Board();
            void post(unsigned int row, unsigned int column, Direction dir, string message);
            string read(unsigned int row, unsigned int column, Direction dir, unsigned int length);
            void show();           
    };
}
