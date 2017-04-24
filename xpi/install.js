// this function verifies disk space in kilobytes
function verifyDiskSpace(dirPath, spaceRequired)
{
  var spaceAvailable;

  // Get the available disk space on the given path
  spaceAvailable = fileGetDiskSpaceAvailable(dirPath);

  // Convert the available disk space into kilobytes
  spaceAvailable = parseInt(spaceAvailable / 1024);

  // do the verification
  if(spaceAvailable < spaceRequired)
  {
    logComment("Insufficient disk space: " + dirPath);
    logComment("  required : " + spaceRequired + " K");
    logComment("  available: " + spaceAvailable + " K");
    return(false);
  }

  return(true);
}

// this function deletes a file if it exists
function deleteThisFile(dirKey, file)
{
  var fFileToDelete;

  fFileToDelete = getFolder(dirKey, file);
  logComment(file + " file: " + fFileToDelete);
  if(File.exists(fFileToDelete))
  {
    fileDelete(fFileToDelete);
    return(true);
  }
  else
    return(false);
}

// this function deletes a folder (recursively) if it exists
function deleteThisFolder(dirKey, folder)
{
  var fToDelete;

  fToDelete = getFolder(dirKey, folder);
  logComment(folder + " folder: " + fToDelete);
  if(File.exists(fToDelete))
  {
    File.dirRemove(fToDelete, true);
    return(true);
  }
  else
    return(false);
}

// OS type detection
// which platform?
function getPlatform()
{
  var platformStr;
  var platformNode;

  if('platform' in Install)
  {
    platformStr = new String(Install.platform);

    if (!platformStr.search(/^Macintosh/))
      platformNode = 'mac';
    else if (!platformStr.search(/^Win/))
      platformNode = 'win';
    else
      platformNode = 'unix';
  }
  else
  {
    var fOSMac  = getFolder("Mac System");
    var fOSWin  = getFolder("Win System");

    logComment("fOSMac: "  + fOSMac);
    logComment("fOSWin: "  + fOSWin);

    if(fOSMac != null)
      platformNode = 'mac';
    else if(fOSWin != null)
      platformNode = 'win';
    else
      platformNode = 'unix';
  }

  return platformNode;
}

var srDest = 16;

var err = initInstall("UPS Print Plugin",
            "Plugins/UPSPrintPlugin", "1.0b"); 
logComment("initInstall: " + err);

//var fPlugins= getFolder("Plugins");
var fPlugins = getFolder("Profile", "../../plugins");
logComment("plugins folder: " + fPlugins);

// verify the plugins directory exists
if(!File.exists(fPlugins))
{
    File.dirCreate(fPlugins);
}

// verify disk space available and install
if (verifyDiskSpace(fPlugins, srDest))
{
    err = addDirectory("UPS_Print_Plugin",
                       "1.0b",
                       "plugins",          // source folder 
                       fPlugins,           // target folder 
                       "",                 // target subdir 
                       true );             // force flag 

    logComment("addDirectory() returned: " + err);

    if (err==SUCCESS)
    {
	    err = performInstall(); 
	    logComment("performInstall() returned: " + err);
    }
    else
    {
	    cancelInstall(err);
	    logComment("cancelInstall() returned: " + err);
    }
}
else
    cancelInstall(INSUFFICIENT_DISK_SPACE);
