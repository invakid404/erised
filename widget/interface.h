//
// Created by inva on 3/3/21.
//

#ifndef ERISED_INTERFACE_H
#define ERISED_INTERFACE_H

#include <QObject>
#include <QString>

namespace erised::widget {
class widget_t {
public:
    virtual ~widget_t() = default;
    virtual QWidget* instantiate_widget() = 0;
};
}  // namespace erised::widget

using namespace erised::widget;

#define widget_interface_iid "tk.erised.Erised.WidgetInterface"
Q_DECLARE_INTERFACE(widget_t, widget_interface_iid)

#endif  // ERISED_INTERFACE_H
