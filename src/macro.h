#ifndef MACRO_H
#define MACRO_H

// https://www.youtube.com/watch?v=p0uMisUnqlk

#define QSETTINGS_FITHOFUPRO() QSettings settings(QSettings::NativeFormat, QSettings::UserScope, "FiThoFuPro")
#define QSETTINGS_READ_PROPERTY(prop,def,to) {param_ ## prop = settings.value(#prop, def).to();}
#define QSETTINGS_SAVE_PROPERTY(prop) {settings.setValue(#prop, param_ ## prop);}
#define QICON_SYSTEM(icon) QIcon::fromTheme(icon, QIcon(":/images/" icon ".png"))

#ifdef QT_DEBUG
#include <QDebug>
#endif

#endif // MACRO_H
