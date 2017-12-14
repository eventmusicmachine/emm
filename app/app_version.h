/**************************************************************************
 * Event Music Machine
 * Copyright (C) 2014-2017 Christoph Kraemer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

#ifndef APP_VERSION_H
#define APP_VERSION_H

namespace Core {
namespace Constants {

    #define STRINGIFY_INTERNAL(x) #x
    #define STRINGIFY(x) STRINGIFY_INTERNAL(x)

    const char EMM_DISPLAY_NAME[] = "Event Music Machine";
    const char EMM_ID[] = "emm";

    const char * const EMM_VERSION_LONG = EMM_VERSION;

    // changes the path where the settings are saved to
    #ifdef EMM_SETTINGSVARIANT
    const char * const EMM_SETTINGSVARIANT_STR = STRINGIFY(EMM_SETTINGSVARIANT);
    #else
    const char * const EMM_SETTINGSVARIANT_STR = "EMM";
    #endif

    const char * const RELATIVE_PLUGIN_PATH = RELATIVE_PLUGIN_PATH_STR;

    #undef STRINGIFY
    #undef STRINGIFY_INTERNAL
}
}

#endif // APP_VERSION_H
