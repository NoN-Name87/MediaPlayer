#include "appstyle.h"

QString AppStyle::getWindowStyle() {
    return "QWidget { "
            "background-color: #gray; "
            "border: 1px solid black; "
            "}";
}

QString AppStyle::getTableStyle() {
    return "QTableView { "
           "background-color: white; "
           "color: black; "
           "border: 1px solid #e2e2de;"
           "}"
           "QTableView::item:selected {"
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
