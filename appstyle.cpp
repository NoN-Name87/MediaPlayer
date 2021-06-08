#include "appstyle.h"

QString AppStyle::getWindowStyle() {
    return "QWidget { "
            "background-color: #gray; "
            "border: 1px solid black; "
            "}";
}

QString AppStyle::getTableStyle() {
        return "QTableView { "
           "background-color: #292929; "
           "color: white; "
           "border: 1px solid #e2e2de;"
           "}"
           "QTableView::item:selected {"
           "background-color: #de8e37;"
           "}"
           "QTableView::item:hover {"
           "background-color: #de8e37;"
           "}"
           "QHeaderView::section:horizintal {"
           "background-color: white;"
           "border-style: none;"
           "color: black; "
           "border: 1px solid #e2e2de; "
           "padding: 6px; "
           "}";
}


QString AppStyle::getCloseBtnStyle() {
    return "QToolButton:hover {"
            "border: 1px solid red; "
            "}";
}
