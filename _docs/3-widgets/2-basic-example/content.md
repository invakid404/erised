---
Title: Minimal example
---

Let's start by considering a minimal example of a widget. For example, something that simply displays a button on screen, which does something on click.

First, there was nothing. Then, there was the widget class. We declare a class named `test`, which extends `QObject` and `erised::widget::widget_t`.

QObject is the heart of the [Qt Object Model](https://doc.qt.io/qt-5/object.html). By extending it, we basically allow our class to make use of Qt's powerful object communication mechanism, known as [signals and slots](https://doc.qt.io/qt-5/signalsandslots.html).

The [widget_t interface](https://github.com/invakid404/erised/blob/main/widget/interface.h) is the skeleton that all widgets need to follow. As of now, it simply consists of a single virtual method, named `instantiate_widget`. It is the so-called entrypoint of your widget. Every plugin needs to provide an implementation of that method, returning a single value - a [QWidget](https://doc.qt.io/qt-5/qwidget.html), containing all of the graphical elements.

Here, all we do is instantiate a new [QPushButton](https://doc.qt.io/qt-5/qpushbutton.html) with the text "Hello, world!", after which we connect a lambda function to the `released` signal of the button. Our slot consists of a single line of code - print a debug message. Epic, we have a fully working Erised widget!

![minimal-example-01](https://www.erised.tk/images/widget-minimal-example-01.png)
