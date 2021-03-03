//
// Created by inva on 3/3/21.
//

#ifndef ERISED_INTERFACE_H
#define ERISED_INTERFACE_H

#include <QObject>
#include <QString>

namespace erised::widget {
class widget_interface {
public:
    virtual ~widget_interface() = default;
    virtual QWidget* instantiate_widget() = 0;
};
}  // namespace erised::widget

using namespace erised::widget;

#define widget_interface_iid "tk.erised.Erised.WidgetInterface"
Q_DECLARE_INTERFACE(widget_interface, widget_interface_iid)

#endif  // ERISED_INTERFACE_H
