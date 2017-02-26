set(SOURCES AudioDecoder.cpp
            AudioEncoder.cpp
            ImageDecoder.cpp
            Screensaver.cpp
            VFSEntry.cpp)

set(HEADERS AudioDecoder.h
            AudioEncoder.h
            ImageDecoder.h
            Screensaver.h
            VFSEntry.h)

core_add_library(addonInterface_kodi_addon_instance)
