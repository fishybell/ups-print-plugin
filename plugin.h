/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Dantifer Dang <dantifer.dang@sun.com>.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Roland Mainz <roland.mainz@nrubsig.org>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/*
 * nathanb@actarg.com:
 * 
 * removed printplugin.c:
 * - printplugin.c contained only functionality no longer needed
 *
 * changed printplugin.h to plugin.h:
 * - I butchered the file to contain only definitions that the UPS print plugin
 *   needed, removing all of the Unix Print Plugin functionality.
 *
 * building/installing:
 * - Change the LPR_CALL definition to match your setup. The %s is where PRINTER
 *   will be placed within the call. The data will be piped in via cat.
 * - The PRINTER definition should point to a printer compliant with the UPS
 *   website (make sure your UPS website preferences are correct).
 * - Install the Gecko-SDK from
 *   http://ftp.mozilla.org/pub/mozilla.org/mozilla/nightly/latest-1.7/
 *   I use the gecko-sdk-i686-pc-linux-gnu.tar.gz file.
 * - Run rebuild.sh. It requires bash, zip, and gcc to run. If your system has
 *   different executable names edit the rebuild.sh to match your system.
 * - A shared object file (libupsprintplugin.so) and a zippie file (upsprint.xpi)
 *   will be created with rebuild.sh. Either use index.html to install the
 *   zippie file for a local installation, or copy the shared object file to
 *   /usr/lib/mozilla/plugins so that all users of the system will have the
 *   plugin available to them.
 *
 * todo:
 * - The plugin needs a better way to decide which printer to use.
 * - A "Reprint" button needs to be made in case the printer doesn't print.
 * - Right now there is no way to tell if the print was unsuccessful without
 *   checking the physical printer.
 */



#ifndef PLUGIN_H
#define PLUGIN_H 1

#define MIME_TYPES_HANDLED  "application/epl2:.epl2:Print Plugin for UPS/Linux"
#define PLUGIN_NAME         "Print Plugin for UPS/Linux"
#define PLUGIN_DESCRIPTION  "Linux clone of UPS print plugin. v1.0b."

/*
 * For now, these definitions must be changed on a per-installation basis.
 *
 * In the future it should read a config file, or create a window to select
 * the printer. A window would be difficult since the UPS site creates three
 * instances of the plugin if "Use my UPS thermal printer for ..." is selected
 * for the receipt and the label. Perhaps a combination would be appropriate.
 */

#define LPR_CALL "lpr -P%s -oraw"
#define PRINTER  "TP1"

/*
 * Define PLUGIN_TRACE to have the wrapper functions print
 * messages to stderr whenever they are called.
 *
 * Mozilla (et al) must have --enable-debug set at run-time
 * or be built without --disable-debug to show the messages.
 */

//#define PLUGIN_TRACE

#endif /* !UPSPRINTPLUGIN_H */

