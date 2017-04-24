/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
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
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Stephen Mak <smak@sun.com>
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
 * npshell.c
 *
 * Netscape Client Plugin API
 * - Function that need to be implemented by plugin developers
 *
 * This file defines a "shell" plugin that plugin developers can use
 * as the basis for a real plugin.  This shell just provides empty
 * implementations of all functions that the plugin can implement
 * that will be called by Netscape (the NPP_xxx methods defined in
 * npapi.h).
 *
 * dp Suresh <dp@netscape.com>
 * updated 5/1998 <pollmann@netscape.com>
 * updated 9/2000 <smak@sun.com>
 * updated 3/2004 <dantifer.dang@sun.com>
 *
 */

/*
 * nathanb@actarg.com:
 * 
 * npshell.c:
 * - removed all code using printplugin.c's PluginInstance class
 * - added tracing calls so that debugging from inside mozilla is
 *   possible
 * - added in functionality to the Stream functions to accept the
 *   file UPS sends me
 * - NPP_StreamAsFile handles the actual printing
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "npapi.h"
#include "plugin.h"
#include "strings.h"
#include "plstr.h"

/*
 * Define PLUGIN_TRACE to have the wrapper functions print
 * messages to stderr whenever they are called.
 */

#ifdef PLUGIN_TRACE
#define PLUGINDEBUGSTR(msg)                       fprintf(stderr, msg)
#define PLUGINDEBUGSTR2(format, msg1)             fprintf(stderr, format, msg1)
#define PLUGINDEBUGSTR3(format, msg1, msg2)       fprintf(stderr, format, msg1, msg2)
#else
#define PLUGINDEBUGSTR(msg)
#define PLUGINDEBUGSTR2(format, msg1)
#define PLUGINDEBUGSTR3(format, msg1, msg2)
#endif


/*
 * All the real work happens in this function.
 *
 * A filename (fname) is passed in, and the plugin cat's the
 * file to LPR_CALL with PRINTER.
 *
 * All calls to system() are assumed safe as long as LPR_CALL and
 * PRINTER are defined correctly. The fname parameter comes directly
 * from mozilla, and not from the user, so is as safe as mozilla is.
 */

void
NPP_StreamAsFile(NPP instance, NPStream *stream, const char* fname)
{
    char tmpString[1024];
    char tmpString2[512];
    
    if (instance == NULL || stream == NULL || fname == NULL)
        return;
    
    PLUGINDEBUGSTR("NPP_StreamAsFile called\n");
    
    /* create a string that is a system call to lpr */
#ifdef PRINTER
    sprintf(tmpString2, LPR_CALL, PRINTER);
#else
#error 'PRINTER not defined'
#endif
    sprintf(tmpString, "cat %s | %s", fname, tmpString2);
    
    /* call lpr to print the file */
    PLUGINDEBUGSTR("NPP_StreamAsFile printing\n");
    system(tmpString);
    
    /* make a local copy of the file in case it doesn't print properly */
    PLUGINDEBUGSTR("NPP_StreamAsFile copying the file\n");
    sprintf(tmpString, "cat %s > ~/.lastupsprint", fname);
    system(tmpString);
}

/***********************************************************************
 *
 * Implementations of plugin API functions
 *
 ***********************************************************************/

char*
NPP_GetMIMEDescription(void)
{
    PLUGINDEBUGSTR2("NPP_GetMIMEDescription called: %s\n", MIME_TYPES_HANDLED);
    
    return(MIME_TYPES_HANDLED);
}


NPError
NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
    PLUGINDEBUGSTR("NPP_GetValue: ");
    
    /* don't call this here:
       the instance instatiated yet
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR; */
    
    NPError err = NPERR_NO_ERROR;

    switch (variable) {
        case NPPVpluginNameString:
            *((char **)value) = PLUGIN_NAME;
            break;
        case NPPVpluginDescriptionString:
            *((char **)value) = PLUGIN_DESCRIPTION;
            break;
        default:
            err = NPERR_GENERIC_ERROR;
    }
    
    PLUGINDEBUGSTR2("%s\n", *((char **)value));
    
    return err;
}


NPError
NPP_Initialize(void)
{
    PLUGINDEBUGSTR("NPP_Initialize called\n");
    
    return NPERR_NO_ERROR;
}


#ifdef OJI
jref
NPP_GetJavaClass()
{
    return NULL;
}
#endif


void
NPP_Shutdown(void)
{
    PLUGINDEBUGSTR("NPP_Shutdown called\n");
}


NPError
NPP_New(NPMIMEType pluginType,
    NPP instance,
    uint16 mode,
    int16 argc,
    char* argn[],
    char* argv[],
    NPSavedData* saved)
{
    PLUGINDEBUGSTR("NPP_New called\n");
    

    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    return NPERR_NO_ERROR;
}


NPError
NPP_Destroy(NPP instance, NPSavedData** save)
{
    PLUGINDEBUGSTR("NPP_Destroy called\n");
    

    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    return NPERR_NO_ERROR;
}


NPError
NPP_SetWindow(NPP instance, NPWindow* window)
{
    PLUGINDEBUGSTR("NPP_SetWindow called\n");
    
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;

    return NPERR_NO_ERROR;
}


NPError
NPP_NewStream(NPP instance,
          NPMIMEType type,
          NPStream *stream,
          NPBool seekable,
          uint16 *stype)
{
    FILE *file;

    PLUGINDEBUGSTR2("NPP_NewStream called: %s\n", stream->url);
    
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;
    
    /* tell the browser that we will accept the stream as a file*/
    *stype = NP_ASFILEONLY;
    
    /* no error here */
    return NPERR_NO_ERROR;
}


int32
NPP_WriteReady(NPP instance, NPStream *stream)
{
    /* this function is not called because I set NP_ASFILEONLY */
    
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;
    
    /* Number of bytes ready to accept in NPP_Write() */
    PLUGINDEBUGSTR("NPP_WriteReady: 1024*1024\n");
    return 1024*1024;   /* accept up to a meg */
}


int32
NPP_Write(NPP instance, NPStream *stream, int32 offset, int32 len, void *buffer)
{
    /* this function is not called because I set NP_ASFILEONLY */
    
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;
    
    PLUGINDEBUGSTR("NPP_Write called\n");
    return 0;
}


NPError
NPP_DestroyStream(NPP instance, NPStream *stream, NPError reason)
{
    PLUGINDEBUGSTR("NPP_DestroyStream called\n");
    
    if (instance == NULL)
        return NPERR_INVALID_INSTANCE_ERROR;
    
    return NPERR_NO_ERROR;
}


void
NPP_URLNotify(NPP instance, const char* url,
                NPReason reason, void* notifyData)
{
    PLUGINDEBUGSTR("NPP_URLNotify called\n");
}


void
NPP_Print(NPP instance, NPPrint* printInfo)
{
    PLUGINDEBUGSTR("NPP_StreamAsFile called\n");
}

