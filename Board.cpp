#include "Board.hpp"

// בנאי המאתחל את המיקום המינימלי והמקסימלי שיש בלוח בערכים הדיפולטים
// unsigned int השורה והתור המינימלים מאותחלים לערכים המקסימלים האפשריים ל 
// 0 - unsigned int השורה והתור המקסימלים מאותחלים לערכים המינימלים האפשריים ל 
ariel::Board::Board() : _minRow(std::numeric_limits<unsigned int>::max()), _minColumn(std::numeric_limits<unsigned int>::max()), _maxRow(0), _maxColumn(0) {}

// מקבלת מיקום (שורה וטור), כיוון (אופקי או אנכי), ומחרוזת המייצגת מודעה, ומדביקה את המחרוזת על הלוח במקום המתאים
void ariel::Board::post(unsigned int row, unsigned int column, Direction dir, string message)
{
    // עדכון המיקום המינימלי
    _minRow = min(row, _minRow);
    _minColumn = min(column, _minColumn);

    if(dir == Direction::Horizontal)
    {
           // עדכון המיקום המקסימלי
        _maxColumn = max((unsigned int)(column + message.length()) , _maxColumn);
        _maxRow = max(row + 1, _maxRow);
        for(unsigned int i = 0; i < message.length(); i++) 
        { // עובר על העמודות במיקום הנתון בשורה הנתונה וכותב שם את המחרוזת
            _board[row][column + i] = message[i] != '\n' ? message[i] : '_'; // if message[i] is '\n' we will add '_' otherwise we will add message[i] 
        }
    }
    else
    {
        // עדכון המיקום המקסימלי
        _maxRow = max((unsigned int)(row + message.length()) ,_maxRow);
        _maxColumn = max(column + 1, _maxColumn);
        for(unsigned int i = 0; i < message.length(); i++) 
        { // עובר על השורות במיקום הנתון בעמודה הנתונה וכותב שם את המחרוזת
            _board[row + i][column] = message[i] != '\n' ? message[i] : '_'; // if message[i] is '\n' we will add '_' otherwise we will add message[i]
        } 
    }
}
// מקבלת מיקום (שורה וטור), כיוון (אופקי או אנכי), ומספר תוים, קוראת את מה שכתוב על הלוח במיקום הנתון ובאורך הנתון, ומחזירה מחרוזת
// האות הנמצאת בכל משבצת על הלוח היא האות האחרונה שהודבקה שם
string ariel::Board::read(unsigned int row, unsigned int column, Direction dir, unsigned int length)
{
     string message = "";
    if(dir == Direction::Horizontal)
    {
        for(unsigned int i = 0; i < length; i++)
        { // עובר על העמודות במיקום הנתון בשורה הנתונהוקורא משם את ההודעה
            if(_board.find(row) != _board.end() && _board[row].find(i + column) != _board[row].end())
            { // אם קיים אות במיקום בלוח נוסיף אותה למחרוזת
                message += _board[row][i + column];
            }
            else
            { // אחרת נוסיף למחרוזת תו שמייצג משבצת ריקה
                message += '_';
            }
        }
    }
    else
    {
        for(unsigned int i = 0; i < length; i++)
        { // עובר על העמודות במיקום הנתון בשורה הנתונה וקורא משם את ההודעה
            if(_board.find(row + i) != _board.end() && _board[row + i].find(column) != _board[row + i].end()) 
            { // אם קיים אות במיקום בלוח נוסיף אותה למחרוזת
                message += _board[row + i][column];
            }            
            else
            { // אחרת נוסיף למחרוזת תו שמייצג משבצת ריקה
                message += '_';
            }
        } 
    }
    return message;
}

// מציגה את לוח-המודעות הנוכחי בצורה נוחה לקריאה
void ariel::Board::show()
{
    for(unsigned int i = _minRow ; i < _maxRow; i++)
    { // עובר על השורות מהשורה המינימלית לשורה המקסימלית ומדפיס אותן
        cout.fill('0'); // הוספת ריווח של 0 למספר השורה שמודפס כדי שההדפסה תיהיה מסודרת יפה
        cout.width(5);
        // קורא ומדפיס את השורה הנוכחית מהעמודה המינימלית לעמודה המקסימלית בצורה אופקית
        cout << i << ": " << read(i, _minColumn, Direction::Horizontal, _maxColumn - _minColumn) << endl;
    }
}    
