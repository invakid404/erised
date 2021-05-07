//
// Created by inva on 5/7/21.
//

#ifndef ERISED_ICONS_H
#define ERISED_ICONS_H

#include <QMap>

static const QMap<QString, QString> icon_map = {{"Snow", "snow.png"},
                                                {"Sleet", "hail.png"},  // FIXME: Separate icon for Sleet
                                                {"Hail", "hail.png"},
                                                {"Thunderstorm", "thunderstorm.png"},
                                                {"Heavy Rain", "heavy_rain.png"},
                                                {"Light Rain", "light_rain.png"},
                                                {"Showers", "showers.png"},
                                                {"Heavy Cloud", "heavy_cloud.png"},
                                                {"Light Cloud", "light_cloud.png"},
                                                {"Clear", "clear.png"}};

#endif  // ERISED_ICONS_H
