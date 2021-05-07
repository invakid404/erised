#! Example widget class
```cpp
class test : public QObject, erised::widget::widget_t {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tk.erised.Erised.Test" FILE "test.json")
    Q_INTERFACES(widget_t)
public:
    QWidget* instantiate_widget() override {
        auto* button = new QPushButton("Hello, world!");
        connect(button, &QPushButton::released,
                [&]() { qDebug() << "Hello from the widget!"; });

        return button;
    }
};
```
*This fragment is adapted from the [Erised GitHub repository](https://github.com/invakid404/erised/tree/main/test-widget)*.

![minimal-example-02](https://www.erised.tk/images/widget-minimal-example-02.png)
